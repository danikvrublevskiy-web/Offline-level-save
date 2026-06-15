#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;
namespace ols {
struct LevelRecord { int levelID=0; int normalPercent=0; int practicePercent=0; int attempts=0; int jumps=0; bool coins[3]={false,false,false}; int64_t lastPlayed=0; };
class RecordsManager {
public:
 static LevelRecord load(int levelID);
 static void save(const LevelRecord& rec);
 static void updateFromPlayLayer(GJGameLevel* level, int percent, bool isPractice);
 static std::vector<LevelRecord> getAll();
 static bool exportJson(std::filesystem::path out);
};
}
