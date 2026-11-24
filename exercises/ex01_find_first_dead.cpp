// Challenge 1: Search a combat roster
//
// The HUD keeps its selected enemy IDs in selection order. Check whether an
// exact ID is selected. The respawn system scans the roster in spawn order.
// Return a copy of the first enemy with zero or negative HP, or no value.

#include <gtest/gtest.h>

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

struct Enemy {
    std::string name;
    int hp;
};

// Both search algorithms share a reference page.
// https://en.cppreference.com/cpp/algorithm/find
bool is_enemy_selected(const std::vector<int>& selectedIds, int id) {
    // TODO: Use std::find. What does it return when the ID is absent? end it
    return std::find(selectedIds.begin(), selectedIds.end(), id) != selectedIds.end();
}

// The result uses std::optional to represent a missing enemy.
// https://en.cppreference.com/cpp/utility/optional
std::optional<Enemy> find_first_dead(const std::vector<Enemy>& enemies) {
    // TODO: Use std::find_if and a lambda for the HP condition. Check for
    // end() before reading the result.
	auto it = std::find_if(enemies.begin(), enemies.end(), 
        [](const Enemy& e) { 
            return e.hp <= 0; 
        });

    if (it != enemies.end()) {
        return *it;
    }
    return std::nullopt;
}

TEST(SelectedEnemyTest, FindsAnExactIdInAnUnsortedSelection) {
    const std::vector<int> selectedIds{7, 42, 3};
    EXPECT_TRUE(is_enemy_selected(selectedIds, 42));
    EXPECT_FALSE(is_enemy_selected(selectedIds, 4));
}

TEST(SelectedEnemyTest, EmptySelectionHasNoMatch) {
    const std::vector<int> selectedIds;
    EXPECT_FALSE(is_enemy_selected(selectedIds, 42));
}

TEST(FindFirstDeadTest, EmptyRosterAndAllAliveGiveNoMatch) {
    const std::vector<Enemy> emptyRoster;
    const std::vector<Enemy> livingRoster{{"Slime", 10}, {"Orc", 1}};
    EXPECT_FALSE(find_first_dead(emptyRoster).has_value());
    EXPECT_FALSE(find_first_dead(livingRoster).has_value());
}

TEST(FindFirstDeadTest, KeepsTheFirstMatchIncludingZeroHp) {
    const std::vector<Enemy> enemies{
        {"Slime", 10}, {"Zombie", 0}, {"Orc", -5}, {"Dragon", 200}
    };
    const auto result = find_first_dead(enemies);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->name, "Zombie");
    EXPECT_EQ(result->hp, 0);
}

TEST(FindFirstDeadTest, FindsNegativeHpAtTheEnd) {
    const std::vector<Enemy> enemies{{"Slime", 1}, {"Orc", -5}};
    const auto result = find_first_dead(enemies);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->name, "Orc");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
