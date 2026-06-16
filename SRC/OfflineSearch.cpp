#include "OfflineManager.hpp"
#include <algorithm>
namespace ols { std::vector<LevelMeta> searchLevels(std::string q){ std::transform(q.begin(),q.end(),q.begin(),::tolower); std::vector<LevelMeta> out; for(auto& m: Manager::getAll()){ std::string name=m.name; std::transform(name.begin(),name.end(),name.begin(),::tolower); if(name.find(q)!=std::string::npos) out.push_back(m);} return out; } }
