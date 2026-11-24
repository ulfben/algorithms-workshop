// Challenge 10: Select alerts and produce their labels
//
// The debug inspector has two independent actions. Select enemies strictly
// below an HP threshold to inspect their full data. Given a selection from
// any source, collect the name of each selected enemy for the label list.
// Both operations keep input order and return their own copy of the data.

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

struct Enemy {
    std::string name;
    int hp;

    bool operator==(const Enemy&) const = default;
};

// Both functions can append their output with std::back_inserter.
// https://en.cppreference.com/cpp/iterator/back_inserter
std::vector<Enemy> select_low_hp(const std::vector<Enemy>& enemies, int threshold) {
    // TODO: Use std::copy_if with a lambda that captures the threshold.
    // Append the matching records to the result with std::back_inserter.
    // https://en.cppreference.com/cpp/algorithm/copy

    std::vector<Enemy> result;
	std::copy_if(enemies.begin(), enemies.end(), std::back_inserter(result),
		[threshold](const Enemy& enemy) {
			return enemy.hp < threshold;
		});
    return result;
}

std::vector<std::string> enemy_names(const std::vector<Enemy>& selectedEnemies) {
    // TODO: Use std::transform to produce one name per enemy. A lambda
    // can select the name and std::back_inserter can append it.
    // https://en.cppreference.com/cpp/algorithm/transform
    std::vector<std::string> result;
    for (const Enemy& enemy : selectedEnemies) {
        result.push_back(enemy.name);
    }
    return result;
}

TEST(SelectLowHpTest, CopiesMatchingRecordsInInputOrder) {
    const std::vector<Enemy> enemies{
        {"Goblin", 30}, {"Orc", 50}, {"Slime", 10}, {"Dragon", 200}, {"Bat", 40}
    };
    const std::vector<Enemy> expected{{"Goblin", 30}, {"Slime", 10}, {"Bat", 40}};
    EXPECT_EQ(select_low_hp(enemies, 50), expected);
}

TEST(SelectLowHpTest, NoMatchesAndEmptyInputGiveEmptyResults) {
    const std::vector<Enemy> enemies{{"Orc", 50}, {"Dragon", 200}};
    const std::vector<Enemy> emptyRoster;
    EXPECT_TRUE(select_low_hp(enemies, 50).empty());
    EXPECT_TRUE(select_low_hp(emptyRoster, 50).empty());
}

TEST(EnemyNamesTest, KeepsEveryNameAndPreservesOrder) {
    const std::vector<Enemy> enemies{{"Bat", 10}, {"Orc", 200}, {"Bat", 30}};
    const std::vector<std::string> expected{"Bat", "Orc", "Bat"};
    EXPECT_EQ(enemy_names(enemies), expected);
}

TEST(EnemyNamesTest, EmptySelectionGivesNoLabels) {
    const std::vector<Enemy> enemies;
    EXPECT_TRUE(enemy_names(enemies).empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
