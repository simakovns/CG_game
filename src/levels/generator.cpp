//
// Created by simakov on 15.08.2020.
//

#include <levels/generator.h>
#include <mathutils/leaf.h>
#include <mathutils/rand.h>

#include <map>
#include <vector>

void Generate() {
  RandomCreator Gen;
  const int MAX_LEAF_SIZE = 40;

  int counter = 1;

  int w = 100;
  int h = 30;

  std::map<int, Leaf *> array;
  array.emplace(counter, new Leaf(0, 0, w, h));
  counter++;

  std::cout << "map created" << std::endl;

  char arr[w][h];
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      arr[i][j] = '.';
    }
  }

  bool did_split = true;
  while (did_split) {
    did_split = false;
    for (auto &L : array) {
      if ((L.second->leftleaf == nullptr) && (L.second->rightleaf == nullptr)) {
        if (L.second->width_ > MAX_LEAF_SIZE || L.second->height_ > MAX_LEAF_SIZE || Gen.Get_double_0_1() > 0.25) {
          if (L.second->split()) {
            array.emplace(counter, L.second->leftleaf);
            counter++;
            array.emplace(counter, L.second->rightleaf);
            counter++;
            did_split = true;
          }
        }
      }
    }
  }
  std::cout << "leafs created" << std::endl;
  array[1]->createRooms();
  std::cout << "rooms & halls created" << std::endl;

  for (auto &R : array) {
    for (int x = R.second->room.x_; x <= R.second->room.x_ + R.second->room.width_; ++x)
      for (int y = R.second->room.y_; y <= R.second->room.y_ + R.second->room.height_; ++y) {
        arr[x][y] = '#';
      }

    for (auto &L : R.second->halls) {
      for (int x = L.x_; x <= L.x_ + L.width_; ++x)
        for (int y = L.y_; y <= L.y_ + L.height_; ++y) {
          arr[x][y] = '#';
        }
    }
  }

  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (arr[i][j] == '.') {
        arr[i][j] = '#';
      } else {
        arr[i][j] = '.';
        if (Gen.Get_double_0_1() < 0.03) {
          arr[i][j] = '$';
        }
      }
    }
  }

  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (arr[i][j] == '.') {
        if (Gen.Get_double_0_1() < 0.002) {
          arr[i][j] = 'p';
        }
      }
    }
  }
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (arr[i][j] == '.') {
        if (Gen.Get_double_0_1() < 0.002) {
          arr[i][j] = 'k';
        }
      }
    }
  }
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (arr[i][j] == '.') {
        if (Gen.Get_double_0_1() < 0.002) {
          arr[i][j] = 'X';
        }
      }
    }
  }
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (arr[i][j] == '.') {
        if (Gen.Get_double_0_1() < 0.01) {
          arr[i][j] = 'E';
        }
      }
    }
  }
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if (arr[i][j] == '.') {
        if (Gen.Get_double_0_1() < 0.01) {
          arr[i][j] = 'G';
        }
      }
    }
  }
  int count_of_doors = 0;
  for (int i = 0; i < w; ++i) {
    for (int j = 0; j < h; ++j) {
      if ((arr[i][j] == '#') && (arr[i + 1][j] == '.') && (arr[i][j - 1] == '#') && (arr[i][j + 1] == '#') &&
          (arr[i + 1][j - 1] == '.')) {
        arr[i][j] = '<';
        count_of_doors = 1;
        break;
      }
      if (count_of_doors == 1) {
        break;
      }
    }
  }

  for (int i = w; i > 0; --i) {
    for (int j = h; j > 0; --j) {
      if (arr[i][j] == '#' && arr[i][j - 1] == '#' && arr[i][j + 1] == '#' && arr[i - 1][j] == '.' &&
          arr[i - 1][j - 1] == '.' && arr[i + 1][j] == '#' && arr[i - 1][j + 1] == '.') {
        arr[i][j] = '>';
        count_of_doors = 2;
        break;
      }
      if (count_of_doors == 2) {
        break;
      }
    }
  }

  arr[0][0] = '#';

  std::ofstream out("resources/levels/generated_level.dat", std::ios_base::trunc);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      out << arr[j][i];
    }
    out << std::endl;
  }
  out.close();

  std::cout << "exit cycle" << std::endl;
}
