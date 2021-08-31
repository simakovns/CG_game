# "Rogue-like" game

Roguelike game. Graphical part realized with [BearLibTerminal](http://foo.wyrd.name/ru:bearlibterminal). 
[This](https://github.com/senior-sigan/WHY_CPP_arkanoid) realization of the ECS pattern is used in project.

## Dependencies

g++, make, cmake, python 2.7 are necessary.

## How to launch

Use `make` in the terminal for:
1. Cleaning project (`make clean`)
2. initializing cmake (`make reload`)
3. Compiling sources (`make build`)
4. Executing the application (`make exec`)

## Structure

- `src` - cpp sources of the application
- `include` - .h headers
- `lib` - all of the necessary libraries
- `CMake`- scripts for cmake
- `CMakeLists.txt` - the main script for building the app
- `Makefile` - helpful scripts for building and launching the app
- `.clang-format` - code style describe
- `.editorconfig` - tabs configure for IDE

## Key feachures

- Choose from 3 characters with unique stats and skills.
- Each character can use unique skill (`u` button)
- There are keys and chests on the map. Use key to open the chest.
- Player may gather healing potions and use it if necessary (`h` button).

