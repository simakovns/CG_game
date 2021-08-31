//
// Created by simakov on 17.07.2020.
//

#ifndef INCLUDE_SYSTEMS_RENDERING_SYSTEM_H_
#define INCLUDE_SYSTEMS_RENDERING_SYSTEM_H_

#include <levels/char_file_reader.h>
#include <systems/data_transmitter.h>

#include <string>

#include "ecs/system.h"

class RenderingSystem : public ISystem {
  DataTransmitter* datatransmitter_;
  int number_of_level_;

 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;
  void PrintEntities(const int& x_1, const int& x_2, const int& y_1, const int& y_2, const int& box_x_size,
                     const int& box_y_size);
  void RenderBorders(const int& x_1, const int& x_2, const int& y_1, const int& y_2);
  void RenderSpriteBorders(const int& x_1, const int& x_2, const int& y_1, const int& y_2);
  void RenderBackgroundOnFirstLevel(const int& x_1, const int& x_2, const int& y_1, const int& y_2,
                                    const int& box_x_size, const int& box_y_size, const int& sprite);
  void RenderBackground(const int& x_1, const int& x_2, const int& y_1, const int& y_2, const int& sprite);
  void RenderInterface(const std::string& character_name, const int& box_x_size);
  void RenderInterfaceSprites(const int& x_1, const int& x_2, const int& y_1, const int& y_2);
  void RenderCharacter(const std::string& character_name, const int& box_x_size);
  void RenderWindow(const int& x_1, const int& x_2, const int& y_1, const int& y_2);
  std::string GetColoredSymbol(const std::string& color, const char& symbol);

 public:
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order);
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, int loading_order,
                  DataTransmitter* datatransmitter);
  RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager, int loading_order,
                  DataTransmitter* datatransmitter, int number_of_level);
};

#endif  // INCLUDE_SYSTEMS_RENDERING_SYSTEM_H_
