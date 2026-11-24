// Challenge 8: Group AI updates by proximity
//
// An AI update processes nearby enemies first. Move every enemy at or
// inside the given radius to the front and return the size of that group.
// The input radius is nonnegative. Keep all enemies in the original vector.
// The relative order within either group can change.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

struct Vec2 {
    float x;
    float y;

    bool operator==(const Vec2&) const = default;
};

struct Enemy {
    int id;
    Vec2 position;

    bool operator==(const Enemy&) const = default;
};

float distance_sq(Vec2 a, Vec2 b) {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

std::size_t partition_near_enemies(std::vector<Enemy>& enemies, Vec2 player, float radius) {
    // TODO: Use std::partition with a lambda that captures the player and
    // squared radius. Convert the returned boundary to a count.
    // https://en.cppreference.com/cpp/algorithm/partition
    // For the count, see https://en.cppreference.com/cpp/iterator/distance
    const float radiusSquared = radius * radius;
    auto it = std::partition(enemies.begin(), enemies.end(),
		[player, radiusSquared](const Enemy& enemy) {
			return distance_sq(enemy.position, player) <= radiusSquared;
		});
	return (std::size_t)std::distance(enemies.begin(), it);
}

TEST(PartitionNearEnemiesTest, IncludesTheBoundaryAndPreservesAllEnemies) {
    const Vec2 player{10, 0};
    const std::vector<Enemy> original{
        {1, {0, 0}}, {2, {13, 4}}, {3, {30, 0}}, {4, {10, 1}}
    };
    auto enemies = original;

    ASSERT_EQ(partition_near_enemies(enemies, player, 5), 2u);
    ASSERT_EQ(enemies.size(), original.size());
    for (std::size_t i = 0; i < enemies.size(); ++i) {
        EXPECT_EQ(distance_sq(enemies[i].position, player) <= 25, i < 2);
    }
    // https://en.cppreference.com/cpp/algorithm/is_permutation
    EXPECT_TRUE(std::is_permutation(
        enemies.begin(), enemies.end(), original.begin(), original.end()));
}

TEST(PartitionNearEnemiesTest, HandlesEmptyAllFarAndAllNearGroups) {
    std::vector<Enemy> enemies;
    EXPECT_EQ(partition_near_enemies(enemies, {0, 0}, 1), 0u);
    EXPECT_TRUE(enemies.empty());

    enemies = {{1, {2, 0}}, {2, {3, 0}}};
    EXPECT_EQ(partition_near_enemies(enemies, {0, 0}, 1), 0u);
    EXPECT_EQ(partition_near_enemies(enemies, {0, 0}, 3), 2u);
    EXPECT_EQ(enemies.size(), 2u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
