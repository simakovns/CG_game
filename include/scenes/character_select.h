//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_SCENES_CHARACTER_SELECT_H_
#define INCLUDE_SCENES_CHARACTER_SELECT_H_

#include <controls.h>
#include <ecs/engine.h>
#include <scenes/scene.h>
#include <systems/data_transmitter.h>

#include <vector>
#include <string>

class CharacterSelectScene : public Scene {
  const Engine engine{};
  const Controls& controls;
  DataTransmitter* datatransmitter_;

 public:
  CharacterSelectScene(Context* const ctx, const Controls& controls);
  CharacterSelectScene(Context* const ctx, const Controls& controls, DataTransmitter* datatransmitter);

  std::string GetColoredSymbol(const std::string& color, const char& symbol);
  void PrintParcedString(const int& x, const int& y, const int& dy, const std::string& str);
  void PrintBorders(const int& x_1, const int& x_2, const int& y_1, const int& y_2, const bool IsSelected);
  void RenderCharacter(const std::string& character_name, const int& box_x_size, const int& box_y_size);
  void ChooseCharacterText();
  void ChooseCharacterSprite();
  void OnCreateText();
  void OnCreateSprites();

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_CHARACTER_SELECT_H_
