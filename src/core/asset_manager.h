/****************************************************************************
#                                                                           #
#    INORGANIC MATERIALS CHEMISTRY CONFIDENTIAL                             #
#                                                                           #
#    Copyright 2016 Inorganic Materials Chemistry                           #
#                   Eindhoven University of Technology (TU/e)               #
#                                                                           #
#    All Rights Reserved.                                                   #
#                                                                           #
#    NOTICE:  All information contained herein is, and remains              #
#    the property of Inorganic Materials Chemistry (TU/e) and its suppliers,#
#    if any.  The intellectual and technical concepts contained             #
#    herein are proprietary to Inorganic Materials Chemistry (TU/e)         #
#    and its suppliers and may be covered by U.S. and Foreign Patents,      #
#    patents in process, and are protected by trade secret or copyright law.#
#    Dissemination of this information or reproduction of this Materials    #
#    is strictly forbidden unless prior written permission is obtained      #
#    from Inorganic Materials Chemistry (TU/e).                             #
#                                                                           #
#    Authors: Ivo Filot       <i.a.w.filot@tue.nl>                          #
#             Emiel Hensen    <e.j.m.hensen@tue.nl>                         #
#                                                                           #
*****************************************************************************/

#ifndef _ASSET_MANAGER_H
#define _ASSET_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
//#include <boost/predef.h>
#include <string>

class AssetManager{
private:
    std::string execution_directory;
    std::string root_directory;

public:
    static AssetManager& get() {
        static AssetManager am_instance;
        return am_instance;
    }

    const std::string& get_execution_directory() const {
        return this->execution_directory;
    }

    const std::string& get_root_directory() const {
        return this->root_directory;
    }

    void init(const char* argv0);

private:
    AssetManager();

    std::string executable_path_fallback(const char *argv0)
    {
        if (argv0 == nullptr || argv0[0] == 0)
        {
            return "";
        }
        boost::system::error_code ec;
        boost::filesystem::path p(
            boost::filesystem::canonical(
                argv0, boost::filesystem::current_path(), ec));
        return p.make_preferred().string();
    }

    #if (BOOST_OS_CYGWIN || BOOST_OS_WINDOWS) // {

    std::string executable_path(const char *argv0)
    {
        return executable_path_fallback(argv0);
    }

    #elif (BOOST_OS_MACOS) // } {

    std::string executable_path(const char *argv0)
    {
        return executable_path_fallback(argv0);
    }

    #elif (BOOST_OS_SOLARIS) // } {

    #include <stdlib.h>

    std::string executable_path(const char *argv0)
    {
        std::string ret = getexecname();
        if (ret.empty())
        {
            return executable_path_fallback(argv0);
        }
        boost::filesystem::path p(ret);
        if (!p.has_root_directory())
        {
            boost::system::error_code ec;
            p = boost::filesystem::canonical(
                p, boost::filesystem::current_path(), ec);
            ret = p.make_preferred().string();
        }
        return ret;
    }

    #elif (BOOST_OS_BSD) // } {

    #include <sys/sysctl.h>

    std::string executable_path(const char *argv0)
    {
        int mib[4] = {0};
        mib[0] = CTL_KERN;
        mib[1] = KERN_PROC;
        mib[2] = KERN_PROC_PATHNAME;
        mib[3] = -1;
        char buf[1024] = {0};
        size_t size = sizeof(buf);
        sysctl(mib, 4, buf, &size, NULL, 0);
        if (size == 0 || size == sizeof(buf))
        {
            return executable_path_fallback(argv0);
        }
        std::string path(buf, size);
        boost::system::error_code ec;
        boost::filesystem::path p(
            boost::filesystem::canonical(
                path, boost::filesystem::current_path(), ec));
        return p.make_preferred().string();
    }

    #elif (BOOST_OS_LINUX) // } {

    #include <unistd.h>

    std::string executable_path(const char *argv0)
    {
        char buf[1024] = {0};
        ssize_t size = readlink("/proc/self/exe", buf, sizeof(buf));
        if (size == 0 || size == sizeof(buf))
        {
            return executable_path_fallback(argv0);
        }
        std::string path(buf, size);
        boost::system::error_code ec;
        boost::filesystem::path p(
            boost::filesystem::canonical(
                path, boost::filesystem::current_path(), ec));
        return p.make_preferred().string();
    }

    #else // } {

    std::string executable_path(const char *argv0)
    {
        return executable_path_fallback(argv0);
    }

    #endif // }

    AssetManager(AssetManager const&)          = delete;
    void operator=(AssetManager const&)  = delete;
};

#endif //_ASSET_MANAGER_H
