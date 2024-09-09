#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <format>

using namespace geode::prelude;

#include <alphalaneous.editortab_api/include/EditorTabs.hpp>

#include "editor.h"
#include "operations.h"
#include "pattern_popup.hpp"

// clang-format off
class $modify(LevelEditUI, EditorUI){
  struct Fields {
    GameObject* firstCorner;
    GameObject* secondCorner;
  };

  bool init(LevelEditorLayer * p0){
    if (!EditorUI::init(p0)) return false;

    m_fields->firstCorner = nullptr;
    m_fields->secondCorner = nullptr;

    EditorTabs::addTab(
      this, TabType::BUILD, "aceinetxLevelEdit"_spr,
      [](EditorUI *ui, CCMenuItemToggler *toggler) -> CCNode * {
        auto items = CCArray::create();
        
				auto ico_spr = CCSprite::create("level-edit-ico.png"_spr);
				ico_spr->setScale(0.25f);
				EditorTabUtils::setTabIcons(toggler, ico_spr, ico_spr);

        auto firstCornerSpr = CCSprite::create("level-edit-first.png"_spr);
        auto firstCornerBtn = CCMenuItemSpriteExtra::create(firstCornerSpr, ui, menu_selector(LevelEditUI::onFirstCorner));

        auto secondCornerSpr = CCSprite::create("level-edit-second.png"_spr);
        auto secondCornerBtn = CCMenuItemSpriteExtra::create(secondCornerSpr, ui, menu_selector(LevelEditUI::onSecondCorner));

        auto fillSpr = CCSprite::create("level-edit-fill.png"_spr);
        auto fillBtn = CCMenuItemSpriteExtra::create(fillSpr, ui, menu_selector(LevelEditUI::onFill));

        auto patternSpr = CCSprite::create("level-edit-pattern.png"_spr);
        auto patternBtn = CCMenuItemSpriteExtra::create(patternSpr, ui, menu_selector(LevelEditUI::onPattern));

        items->addObject(firstCornerBtn);
        items->addObject(secondCornerBtn);
        items->addObject(fillBtn);
        items->addObject(patternBtn);


        return EditorTabUtils::createEditButtonBar(items, ui);
      }, [](EditorUI *, bool state, CCNode *) {});
    
    return true;
  }

  void onFirstCorner(CCObject* sender){
    m_fields->firstCorner = GetSelectedObject();
  }

  void onSecondCorner(CCObject* sender){
    m_fields->secondCorner = GetSelectedObject();
  }

  bool checkCorners(){
    if(m_fields->firstCorner == nullptr || m_fields->secondCorner == nullptr){
      Notification::create("Failed to perform operation: missing corners", CCSprite::createWithSpriteFrameName("particle_193_001.png"), 2.0f)->show();
      return false;
    }
    return true;
  }

  void onFill(CCObject* sender){
    int affected=0;
    if(!checkCorners()) return;
    if(!Operations::Fill(m_fields->firstCorner, m_fields->secondCorner, &affected)){
      Notification::create("Failed to perform operation (probably no EditorUI)", CCSprite::createWithSpriteFrameName("particle_193_001.png"), 2.0f)->show();
    }
    Notification::create(std::format("Success (Affected {} objects)", affected), CCSprite::createWithSpriteFrameName("particle_50_001.png"), 1.0f)->show();
  }

  void onPattern(CCObject* sender){
    PatternPopup::create("Pattern")->show();
  }
};
// clang-format on