//
// Created by simakov on 16.08.2020.
//
#include <components/all_components.h>
#include <ecs/engine.h>
#include <ecs/entity_manager.h>
#include <levels/generator.h>
#include <scenes/game_scene.h>
#include <systems/all_systems.h>

#include <iostream>  // NOLINT
#include <string>
#include <vector>

void GameScene::CreateWall(int col, int row) {
  auto wall = engine.GetEntityManager()->CreateEntity("wall");
  wall->Add<TextureComponent>('#', "steel");
  wall->Add<SpriteComponent>(0xE005);
  wall->Add<CollisionComponent>();
  wall->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateTree(int col, int row) {
  auto tree = engine.GetEntityManager()->CreateEntity("wall");
  tree->Add<TextureComponent>('T', "green");
  tree->Add<SpriteComponent>(0xE009);
  tree->Add<CollisionComponent>();
  tree->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateMountain(int col, int row) {
  auto tree = engine.GetEntityManager()->CreateEntity("wall");
  tree->Add<TextureComponent>('^', "grey");
  tree->Add<SpriteComponent>(0xE021);
  tree->Add<CollisionComponent>();
  tree->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateChest(int col, int row) {
  auto chest = engine.GetEntityManager()->CreateEntity("chest");
  chest->Add<TextureComponent>('X', "yellow");
  chest->Add<SpriteComponent>(0xE012);
  chest->Add<CollisionComponent>();
  chest->Add<ChestComponent>(100);
  chest->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreatePlayer(int col, int row) {
  auto player = engine.GetEntityManager()->CreateEntity(0, "player");
  datatransmitter_->CollidableEntitites.emplace(player->GetId(), player->GetId());
  player->Add<PlayerComponent>(datatransmitter_->wallet_, datatransmitter_->turn_, datatransmitter_->turns_left_,
                               datatransmitter_->key_count_, datatransmitter_->potion_count_);
  player->Add<StatsComponent>(datatransmitter_->damage_, datatransmitter_->strength_, datatransmitter_->agility_,
                              datatransmitter_->armor_);
  if (datatransmitter_->character_ == "shieldbearer") {
    player->Add<SkillComponent>(20, "bash");
  } else if (datatransmitter_->character_ == "duelant") {
    player->Add<SkillComponent>(20, "slaughter", 20);
  } else if (datatransmitter_->character_ == "warrior") {
    player->Add<SkillComponent>(20, "poison", 10);
  }
  player->Add<TextureComponent>('@');
  player->Add<SpriteComponent>(datatransmitter_->sprite_of_character_);
  player->Add<CollisionComponent>();
  player->Add<PositionComponent>(Pair(col, row));
  player->Add<TransferComponent>(false, datatransmitter_->current_level);
  player->Add<HealthComponent>(datatransmitter_->maximum_health_, datatransmitter_->current_health_);
  datatransmitter_->pos_ = Pair(col, row);
}
void GameScene::CreateKey(int col, int row) {
  auto key = engine.GetEntityManager()->CreateEntity("key");
  key->Add<TextureComponent>('k', "orange");
  key->Add<SpriteComponent>(0xE015);
  key->Add<CollisionComponent>();
  key->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateMoney(int col, int row) {
  auto coin = engine.GetEntityManager()->CreateEntity("money");
  coin->Add<TextureComponent>('$', "green");
  coin->Add<SpriteComponent>(0xE002);
  coin->Add<LootComponent>(10);
  coin->Add<CollisionComponent>();
  coin->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreatePotion(int col, int row) {
  auto potion = engine.GetEntityManager()->CreateEntity("potion");
  potion->Add<TextureComponent>('p', "pink");
  potion->Add<SpriteComponent>(0xE014);
  potion->Add<CollisionComponent>();
  potion->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateBorders(int col, int row) {
  auto wall = engine.GetEntityManager()->CreateEntity("wall");
  wall->Add<CollisionComponent>();
  wall->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateRoad(int col, int row) {
  auto road = engine.GetEntityManager()->CreateEntity("road");
  road->Add<TextureComponent>('+', "brown", 0);
  road->Add<SpriteComponent>(0xE003);
  road->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateBridge(int col, int row) {
  auto road = engine.GetEntityManager()->CreateEntity("road");
  road->Add<TextureComponent>('|', "brown", 0);
  road->Add<SpriteComponent>(0xE020);
  road->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateWater(int col, int row) {
  auto road = engine.GetEntityManager()->CreateEntity("wall");
  road->Add<TextureComponent>('x', "light blue", 0);
  road->Add<CollisionComponent>();
  road->Add<SpriteComponent>(0xE006);
  road->Add<PositionComponent>(Pair(col, row));
}

void GameScene::CreateExitDoor(int col, int row) {
  auto door = engine.GetEntityManager()->CreateEntity("door");
  door->Add<TextureComponent>('<', "brown");
  door->Add<SpriteComponent>(0xE004);
  door->Add<CollisionComponent>();
  door->Add<PositionComponent>(Pair(col, row));
  door->Add<DoorComponent>(datatransmitter_->prev_level);
  if (datatransmitter_->destination_ == datatransmitter_->prev_level + "_" + datatransmitter_->current_level) {
    CreatePlayer(col + 1, row);
  }
}

void GameScene::CreateEnterDoor(int col, int row) {
  auto door = engine.GetEntityManager()->CreateEntity("door");
  door->Add<TextureComponent>('>', "brown");
  door->Add<SpriteComponent>(0xE004);
  door->Add<CollisionComponent>();
  door->Add<PositionComponent>(Pair(col, row));
  door->Add<DoorComponent>(datatransmitter_->next_level);
  if (datatransmitter_->destination_ == datatransmitter_->next_level + "_" + datatransmitter_->current_level) {
    CreatePlayer(col - 1, row);
  }
  if (datatransmitter_->current_level == "first_level" &&
      (datatransmitter_->destination_ != datatransmitter_->next_level + "_" + datatransmitter_->current_level)) {
    CreatePlayer(56, 20);
  }
}

void GameScene::CreateEnemyWanderer(int col, int row) {
  auto enemy = engine.GetEntityManager()->CreateEntity("enemy");
  datatransmitter_->CollidableEntitites.emplace(enemy->GetId(), enemy->GetId());
  enemy->Add<AIComponent>(10, 2, "wanderer", 20);
  enemy->Add<EffectsComponent>();
  enemy->Add<BehaviourComponent>(Pair(col, row), "wander", 10);
  enemy->Add<TextureComponent>('E', "red");
  enemy->Add<SpriteComponent>(0xE016);
  enemy->Add<CollisionComponent>();
  enemy->Add<PositionComponent>(Pair(col, row));
  enemy->Add<HealthComponent>(30, 30);
}
void GameScene::CreateEnemyGuardian(int col, int row) {
  auto enemy = engine.GetEntityManager()->CreateEntity("enemy");
  datatransmitter_->CollidableEntitites.emplace(enemy->GetId(), enemy->GetId());
  enemy->Add<AIComponent>(10, 7, "guardian", 5);
  enemy->Add<EffectsComponent>();
  enemy->Add<BehaviourComponent>(Pair(col, row), "guard", 10);
  enemy->Add<TextureComponent>('G', "red");
  enemy->Add<SpriteComponent>(0xE017);
  enemy->Add<CollisionComponent>();
  enemy->Add<PositionComponent>(Pair(col, row));
  enemy->Add<HealthComponent>(100, 100);
}

void GameScene::FillEntityCreationMap() {
  EntityCreationMap.emplace('#', &GameScene::CreateWall);
  EntityCreationMap.emplace('T', &GameScene::CreateTree);
  EntityCreationMap.emplace('^', &GameScene::CreateMountain);
  EntityCreationMap.emplace('+', &GameScene::CreateRoad);
  EntityCreationMap.emplace('|', &GameScene::CreateBridge);
  EntityCreationMap.emplace('x', &GameScene::CreateWater);
  EntityCreationMap.emplace('/', &GameScene::CreateBorders);
  EntityCreationMap.emplace('$', &GameScene::CreateMoney);
  EntityCreationMap.emplace('>', &GameScene::CreateEnterDoor);
  EntityCreationMap.emplace('<', &GameScene::CreateExitDoor);
  EntityCreationMap.emplace('X', &GameScene::CreateChest);
  EntityCreationMap.emplace('E', &GameScene::CreateEnemyWanderer);
  EntityCreationMap.emplace('G', &GameScene::CreateEnemyGuardian);
  EntityCreationMap.emplace('k', &GameScene::CreateKey);
  EntityCreationMap.emplace('p', &GameScene::CreatePotion);
}
void GameScene::CallEntityCreateFunction(const char& name, int col, int row) {
  auto iter = EntityCreationMap.find(name);
  if (iter == EntityCreationMap.end()) {
    return;
  }
  (this->*EntityCreationMap[name])(col, row);
}

void GameScene::OnCreateFromFile(const CharFileReader* levelreader) {
  FillEntityCreationMap();
  for (int row = 0; row < levelreader->GetResourceMatrix().size(); ++row) {
    for (int col = 0; col < levelreader->GetResourceMatrix()[row].size(); ++col) {
      CallEntityCreateFunction(levelreader->GetResourceMatrix()[row][col], col, row);
    }
  }
  auto sys = engine.GetSystemManager();
  sys->AddSystem<PlayerMovementSystem>(controls, 1);
  sys->AddSystem<SkillSystem>(2, datatransmitter_);
  sys->AddSystem<AIBehaviourSystem>(3, datatransmitter_);
  sys->AddSystem<CollisionSystem>(4, datatransmitter_);
  sys->AddSystem<GameOverSystem>(controls, 5, ctx_, datatransmitter_);
  sys->AddSystem<PlayerStatusSystem>(6, datatransmitter_);
  sys->AddSystem<RenderingSystem>(7, datatransmitter_, 1);
}

void GameScene::OnCreate() {
  if (datatransmitter_->current_level == "first_level") {
    CharFileReader level_array("resources/levels/level_1.dat");
    level_array.Read();
    OnCreateFromFile(&level_array);
    datatransmitter_->file_name = "resources/levels/level_1.dat";
  } else if (datatransmitter_->current_level == "second_level") {
    CharFileReader level_array("resources/levels/level_2.dat");
    level_array.Read();
    OnCreateFromFile(&level_array);
    datatransmitter_->file_name = "resources/levels/level_2.dat";
  } else if (datatransmitter_->current_level == "third_level") {
    CharFileReader level_array("resources/levels/level_3.dat");
    level_array.Read();
    OnCreateFromFile(&level_array);
    datatransmitter_->file_name = "resources/levels/level_3.dat";
  } else {
    Generate();
    CharFileReader level_array("resources/levels/generated_level.dat");
    level_array.Read();
    OnCreateFromFile(&level_array);
    datatransmitter_->file_name = "resources/levels/generated_level.dat";
  }
}
void GameScene::OnRender() {
  engine.OnUpdate();
}
void GameScene::OnExit() {
  datatransmitter_->CollidableEntitites.clear();
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
GameScene::GameScene(Context* const ctx, const Controls& controls) : Scene(ctx), controls(controls) {}
GameScene::GameScene(Context* const ctx, const Controls& controls, DataTransmitter* datatransmitter)
    : Scene(ctx), controls(controls), datatransmitter_(datatransmitter) {}
