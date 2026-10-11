// The stack invariant (v23.34.0, the user's rule; human_vs_bot_diagnostics/2027454.md
// T46): no stack view of a seat stands at or past a card none of whose copies can
// have been played -- every copy is in the discard pile or in a hand the seat can
// see. `stacks_past_unplayed_in_sight` is asked directly here, on views forced past
// such a card; the engine itself never writes them.
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "hanabi/basics/game.h"
#include "hanabi/basics/identity.h"
#include "hanabi/basics/stack_invariant.h"
#include "test_harness.h"

using namespace hanabi;
using namespace hanabi::test;

namespace {

// Alice is us. Bob holds the r5, the only copy, and a g3; Cathy the other g3 and one
// b3, whose twin nobody can see.
Game tiiah_game() {
  SetupOptions opts;
  opts.variant_name = "Throw It in a Hole (5 Suits)";
  opts.hands = {
      {"xx", "xx", "xx", "xx", "xx"},
      {"r5", "g3", "y1", "y1", "p1"},
      {"g3", "b3", "y2", "p2", "p2"},
  };
  return setup(std::move(opts));
}

bool reported(const std::vector<StackViolation>& v, const std::string& view, int seat,
              Identity id) {
  return std::any_of(v.begin(), v.end(), [&](const StackViolation& x) {
    return x.view == view && x.view_seat == seat && x.id == id;
  });
}

}  // namespace

TEST(StackInvariant, NothingPastAnythingAtTheStart) {
  Game g = tiiah_game();
  EXPECT_TRUE(stacks_past_unplayed_in_sight(g).empty());
}

// The user's case: a critical card in a partner's hand. Every view of ours is held
// to it.
TEST(StackInvariant, AViewAtACriticalCardInSightIsReported) {
  Game g = tiiah_game();
  g.state.common_play_stacks[0] = 5;
  const auto v = stacks_past_unplayed_in_sight(g);
  EXPECT_TRUE(reported(v, "common", -1, Identity(0, 5)));
  EXPECT_FALSE(reported(v, "private", -1, Identity(0, 5))) << "our own red is still 0";
  g.state.play_stacks[0] = 5;
  EXPECT_TRUE(reported(stacks_past_unplayed_in_sight(g), "private", -1, Identity(0, 5)));
}

// Not critical, but both copies are in partners' hands, so neither is on the stack:
// replay 2027454 T41's pair rows, which took a g3 with both in view.
TEST(StackInvariant, APairRowPastBothCopiesInHandsIsReported) {
  Game g = tiiah_game();
  g.state.pairwise_play_stacks[2][2] = 3;
  const auto v = stacks_past_unplayed_in_sight(g);
  EXPECT_TRUE(reported(v, "pair", 2, Identity(2, 3)));
  EXPECT_EQ(v.size(), 1u);
}

// A copy we cannot see may be the one on the stack: nothing to report.
TEST(StackInvariant, ACopyOutOfSightMayHaveLanded) {
  Game g = tiiah_game();
  g.state.play_stacks[3] = 3;
  g.state.common_play_stacks[3] = 3;
  EXPECT_TRUE(stacks_past_unplayed_in_sight(g).empty());
}

// A reversed suit counts down from 6: a stack of 4 has the 4 down, a stack of 5 has
// not.
TEST(StackInvariant, AReversedSuitIsHeldTheReversedWay) {
  SetupOptions opts;
  opts.variant_name = "Reversed (5 Suits)";  // purple reversed at index 4
  opts.hands = {
      {"xx", "xx", "xx", "xx", "xx"},
      {"r1", "y1", "g1", "b1", "r2"},
      {"r1", "y1", "g1", "b1", "y2"},
  };
  Game g = setup(std::move(opts));
  // Both copies of the reversed 4 are in partners' hands.
  g.state.deck[g.state.hands[1][0]].suit_index = 4;
  g.state.deck[g.state.hands[1][0]].rank = 4;
  g.state.deck[g.state.hands[2][0]].suit_index = 4;
  g.state.deck[g.state.hands[2][0]].rank = 4;
  g.state.play_stacks[4] = 5;
  EXPECT_TRUE(stacks_past_unplayed_in_sight(g).empty()) << "only the 5 is down";
  g.state.play_stacks[4] = 4;
  EXPECT_TRUE(reported(stacks_past_unplayed_in_sight(g), "private", -1, Identity(4, 4)));
}
