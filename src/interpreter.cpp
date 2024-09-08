#include "interpreter.h"

#include <Geode/Geode.hpp>

std::vector<PatternEntry> Interpreter::parse(std::string pattern) {
  std::vector<PatternEntry> result;
  PatternEntry entry;
  entry.objectId = 0;
  entry.percentage = 0;
  bool added = false;
  for (int i = 0; i < pattern.length(); i++) {
    char c = pattern.at(i);
    added = false;
    if (c >= '0' && c <= '9') {
      entry.objectId *= 10;
      entry.objectId += c - 48;
    } else if (c == '%') {
      entry.percentage = entry.objectId;
      entry.objectId = 0;
    } else if (c == ',') {
      if (entry.objectId <= 0) entry.objectId = 1;
      result.push_back(entry);
      entry.objectId = 0;
      entry.percentage = 0;
      added = true;
    }
  }

  if (!added) {
    result.push_back(entry);
  }

  for (int i = 0; i < result.size(); i++) {
    PatternEntry &e = result.at(i);
    if (e.percentage == 0) e.percentage = 100 / result.size();
  }
  return result;
}

int Interpreter::chooseRandomObjId(std::vector<PatternEntry> parsed) {
  while (true) {
    for (int i = 0; i < parsed.size(); i++) {
      PatternEntry &e = parsed.at(i);
      if ((rand() % 100) <= e.percentage) {
        return e.objectId;
      }
    }
  }
  return parsed.at(0).objectId;
}