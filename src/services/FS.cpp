
#include <filesystem>
#include <fstream>
#include "services/FS.h"
#include "services/Console.h"

FS::Path FS::basePath(){
     return std::filesystem::current_path().parent_path();
}

FS::Path FS::resorcesPath(){
     return FS::basePath() / "resources";
}

nlohmann::json FS::getJsonResource(std::string const resourceName) {
    FS::Path pathToResource = FS::resorcesPath() / resourceName;
    std::ifstream resourceStream(pathToResource.string());
    nlohmann::json resourceJson;
    resourceStream >> resourceJson;
    return resourceJson;
}