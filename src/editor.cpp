#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
#include <Geode/binding/EditorUI.hpp>

GameObject *GetSelectedObject()
{
  LevelEditorLayer *editor = GameManager::sharedState()->getEditorLayer();
  EditorUI *ui;
  if (editor == nullptr)
    return nullptr;
  ui = editor->m_editorUI;
  if (ui == nullptr)
    return nullptr;
  return ui->m_selectedObject;
}

GameObject *CreateEditorObject(int id, double x, double y)
{
  LevelEditorLayer *editor = GameManager::sharedState()->getEditorLayer();
  EditorUI *ui;
  if (editor == nullptr)
    return nullptr;
  ui = editor->m_editorUI;
  if (ui == nullptr)
    return nullptr;

  cocos2d::CCPoint point;
  point.y = (float)y;
  point.x = (float)x;
  return editor->createObject(id, point, true);
}