#include <string>

inline const std::string& GetProjectDir()
{
    static std::string projectDir = "C:/LEO/GIt/ClassProject/MushroomEngine/MushroomEngine/";
    return projectDir;
}
