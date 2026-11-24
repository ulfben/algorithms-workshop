// Challenge 3: Ask three questions about a map row
//
// The level editor previews a walking route across a row. The route must
// have at least one tile, and every tile must be floor. A separate warning
// detects any lava. The geometry overlay asks whether the row contains no
// walls, which is true for an empty row. Each query reads the same row.

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <span>

enum class TileType {
    Floor,
    Wall,
    Lava,
};

// The three queries take a std::span by value.
// https://en.cppreference.com/cpp/container/span
//
// std::all_of, std::any_of and std::none_of share a reference page.
// https://en.cppreference.com/cpp/algorithm/all_any_none_of
bool is_row_walkable(std::span<const TileType> row) {
    // TODO: Use std::all_of to check each tile. Keep the nonempty rule.
    if (row.empty()) {
        return false;
    }
    return std::all_of(row.begin(), row.end(), 
        [](TileType tile) { 
            return tile == TileType::Floor; 
        });
}

bool has_lava(std::span<const TileType> row) {
    // TODO: Use std::any_of. The lambda should recognise one lava tile.
    return std::any_of(row.begin(), row.end(), [](TileType tile) { return tile == TileType::Lava; });
}

bool is_row_wall_free(std::span<const TileType> row) {
    // TODO: Use std::none_of. The lambda should recognise one wall tile.
    return std::none_of(row.begin(), row.end(), [](TileType tile) { return tile == TileType::Wall; });
}

TEST(MapRowTest, EmptyRowHasNoRouteLavaOrWalls) {
    const std::array<TileType, 0> row{};
    EXPECT_FALSE(is_row_walkable(row));
    EXPECT_FALSE(has_lava(row));
    EXPECT_TRUE(is_row_wall_free(row));
}

TEST(MapRowTest, AllFloorIsWalkable) {
    const std::array row{TileType::Floor, TileType::Floor};
    EXPECT_TRUE(is_row_walkable(row));
    EXPECT_FALSE(has_lava(row));
    EXPECT_TRUE(is_row_wall_free(row));
}

TEST(MapRowTest, LavaBlocksWalkingWithoutAddingAWall) {
    const std::array row{TileType::Floor, TileType::Lava, TileType::Floor};
    EXPECT_FALSE(is_row_walkable(row));
    EXPECT_TRUE(has_lava(row));
    EXPECT_TRUE(is_row_wall_free(row));
}

TEST(MapRowTest, AWallBlocksWalkingWithoutAddingLava) {
    const std::array row{TileType::Floor, TileType::Wall, TileType::Floor};
    EXPECT_FALSE(is_row_walkable(row));
    EXPECT_FALSE(has_lava(row));
    EXPECT_FALSE(is_row_wall_free(row));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
