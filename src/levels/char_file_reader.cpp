//
// Created by simakov on 06.08.2020.
//
#include <levels/char_file_reader.h>

#include <cassert>
#include <fstream>   //NOLINT
#include <string>
#include <vector>

void CharFileReader::InitializeResourceMatrix() {
  std::string name_of_file = resource_name_;
  std::ifstream file_of_resource(name_of_file);
  assert(file_of_resource.is_open());
  int row = 0, col;
  char element;
  std::string line;
  std::getline(file_of_resource, line);
  col = line.size();
  while (!file_of_resource.eof()) {
    std::getline(file_of_resource, line);
    ++row;
  }
  file_of_resource.clear();
  file_of_resource.seekg(0);
  resource_.resize(row);
  for (int row_ = 0; row_ < row; ++row_) {
    resource_[row_].resize(col);
    for (int col_ = 0; col_ < col; ++col_) {
      file_of_resource >> element;
      AddElement(row_, col_, element);
    }
  }
  file_of_resource.close();
}

void CharFileReader::Read() {
  InitializeResourceMatrix();
}

void CharFileReader::Read(const std::string &resource_name) {
  resource_name_ = resource_name;
  Read();
}
void CharFileReader::AddElement(int row, int col, char element) {
  resource_[row][col] = element;
}
std::vector<std::vector<char>> CharFileReader::GetResourceMatrix() const {
  return resource_;
}
