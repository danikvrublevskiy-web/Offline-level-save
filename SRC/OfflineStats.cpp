#include "OfflineManager.hpp"
namespace ols { struct Stats{int total=0; size_t bytes=0;}; Stats getStats(){ Stats s; auto list=Manager::getAll(); s.total=(int)list.size(); for(auto& m:list) s.bytes+=Manager::getData(m.id).size(); return s; } }
