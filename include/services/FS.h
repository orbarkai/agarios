#ifndef FS_H_
#define FS_H_

#include <filesystem>
#include "nlohmann/json.hpp"

namespace FS
{
    typedef std::filesystem::path Path;

    FS::Path basePath();
    FS::Path resorcesPath();

    nlohmann::json getJsonResource(std::string const resourceName);
};

#endif