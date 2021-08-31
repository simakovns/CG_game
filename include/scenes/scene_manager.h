//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_SCENES_SCENE_MANAGER_H_
#define INCLUDE_SCENES_SCENE_MANAGER_H_

#include <scenes/context.h>
#include <scenes/scene.h>

#include <map>
#include <memory>
#include <string>

class SceneManager {
  std::map<std::string, std::unique_ptr<Scene>> scenes_;
  const Context& ctx_;
  std::string current_scene_ = "";

 public:
  explicit SceneManager(const Context& ctx) : ctx_(ctx) {}

  std::string GetCurrentScene() const {
    return current_scene_;
  }

  void OnRender() {
    if (ctx_.scene_ != current_scene_) {
      std::cout << "Transition from '" << ctx_.scene_ << "' to '" << current_scene_ << "'" << std::endl;
      if (scenes_.count(current_scene_) != 0) {
        scenes_.at(current_scene_)->OnExit();
      }
      current_scene_ = ctx_.scene_;
      scenes_.at(current_scene_)->OnCreate();
    }
    if (scenes_.count(current_scene_) != 0) {
      scenes_.at(current_scene_)->OnRender();
    } else {
      std::cout << "[WARNING] Cannot update scene_ '" << current_scene_ << "': it doesn't exist." << std::endl;
    }
  }
  void OnExit() const {
    if (scenes_.count(current_scene_) != 0) {
      scenes_.at(current_scene_)->OnExit();
    }
  }

  void Put(const std::string& name, Scene* scene) {
    scenes_[name] = std::unique_ptr<Scene>(scene);
  }
};

#endif  // INCLUDE_SCENES_SCENE_MANAGER_H_
