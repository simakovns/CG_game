//
// Created by simakov on 16.08.2020.
//
#ifndef INCLUDE_SCENES_GAME_SCENE_H_
#define INCLUDE_SCENES_GAME_SCENE_H_

#include <controls.h>
#include <ecs/engine.h>
#include <scenes/scene.h>
#include <systems/data_transmitter.h>
#include <levels/char_file_reader.h>

#include <map>
#include <vector>
#include <string>

class GameScene : public Scene {
  const Engine engine{};
  const Controls& controls;
  DataTransmitter* datatransmitter_;

 public:
  typedef void (GameScene::*EntityCreateFunc)(int col, int row);
  std::map<char, EntityCreateFunc> EntityCreationMap;
  void FillEntityCreationMap();
  void CallEntityCreateFunction(const char& name, int col, int row);

  void CreateWall(int col, int row);
  void CreateTree(int col, int row);
  void CreateMountain(int col, int row);
  void CreatePlayer(int col, int row);
  void CreateChest(int col, int row);
  void CreateMoney(int col, int row);
  void CreateKey(int col, int row);
  void CreatePotion(int col, int row);
  void CreateBorders(int col, int row);
  void CreateRoad(int col, int row);
  void CreateBridge(int col, int row);
  void CreateWater(int col, int row);
  void CreateExitDoor(int col, int row);
  void CreateEnterDoor(int col, int row);
  void CreateEnemyWanderer(int col, int row);
  void CreateEnemyGuardian(int col, int row);

  GameScene(Context* const ctx, const Controls& controls);
  GameScene(Context* const ctx, const Controls& controls, DataTransmitter* datatransmitter);

  void OnCreateFromFile(const CharFileReader* levelreader);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_GAME_SCENE_H_

