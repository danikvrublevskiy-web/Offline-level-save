#include "OfflineManager.hpp"
namespace ols { bool exportAll(std::filesystem::path outDir){ int n=0; for(auto& m: Manager::getAll()) if(Manager::exportGmd(m.id,outDir)) n++; return n>0; } }
