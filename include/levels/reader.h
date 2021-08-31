//
// Created by simakov on 25.07.2020.
//

#ifndef INCLUDE_LEVELS_READER_H_
#define INCLUDE_LEVELS_READER_H_

#include <vector>

class IReader {
 public:
  virtual void Read() = 0;
  virtual ~IReader() = default;
};

#endif  // INCLUDE_LEVELS_READER_H_
