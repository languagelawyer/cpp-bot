// Forced endgame Rule 7 — "the seat after next needs two turns, one card left"
// (reactor0 and Throw It in a Hole; the user's ruling, self-play 9000170 T58,
// human_vs_bot_diagnostics/9000170_23_33.md).
//
// Three players, ONE card left, two clue tokens. The max score needs Cathy to play,
// then Bob, then Cathy again:
//
//   CP acts   -> CP draws the last card. Final round is Bob, Cathy, CP: Cathy gets
//                ONE turn, so her second card never plays.
//   CP stalls -> Bob stalls too, Cathy plays and draws the last card, and the final
//                round is CP, Bob, Cathy: Bob's card goes down between her two.
//
// So CP must stall. Rule 6 is the same schedule at two cards left and no token.
#include <gtest/gtest.h>

#include <variant>

#include "hanabi/basics/action.h"
#include "hanabi/basics/convention.h"
#include "hanabi/basics/game.h"
#include "hanabi/basics/identity.h"
#include "hanabi/basics/state.h"
#include "hanabi/endgame/forced_endgame.h"
#include "test_harness.h"

using namespace hanabi;
using namespace hanabi::test;

namespace {

Game with_cards_left(Game g, int n) {
  g.state.cards_left = n;
  return g;
}

// Every stack on 5 but red, on 2: the max score needs r3, r4, r5. Cathy holds the r3
// and the r5, Bob the r4, and everything else is trash.
SetupOptions base(Convention convention = Convention::REACTOR0) {
  SetupOptions opts;
  opts.variant_name = "No Variant";
  opts.starting = TestPlayer::ALICE;
  opts.play_stacks = {2, 5, 5, 5, 5};
  opts.clue_tokens = 2;
  opts.hands = {
      {"y1", "g1", "b1", "p1", "y2"},   // Alice (CP): all trash
      {"r4", "y3", "g3", "b3", "p3"},   // Bob: the r4
      {"r3", "r5", "y4", "g4", "b4"},   // Cathy: the r3 and the r5
  };
  opts.init = [convention](Game& game) { game.convention = convention; };
  return opts;
}

bool action_is_clue(const PerformAction& a) {
  return std::holds_alternative<PerformColour>(a) ||
         std::holds_alternative<PerformRank>(a);
}

}  // namespace

TEST(ForcedEndgameRuleSeven, FiresWhenTheSeatAfterNextNeedsTwoTurns) {
  Game g = with_cards_left(setup(base()), 1);
  EXPECT_TRUE(hanabi::endgame::stall_for_two_turns_one_card(g, g.state.our_player_index));
  auto forced = hanabi::endgame::forced_endgame_action(g);
  ASSERT_TRUE(forced.has_value());
  EXPECT_TRUE(action_is_clue(*forced)) << "Alice stalls: drawing now strands the r5";
}

TEST(ForcedEndgameRuleSeven, DeclinesWithOneToken) {
  SetupOptions opts = base();
  opts.clue_tokens = 1;
  Game g = with_cards_left(setup(opts), 1);
  EXPECT_FALSE(hanabi::endgame::stall_for_two_turns_one_card(g, g.state.our_player_index))
      << "Bob could not stall after us";
}

TEST(ForcedEndgameRuleSeven, DeclinesWhenDrawingNowStillWins) {
  SetupOptions opts = base();
  opts.play_stacks = {3, 5, 5, 5, 5};
  opts.hands = {
      {"y1", "g1", "b1", "p1", "y2"},
      {"r4", "y3", "g3", "b3", "p3"},   // Bob: the r4
      {"r5", "r1", "y4", "g4", "b4"},   // Cathy: the r5, after him
  };
  Game g = with_cards_left(setup(opts), 1);
  EXPECT_FALSE(hanabi::endgame::stall_for_two_turns_one_card(g, g.state.our_player_index))
      << "Bob then Cathy in the final round lays both";
}

TEST(ForcedEndgameRuleSeven, DeclinesWithTwoCardsLeft) {
  Game g = with_cards_left(setup(base()), 2);
  EXPECT_FALSE(hanabi::endgame::stall_for_two_turns_one_card(g, g.state.our_player_index));
}

TEST(ForcedEndgameRuleSeven, DeclinesUnderReactor) {
  Game g = with_cards_left(setup(base(Convention::REACTOR)), 1);
  EXPECT_FALSE(hanabi::endgame::stall_for_two_turns_one_card(g, g.state.our_player_index))
      << "a reactor0 and Throw It in a Hole rule";
}
