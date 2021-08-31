//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_SCENES_GAME_OVER_H_
#define INCLUDE_SCENES_GAME_OVER_H_

#include <controls.h>
#include <ecs/engine.h>
#include <scenes/scene.h>
#include <systems/data_transmitter.h>

#include <vector>

class GameOverScene : public Scene {
  const Engine engine{};
  const Controls& controls;
  DataTransmitter* datatransmitter_;

 public:
  GameOverScene(Context* const ctx, const Controls& controls);
  GameOverScene(Context* const ctx, const Controls& controls, DataTransmitter* datatransmitter);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_GAME_OVER_H_
