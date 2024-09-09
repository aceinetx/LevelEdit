#include "operations.h"

#include <Geode/Geode.hpp>
#include <Geode/ui/Notification.hpp>

#include "editor.h"
#include "interpreter.h"
#include "pattern_popup.hpp"

bool Operations::Fill(GameObject *firstCorner, GameObject *secondCorner,
                      int *affected) {
  LevelEditorLayer *editor = GameManager::sharedState()->getEditorLayer();
  EditorUI *ui;
  if (editor == nullptr) return false;
  ui = editor->m_editorUI;
  if (ui == nullptr) return false;

  int affected_obj = 0;

  std::vector<PatternEntry> parsed = Interpreter::parse(pattern);

  if (firstCorner->getPositionX() <= secondCorner->getPositionX()) {
    double x;
    if (firstCorner->getPositionY() < secondCorner->getPositionY()) {
      double y = firstCorner->getPositionY();
      while (y <= secondCorner->getPositionY()) {
        x = firstCorner->getPositionX();
        while (x <= secondCorner->getPositionX()) {
          CreateEditorObject(Interpreter::chooseRandomObjId(parsed), x, y);
          affected_obj++;
          x += 30;
        }
        y += 30;
      }
    } else {
      double y = secondCorner->getPositionY();
      while (y <= firstCorner->getPositionY()) {
        x = firstCorner->getPositionX();
        while (x <= secondCorner->getPositionX()) {
          CreateEditorObject(Interpreter::chooseRandomObjId(parsed), x, y);
          affected_obj++;
          x += 30;
        }
        y += 30;
      }
    }
    firstCorner->removeMeAndCleanup();
    secondCorner->removeMeAndCleanup();
    firstCorner = nullptr;
    secondCorner = nullptr;
  }

  if (firstCorner != nullptr && secondCorner != nullptr) {
    if (firstCorner->getPositionX() >= secondCorner->getPositionX()) {
      double x;
      if (firstCorner->getPositionY() > secondCorner->getPositionY()) {
        double y = secondCorner->getPositionY();
        while (y <= firstCorner->getPositionY()) {
          x = secondCorner->getPositionX();
          while (x <= firstCorner->getPositionX()) {
            CreateEditorObject(Interpreter::chooseRandomObjId(parsed), x, y);
            affected_obj++;
            x += 30;
          }
          y += 30;
        }
      } else {
        double y = firstCorner->getPositionY();
        while (y <= secondCorner->getPositionY()) {
          x = secondCorner->getPositionX();
          while (x <= firstCorner->getPositionX()) {
            CreateEditorObject(Interpreter::chooseRandomObjId(parsed), x, y);
            affected_obj++;
            x += 30;
          }
          y += 30;
        }
      }
      firstCorner->removeMeAndCleanup();
      secondCorner->removeMeAndCleanup();
      firstCorner = nullptr;
      secondCorner = nullptr;

      ui->deselectAll();
    }
  }

  if (affected != nullptr) {
    *affected = affected_obj;
  }

  return true;
}