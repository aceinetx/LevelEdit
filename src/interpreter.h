#include <Geode/Geode.hpp>
struct PatternEntry {
  int objectId;
  int percentage;
};

namespace Interpreter {
std::vector<PatternEntry> parse(std::string pattern);
int chooseRandomObjId(std::vector<PatternEntry> parsed);
};  // namespace Interpreter