// Challenge 2: Count enemies with an active poison effect
//
// A debug HUD shows how many enemies in the supplied roster have a poison
// effect. Count enemies with the flag set, regardless of their remaining HP.
// The roster is small enough for the count to fit in an int.

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

struct Enemy {
    int hp;
    bool poisoned;
};

int count_poisoned(const std::vector<Enemy>& enemies) {
    // TODO: Use std::count_if with a lambda that checks the poison flag.
    // https://en.cppreference.com/cpp/algorithm/count
    return (int) std::count_if(enemies.begin(), enemies.end(), 
        [](const Enemy& e) { 
            return e.poisoned; 
        });
}

TEST(CountPoisonedTest, EmptyRosterAndNoPoisonGiveZero) {
    const std::vector<Enemy> emptyRoster;
    const std::vector<Enemy> healthyRoster{{10, false}, {20, false}};
    EXPECT_EQ(count_poisoned(emptyRoster), 0);
    EXPECT_EQ(count_poisoned(healthyRoster), 0);
}

TEST(CountPoisonedTest, CountsTheFlagRegardlessOfHp) {
    const std::vector<Enemy> enemies{{0, true}, {1, false}, {100, true}};
    EXPECT_EQ(count_poisoned(enemies), 2);
}

TEST(CountPoisonedTest, CountsEveryMatch) {
    const std::vector<Enemy> enemies{{10, true}, {20, true}, {30, true}};
    EXPECT_EQ(count_poisoned(enemies), 3);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
