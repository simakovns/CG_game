//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_COMPONENTS_TEXTURE_COMPONENT_H_
#define INCLUDE_COMPONENTS_TEXTURE_COMPONENT_H_

#include <ecs/component.h>

#include <string>

class TextureComponent : public IComponent {
 public:
  char symbol_;
  std::string color_ = "white";
  int layer_ = 1;

  explicit TextureComponent(char symbol) : symbol_(symbol) {}
  TextureComponent(char symbol, std::string color) : symbol_(symbol), color_(color) {}
  TextureComponent(char symbol, std::string color, int layer) : symbol_(symbol), color_(color), layer_(layer) {}
};

#endif  // INCLUDE_COMPONENTS_TEXTURE_COMPONENT_H_
