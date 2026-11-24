// Challenge 5: Apply an area effect and keep HP in range
//
// Apply an area effect to each enemy. Positive damage reduces HP and negative
// damage heals. Input HP is in [0, 100] and damage is in [-100, 100]. Keep
// each resulting HP in [0, 100]. Enemy IDs and order stay the same.

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

struct Enemy {
    int id;
    int hp;
};

void apply_damage(std::vector<Enemy>& enemies, int damagePerEnemy) {
    // TODO: Use std::clamp for the HP calculation. A range-based for is
    // sufficient for applying it to each enemy.
    // https://en.cppreference.com/cpp/algorithm/clamp
    for (Enemy& enemy : enemies) {
        enemy.hp -= damagePerEnemy;
		enemy.hp = std::clamp(enemy.hp, 0, 100);
    }
}

TEST(ApplyDamageTest, ReachesZeroAndClampsOverkill) {
    std::vector<Enemy> enemies{{8, 50}, {3, 20}, {9, 5}};
    apply_damage(enemies, 20);

    ASSERT_EQ(enemies.size(), 3u);
    EXPECT_EQ(enemies[0].hp, 30);
    EXPECT_EQ(enemies[1].hp, 0);
    EXPECT_EQ(enemies[2].hp, 0);
    EXPECT_EQ(enemies[0].id, 8);
    EXPECT_EQ(enemies[1].id, 3);
    EXPECT_EQ(enemies[2].id, 9);
}

TEST(ApplyDamageTest, NegativeDamageHealsUpToTheCap) {
    std::vector<Enemy> enemies{{1, 90}, {2, 80}, {3, 50}};
    apply_damage(enemies, -20);

    EXPECT_EQ(enemies[0].hp, 100);
    EXPECT_EQ(enemies[1].hp, 100);
    EXPECT_EQ(enemies[2].hp, 70);
}

TEST(ApplyDamageTest, ZeroDamageKeepsTheBoundaryValues) {
    std::vector<Enemy> enemies{{1, 0}, {2, 100}};
    apply_damage(enemies, 0);

    EXPECT_EQ(enemies[0].hp, 0);
    EXPECT_EQ(enemies[1].hp, 100);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
