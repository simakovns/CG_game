//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_SCENES_MAIN_MENU_H_
#define INCLUDE_SCENES_MAIN_MENU_H_

#include <controls.h>
#include <ecs/engine.h>
#include <scenes/scene.h>
#include <systems/data_transmitter.h>

#include <vector>
#include <string>

class MainMenuScene : public Scene {
  const Engine engine{};
  const Controls& controls;
  DataTransmitter* datatransmitter_;

 public:
  MainMenuScene(Context* const ctx, const Controls& controls);
  MainMenuScene(Context* const ctx, const Controls& controls, DataTransmitter* datatransmitter);

  std::string GetColoredSymbol(const std::string& color, const char& symbol);
  void RenderCharacter(const std::string& character_name, const int& box_x_size, const int& box_y_size);
  void ChooseCharacterText();
  void ChooseCharacterSprite();
  void OnCreateText();
  void OnCreateSprites();

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_MAIN_MENU_H_
