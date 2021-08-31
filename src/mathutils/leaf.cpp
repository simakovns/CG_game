//
// Created by simakov on 15.08.2020.
//

#include <mathutils/leaf.h>
#include <mathutils/rand.h>

bool Leaf::split() {
  RandomCreator Gen;
  if (leftleaf != nullptr || rightleaf != nullptr) {
    return false;
  }

  bool splitH = Gen.Get_double_0_1() < 0.5;
  if (width_ > height_ && width_ / height_ >= 1.25) {
    splitH = false;
  } else if (width_ > height_ && height_ / width_ >= 1.25) {
    splitH = true;
  }

  int max = (splitH ? height_ : width_) - MIN_LEAF_SIZE;
  if (max <= MIN_LEAF_SIZE) {
    return false;
  }

  int split = Gen.Get_random_int(MIN_LEAF_SIZE, max);
  if (splitH) {
    leftleaf = new Leaf(x_, y_, width_, split);
    rightleaf = new Leaf(x_, y_ + split, width_, height_ - split);
  } else {
    leftleaf = new Leaf(x_, y_, split, height_);
    rightleaf = new Leaf(x_ + split, y_, width_ - split, height_);
  }
  return true;
}

void Leaf::createRooms() {
  RandomCreator Gen;
  if (leftleaf != nullptr || rightleaf != nullptr) {
    if (leftleaf != nullptr) {
      leftleaf->createRooms();
    }
    if (rightleaf != nullptr) {
      rightleaf->createRooms();
    }

    if (leftleaf != nullptr && rightleaf != nullptr) {
      CreateHall(leftleaf->GetRoom(), rightleaf->GetRoom());
    }
  } else {
    int roomsize_x = Gen.Get_random_int(7, width_ - 2);
    int roomsize_y = Gen.Get_random_int(7, height_ - 2);

    int roompos_x = Gen.Get_random_int(1, width_ - roomsize_x - 1);
    int roompos_y = Gen.Get_random_int(1, height_ - roomsize_y - 1);
    rect_x = x_ + roompos_x;
    rect_y = y_ + roompos_y;
    rect_width = roomsize_x;
    rect_height = roomsize_y;
    room = Rectangle(rect_x, rect_y, rect_width, rect_height);
    std::cout << "room created " << std::endl;
  }
}

Rectangle Leaf::GetRoom() {
  RandomCreator Gen;
  if (room != null_room) {
    return room;
  } else {
    Rectangle leftroom;
    Rectangle rightroom;
    if (leftleaf != nullptr) {
      leftroom = leftleaf->GetRoom();
    }
    if (rightleaf != nullptr) {
      rightroom = rightleaf->GetRoom();
    }
    if (leftroom == null_room && rightroom == null_room) {
      return null_room;
    } else if (rightroom == null_room) {
      return rightroom;
    } else if (leftroom == null_room) {
      return leftroom;
    } else if (Gen.Get_double_0_1() > 0.5) {
      return leftroom;
    } else {
      return rightroom;
    }
  }
}

void Leaf::CreateHall(Rectangle l, Rectangle r) {
  RandomCreator Gen;
  int point_1_x = Gen.Get_random_int(l.x_ + 1, l.x_ + l.width_ - 2);
  int point_1_y = Gen.Get_random_int(l.y_, l.y_ + l.height_ - 2);

  int point_2_x = Gen.Get_random_int(r.x_ + 1, r.x_ + r.width_ - 2);
  int point_2_y = Gen.Get_random_int(r.y_, r.y_ + r.height_ - 2);

  int width = point_2_x - point_1_x;
  int height = point_2_y - point_1_y;

  int wide = 2;

  if (width < 0) {
    if (height < 0) {
      if (Gen.Get_double_0_1() < 0.5) {
        halls.push_back(Rectangle(point_2_x, point_1_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_2_x, point_2_y, wide, std::abs(height)));
      } else {
        halls.push_back(Rectangle(point_2_x, point_2_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_1_x, point_2_y, wide, std::abs(height)));
      }
    } else if (height > 0) {
      if (Gen.Get_double_0_1() < 0.5) {
        halls.push_back(Rectangle(point_2_x, point_1_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_2_x, point_1_y, wide, std::abs(height)));
      } else {
        halls.push_back(Rectangle(point_2_x, point_2_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_1_x, point_1_y, wide, std::abs(height)));
      }
    } else {  // height == 0
      halls.push_back(Rectangle(point_2_x, point_2_y, std::abs(width), wide));
    }
  } else if (width > 0) {
    if (height < 0) {
      if (Gen.Get_double_0_1() < 0.5) {
        halls.push_back(Rectangle(point_1_x, point_2_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_1_x, point_2_y, wide, std::abs(height)));
      } else {
        halls.push_back(Rectangle(point_1_x, point_1_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_2_x, point_2_y, wide, std::abs(height)));
      }
    } else if (height > 0) {
      if (Gen.Get_double_0_1() < 0.5) {
        halls.push_back(Rectangle(point_1_x, point_1_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_2_x, point_1_y, wide, std::abs(height)));
      } else {
        halls.push_back(Rectangle(point_1_x, point_2_y, std::abs(width), wide));
        halls.push_back(Rectangle(point_1_x, point_1_y, wide, std::abs(height)));
      }
    } else {  // height == 0
      halls.push_back(Rectangle(point_1_x, point_1_y, std::abs(width), wide));
    }
  } else {  // width == 0
    if (height < 0) {
      halls.push_back(Rectangle(point_2_x, point_2_y, wide, std::abs(height)));
    } else if (height > 0) {
      halls.push_back(Rectangle(point_1_x, point_1_y, wide, std::abs(height)));
    }
  }
}

Leaf::Leaf(int x, int y, int width, int height) : x_(x), y_(y), width_(width), height_(height) {
  leftleaf = nullptr;
  rightleaf = nullptr;
  std::cout << "new life is born" << std::endl;
}
