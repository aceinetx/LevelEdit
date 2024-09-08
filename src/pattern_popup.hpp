#include <Geode/Geode.hpp>

extern std::string pattern;

class PatternPopup : public geode::Popup<std::string const &> {
 protected:
  bool setup(std::string const &value) override;

 public:
  static PatternPopup *create(std::string const &text);
};