//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_SCENES_SCENE_H_
#define INCLUDE_SCENES_SCENE_H_

#include <scenes/context.h>

class Scene {
 protected:
  Context* const ctx_;

 public:
  explicit Scene(Context* const ctx) : ctx_(ctx) {}

  virtual ~Scene() = default;

  virtual void OnCreate() = 0;

  virtual void OnRender() = 0;

  virtual void OnExit() = 0;
};

#endif  // INCLUDE_SCENES_SCENE_H_
