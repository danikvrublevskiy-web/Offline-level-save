#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;
namespace ols {
inline std::string keyData(int id) { return fmt::format("level_{}", id); }
inline std::string keyMeta(int id) { return fmt::format("meta_{}", id); }
struct LevelMeta { int id=0; std::string name; std::string author; int64_t savedAt=0; };
class Manager {
public:
 static bool save(GJGameLevel* level);
 static bool remove(int levelID);
 static bool isSaved(int levelID);
 static std::string getData(int levelID);
 static std::vector<LevelMeta> getAll();
 static bool exportGmd(int levelID, std::filesystem::path outDir);
};
}
