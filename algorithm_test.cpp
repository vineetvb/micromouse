// For now, inlcude gtest.h before other files dues to this issue https://github.com/google/googletest/issues/371
#include "gtest/gtest.h"

#include "algorithm.h"

#include <iostream>

TEST(AlgorithmTest, IsAlwaysTrue) {
    ASSERT_TRUE(true);
}

