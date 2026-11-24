// Challenge 11: Shuffle a deck at the start of a match
//
// The match owns its random engine so it can use a fixed seed for replay
// and tests. Use that engine to shuffle this deck in place. Preserve every
// card, including repeats. An unchanged order is a possible shuffle result.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <random>
#include <utility>
#include <vector>

enum class Card {
    Move,
    Guard,
    Draw,
    Swap
};

// std::mt19937 is the random engine supplied by the caller.
// https://en.cppreference.com/cpp/numeric/random/mersenne_twister_engine
void shuffle_deck(std::vector<Card>& deck, std::mt19937& rng) {
    // TODO: Replace the manual shuffle with std::shuffle and pass the
    // supplied random engine.
    // https://en.cppreference.com/cpp/algorithm/random_shuffle
	std::shuffle(deck.begin(), deck.end(), rng);
}

TEST(ShuffleDeckTest, PreservesCardCountsIncludingDuplicates) {
    const std::vector<Card> original{
        Card::Move, Card::Guard, Card::Move, Card::Swap, Card::Draw, Card::Guard
    };
    auto deck = original;
    std::mt19937 rng{123};

    shuffle_deck(deck, rng);

    // https://en.cppreference.com/cpp/algorithm/is_permutation
    EXPECT_TRUE(std::is_permutation(
        deck.begin(), deck.end(), original.begin(), original.end()));
}

TEST(ShuffleDeckTest, UsesTheSuppliedEngineAndIsRepeatableWithTheSameSeed) {
    std::vector<Card> left{Card::Move, Card::Guard, Card::Draw, Card::Swap};
    auto right = left;
    const std::mt19937 initial{321};
    auto leftRng = initial;
    auto rightRng = initial;

    shuffle_deck(left, leftRng);
    shuffle_deck(right, rightRng);

    EXPECT_EQ(left, right);
    EXPECT_FALSE(leftRng == initial);
}

TEST(ShuffleDeckTest, EmptyAndSingleCardDecksKeepTheirContents) {
    std::mt19937 rng{123};
    std::vector<Card> deck;
    shuffle_deck(deck, rng);
    EXPECT_TRUE(deck.empty());

    deck.push_back(Card::Draw);
    shuffle_deck(deck, rng);
    EXPECT_EQ(deck, std::vector<Card>{Card::Draw});
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
