cmake_minimum_required(VERSION 3.15)
project(Rastros_LI2 C)

set(CMAKE_C_STANDARD 11)
add_definitions(-DCONFIG_CTRL_IFACE)
add_executable(Rastros_LI2 main.c data/state.c data/state.h logic/game.c logic/game.h interface/interface.c interface/interface.h interface/board.c interface/board.h data/file.c data/file.h data/list_contents/OS_list.c data/list_contents/OS_list.h linked_lists/linked.c linked_lists/linked.h)