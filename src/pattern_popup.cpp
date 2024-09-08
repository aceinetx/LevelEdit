#include "pattern_popup.hpp"

#include <Geode/Geode.hpp>

std::string pattern = "1";

void pattern_changed(const std::string& text) {
  pattern.clear();
  pattern.append(text);
}

bool PatternPopup::setup(std::string const& value) {
  auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

  auto input = geode::TextInput::create(240.0f / 2, value);
  input->setFilter(
      "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890%,.;");
  input->setString(pattern, false);
  std::function<void(const std::string&)> callback = pattern_changed;

  input->setCallback(callback);
  input->setPosition(winSize / 2);
  this->addChild(input);

  return true;
}

PatternPopup* PatternPopup::create(std::string const& text) {
  auto ret = new PatternPopup();
  if (ret->init(240.f, 160.f, text)) {
    ret->autorelease();
    return ret;
  }

  delete ret;
  return nullptr;
}