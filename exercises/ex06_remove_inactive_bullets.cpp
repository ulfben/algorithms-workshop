// Challenge 6: Clean up bullets after the update
//
// The game removes spent bullets and bullets beyond the playfield. A bullet
// on any boundary is still inside. Shrink the caller's vector and keep the
// surviving bullets in their original order.

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

struct Bullet {
    int id;
    float x;
    float y;
    bool alive;
};

void remove_inactive_bullets(std::vector<Bullet>& bullets, float width, float height) {
    // TODO: Use std::erase_if. Capture the dimensions in the predicate.
    // The predicate should identify the bullets to remove.
    // https://en.cppreference.com/cpp/container/vector/erase2
    std::erase_if(bullets, 
        [width, height](const Bullet& bullet){ 
            return  !bullet.alive || 
                bullet.x < 0 || bullet.x > width || bullet.y < 0 || bullet.y > height; 
        });
}

TEST(RemoveInactiveBulletsTest, KeepsBoundaryBulletsInOriginalOrder) {
    std::vector<Bullet> bullets{
        {9, -1, 5, true}, {4, 0, 0, true}, {8, 11, 5, true},
        {6, 5, -1, true}, {7, 8, 0, false}, {1, 10, 20, true},
        {2, 5, 21, true}
    };

    remove_inactive_bullets(bullets, 10, 20);

    ASSERT_EQ(bullets.size(), 2u);
    EXPECT_EQ(bullets[0].id, 4);
    EXPECT_EQ(bullets[1].id, 1);
}

TEST(RemoveInactiveBulletsTest, CanRemoveEveryBullet) {
    std::vector<Bullet> bullets{{1, 0, 0, false}, {2, 11, 0, true}};
    remove_inactive_bullets(bullets, 10, 20);
    EXPECT_TRUE(bullets.empty());
}

TEST(RemoveInactiveBulletsTest, EmptyPlayfieldNeedsNoCleanup) {
    std::vector<Bullet> bullets;
    remove_inactive_bullets(bullets, 10, 20);
    EXPECT_TRUE(bullets.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
