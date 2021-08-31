//
// Created by simakov on 17.07.2020.
//

#include <scenes/game_over.h>
#include <systems/all_systems.h>

void GameOverScene::OnCreate() {
  auto sys = engine.GetSystemManager();

  sys->AddSystem<ScoreSystem>(1, datatransmitter_);
}
void GameOverScene::OnRender() {
  engine.OnUpdate();
  if (controls.Get_is_pressed_enter()) {
    ctx_->scene_ = "main_menu";
  }
}
void GameOverScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
GameOverScene::GameOverScene(Context* const ctx, const Controls& controls) : Scene(ctx), controls(controls) {}
GameOverScene::GameOverScene(Context* const ctx, const Controls& controls, DataTransmitter* datatransmitter)
    : Scene(ctx), controls(controls), datatransmitter_(datatransmitter) {}
