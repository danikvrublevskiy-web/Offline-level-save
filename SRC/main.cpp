#include "OfflineManager.hpp"
#include "RecordsManager.hpp"
class OfflineBrowser;
#include "OfflineBrowserLayer.cpp"
class $modify(OLSLevelInfoLayer, LevelInfoLayer) {
 struct Fields { GJGameLevel* m_level=nullptr; };
 bool init(GJGameLevel* level, bool challengeReward){ if(!LevelInfoLayer::init(level,challengeReward)) return false; m_fields->m_level=level; if(level->m_levelID>0 && Mod::get()->getSettingValue<bool>("save-records")){ auto rec=ols::RecordsManager::load(level->m_levelID); if(rec.normalPercent>0) level->m_normalPercent=rec.normalPercent; } if(level->m_levelID<=0) return true; auto leftMenu=typeinfo_cast<CCMenu*>(this->getChildByID("left-side-menu")); if(!leftMenu) return true; bool saved=ols::Manager::isSaved(level->m_levelID); auto sprite=CCSprite::create(saved?"save-btn-on.png"_spr:"save-btn.png"_spr); if(!sprite) sprite=CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png"); sprite->setScale(0.7f); auto btn=CCMenuItemSpriteExtra::create(sprite,this,menu_selector(OLSLevelInfoLayer::onToggle)); btn->setID("ols-save-btn"_spr); leftMenu->addChild(btn); leftMenu->updateLayout(); return true; }
 void onToggle(CCObject* sender){ auto level=m_fields->m_level; if(!level) return; int id=level->m_levelID; if(ols::Manager::isSaved(id)){ ols::Manager::remove(id); Notification::create("Удалено",NotificationIcon::Info)->show(); } else { if(level->m_levelString.empty()){ FLAlertLayer::create("Offline Saver","Сначала скачай уровень","OK")->show(); return;} ols::Manager::save(level); Notification::create(fmt::format("{} сохранен!",level->m_levelName),NotificationIcon::Success)->show(); } if(auto btn=typeinfo_cast<CCMenuItemSpriteExtra*>(sender)){ bool now=ols::Manager::isSaved(id); auto spr=CCSprite::create(now?"save-btn-on.png"_spr:"save-btn.png"_spr); if(spr){spr->setScale(0.7f); btn->setNormalImage(spr);} } }
};
class $modify(OLSGameLevelManager, GameLevelManager){
 void levelDownloadFinished(GJGameLevel* level){ GameLevelManager::levelDownloadFinished(level); if(Mod::get()->getSettingValue<bool>("auto-save") && level && level->m_levelID>0) ols::Manager::save(level); }
 void downloadLevel(int levelID, bool isGauntlet){ GameLevelManager::downloadLevel(levelID,isGauntlet); Loader::get()->queueInMainThread([levelID](){ auto glm=GameLevelManager::sharedState(); auto level=glm->getSavedLevel(levelID); if(!level) return; auto data=ols::Manager::getData(levelID); if(!data.empty() && level->m_levelString.empty()){ level->m_levelString=data; if(Mod::get()->getSettingValue<bool>("restore-notify")) Notification::create("Уровень восстановлен",NotificationIcon::Success)->show(); }}); }
};
class $modify(OLSPlayLayer, PlayLayer){
 void onQuit(){ PlayLayer::onQuit(); if(m_level) ols::RecordsManager::updateFromPlayLayer(m_level, getCurrentPercentInt(), m_isPracticeMode); }
 void levelComplete(){ PlayLayer::levelComplete(); if(m_level) ols::RecordsManager::updateFromPlayLayer(m_level, 100, false); }
};
class $modify(OLSCreatorLayer, CreatorLayer){
 bool init(){ if(!CreatorLayer::init()) return false; if(auto menu=typeinfo_cast<CCMenu*>(this->getChildByID("creator-buttons-menu"))){ auto spr=ButtonSprite::create("Offline",90,true,"bigFont.fnt","GJ_button_04.png",30,0.7f); auto btn=CCMenuItemSpriteExtra::create(spr,this,menu_selector(OLSCreatorLayer::onOffline)); btn->setID("ols-browser-btn"_spr); menu->addChild(btn); menu->updateLayout(); } return true; }
 void onOffline(CCObject*){ auto list=ols::Manager::getAll(); auto records=ols::RecordsManager::getAll(); std::string text=fmt::format("Offline Level Saver v3.0\nCreated by Geo\n\nУровней: {}\nРекордов: {}\n\nВсе рекорды сохраняются автоматически!", list.size(), records.size()); FLAlertLayer::create("Offline Library", text, "OK")->show(); }
};
