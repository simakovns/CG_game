//
// Created by simakov on 06.08.2020.
//

#ifndef INCLUDE_LEVELS_CHAR_FILE_READER_H_
#define INCLUDE_LEVELS_CHAR_FILE_READER_H_

#include <levels/file_reader.h>

#include <vector>
#include <string>

class CharFileReader : public FileReader {
  std::string resource_name_;
  std::vector<std::vector<char>> resource_;
 public:
  CharFileReader() = default;
  explicit CharFileReader(std::string resource_name) : resource_name_(resource_name) {}
  void Read() override;
  void Read(const std::string& resource_name);
  void AddElement(int row, int col, char element);
  void InitializeResourceMatrix();
  std::vector<std::vector<char>> GetResourceMatrix() const;
};

#endif  // INCLUDE_LEVELS_CHAR_FILE_READER_H_
