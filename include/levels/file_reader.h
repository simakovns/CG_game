//
// Created by simakov on 25.07.2020.
//

#ifndef INCLUDE_LEVELS_FILE_READER_H_
#define INCLUDE_LEVELS_FILE_READER_H_

#include <levels/reader.h>
#include <vector>

class FileReader : IReader{
 public:
  void Read() override = 0;
  ~FileReader() override = default;
};

#endif  // INCLUDE_LEVELS_FILE_READER_H_
