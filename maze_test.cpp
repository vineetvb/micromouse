// For now, include gtest.h before other files dues to this issue https://github.com/google/googletest/issues/371
#include "gtest/gtest.h"

#include "maze.h"

#include <iostream>

TEST(MazeTest, ConstructStandardMazeCheckSize) {
    constexpr int maze_size = 10;
    Maze maze(maze_size);
    ASSERT_TRUE(maze.getSize() == maze_size);
}
