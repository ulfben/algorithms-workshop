// Challenge 4: Total the weight carried by a player
//
// The inventory UI displays the player's carried weight in kilograms. Add
// the weight of every item, including repeated items. An empty inventory
// weighs zero. Item weights may contain fractions.

#include <gtest/gtest.h>

#include <numeric>
#include <vector>

struct Item {
    float weight;
};

float total_weight(const std::vector<Item>& items) {
    // TODO: Use std::accumulate with a lambda that adds one Item's weight
    // to the running total. The initial value determines the accumulator type.
    // https://en.cppreference.com/cpp/algorithm/accumulate
    return std::accumulate(items.begin(), items.end(), 0.0f, 
        [](float acc, const Item& item) { 
            return acc + item.weight; 
        });
}

TEST(TotalWeightTest, EmptyInventoryIsZero) {
    const std::vector<Item> items;
    EXPECT_FLOAT_EQ(total_weight(items), 0.0f);
}

TEST(TotalWeightTest, AddsFractionalWeightsIncludingRepeatItems) {
    const std::vector<Item> items{{1.25f}, {0.5f}, {1.25f}, {0.25f}};
    EXPECT_FLOAT_EQ(total_weight(items), 3.25f);
}

TEST(TotalWeightTest, CountsASingleItem) {
    const std::vector<Item> items{{0.75f}};
    EXPECT_FLOAT_EQ(total_weight(items), 0.75f);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
