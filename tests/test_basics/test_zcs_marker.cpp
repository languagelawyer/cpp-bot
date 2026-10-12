// The zero-clue marker (reactor CONVENTION.md, `chop()`; v23.38.0, the user's
// ruling; human_vs_bot_diagnostics/2027922.md T27).
//
// A clue that takes the team to zero tokens sets `zcs_turn`, and `Game::chop`
// skips a card drawn after it. A player who begins his turn with a token clears
// the marker for every OTHER player, whether or not he acts; his own clears when
// someone else begins a turn with one.
#include <gtest/gtest.h>

#include <utility>

#include "hanabi/basics/card.h"
#include "hanabi/basics/game.h"
#include "test_harness.h"

using namespace hanabi;
using namespace hanabi::test;

namespace {

constexpr int kAlice = static_cast<int>(TestPlayer::ALICE);
constexpr int kBob = static_cast<int>(TestPlayer::BOB);
constexpr int kCathy = static_cast<int>(TestPlayer::CATHY);

// What the fixture's actions MEAN is not the subject here: a call they stamp (the 3
// reads as a discard call on Bob's p4) would decide `chop` ahead of the marker.
void clear_calls(Game& g) {
  for (const auto& hand : g.state.hands) {
    for (int o : hand) {
      g.with_meta(o, [](ConvData& m) { m.status = CardStatus::NONE; });
    }
  }
}

// Alice spends the last token; Bob plays his r1 and draws; Cathy discards, which
// brings a token back, and draws. Alice is about to begin her turn with it.
Game stall_then_a_token_back() {
  SetupOptions opts;
  opts.hands = {{"xx", "xx", "xx", "xx", "xx"},
                {"r1", "g4", "b3", "y3", "p4"},
                {"g3", "b4", "y4", "r3", "p3"}};
  opts.clue_tokens = 1;
  Game g = setup(std::move(opts));
  g = take_turn(std::move(g), "Alice clues 3 to Bob");
  g = take_turn(std::move(g), "Bob plays r1 (slot 1)", "y2");
  g = take_turn(std::move(g), "Cathy discards p3 (slot 5)", "g2");
  clear_calls(g);
  return g;
}

}  // namespace

TEST(ZeroClueMarker, ClearsForEveryoneButThePlayerBeginningWithAToken) {
  Game g = stall_then_a_token_back();
  ASSERT_EQ(g.state.clue_tokens, 1);
  ASSERT_NE(g.zcs_turn, -1) << "Alice's clue spent the last token";
  EXPECT_FALSE(g.zcs_gates(kBob)) << "Alice begins this turn with a token";
  EXPECT_FALSE(g.zcs_gates(kCathy)) << "Alice begins this turn with a token";
  EXPECT_TRUE(g.zcs_gates(kAlice)) << "Bob and Cathy began their turns with none";
  // Bob's y2 and Cathy's g2, drawn during the stall, are their chops again.
  const int bob_new = g.state.hands[kBob].front();
  EXPECT_EQ(g.chop(kBob), bob_new);
  const int cathy_new = g.state.hands[kCathy].front();
  EXPECT_EQ(g.chop(kCathy), cathy_new);
}

TEST(ZeroClueMarker, ResetsWhenTheNextPlayerBeginsWithAToken) {
  Game g = stall_then_a_token_back();
  g = take_turn(std::move(g), "Alice discards g1 (slot 5)", "r4");
  EXPECT_EQ(g.zcs_turn, -1) << "Bob begins his turn with a token: Alice's clears too";
  EXPECT_FALSE(g.zcs_gates(kAlice));
}
