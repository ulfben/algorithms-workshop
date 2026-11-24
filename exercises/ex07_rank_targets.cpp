// Challenge 7: Rank and select lock-on targets
//
// The lock-on menu ranks all targets by distance from the player. Auto-lock
// selects just the closest target and returns its ID without reordering the
// roster. Both tasks break distance ties by ascending enemy ID. Enemy IDs
// are unique, and an empty roster gives auto-lock no target.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

struct Vec2 {
    float x;
    float y;
};

struct Enemy {
    int id;
    Vec2 position;
};

float distance_sq(Vec2 a, Vec2 b) {
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool ranks_before(const Enemy& left, const Enemy& right, Vec2 player) {
    const float leftDistance = distance_sq(left.position, player);
    const float rightDistance = distance_sq(right.position, player);
    if (leftDistance == rightDistance) {
        return left.id < right.id;
    }
    return leftDistance < rightDistance;
}

void sort_by_distance_to_player(std::vector<Enemy>& enemies, Vec2 player) {
    // TODO: Replace the nested loops with std::sort. Use a lambda that
    // captures the player position and calls ranks_before.
    // https://en.cppreference.com/cpp/algorithm/sort
	std::sort(enemies.begin(), enemies.end(), 
        [player](const Enemy& left, const Enemy& right) {
		    return ranks_before(left, right, player);
		});
}

std::optional<int> closest_target_id(const std::vector<Enemy>& enemies, Vec2 player) {
    // TODO: Use std::min_element with the same ranking rule. What iterator
    // does it return when there are no targets? end it
    // https://en.cppreference.com/cpp/algorithm/min_element
    // https://en.cppreference.com/cpp/utility/optional
    if (enemies.empty()) {
        return std::nullopt;
    }
	auto closest = std::min_element(enemies.begin(), enemies.end(),
		[player](const Enemy& left, const Enemy& right) {
			return ranks_before(left, right, player);
		});
    return closest->id;
}

TEST(SortByDistanceTest, RanksRelativeToPlayerAndBreaksTiesById) {
    std::vector<Enemy> enemies{
        {9, {0, 0}}, {8, {11, 0}}, {2, {9, 0}}, {5, {10, 0}}
    };
    sort_by_distance_to_player(enemies, {10, 0});

    ASSERT_EQ(enemies.size(), 4u);
    EXPECT_EQ(enemies[0].id, 5);
    EXPECT_EQ(enemies[1].id, 2);
    EXPECT_EQ(enemies[2].id, 8);
    EXPECT_EQ(enemies[3].id, 9);
}

TEST(SortByDistanceTest, EmptyAndSingleTargetAreValid) {
    std::vector<Enemy> enemies;
    sort_by_distance_to_player(enemies, {10, 0});
    EXPECT_TRUE(enemies.empty());

    enemies.push_back({5, {10, 2}});
    sort_by_distance_to_player(enemies, {10, 0});
    ASSERT_EQ(enemies.size(), 1u);
    EXPECT_EQ(enemies.front().id, 5);
}

TEST(ClosestTargetTest, FindsTheClosestTargetRelativeToThePlayer) {
    const std::vector<Enemy> enemies{{7, {0, 0}}, {3, {12, 0}}, {9, {11, 0}}};
    const auto target = closest_target_id(enemies, {10, 0});
    ASSERT_TRUE(target.has_value());
    EXPECT_EQ(*target, 9);
}

TEST(ClosestTargetTest, BreaksDistanceTiesByLowestId) {
    const std::vector<Enemy> enemies{{8, {11, 0}}, {2, {9, 0}}};
    const auto target = closest_target_id(enemies, {10, 0});
    ASSERT_TRUE(target.has_value());
    EXPECT_EQ(*target, 2);
}

TEST(ClosestTargetTest, EmptyRosterGivesNoTarget) {
    const std::vector<Enemy> enemies;
    EXPECT_FALSE(closest_target_id(enemies, {10, 0}).has_value());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
