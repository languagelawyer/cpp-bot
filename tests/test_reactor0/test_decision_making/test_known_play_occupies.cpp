// A play Alice knows by touch makes her OCCUPIED (v23.31.0, the user's ruling;
// reactor0/DECISION_MAKING.md "Decision phase 1"; human diagnostic 2026856 T47).
// Occupied means she has something better to do than spend a token on a LOW clue,
// and a known play she can make is that. So below pace 3, where an unoccupied Alice
// may give any clue, an Alice with a known play is still held to HIGH, and plays.
// Without a known play the 2a window is unchanged.
#include <gtest/gtest.h>

#include <variant>

#include "hanabi/basics/action.h"
#include "hanabi/basics/card.h"
#include "hanabi/basics/game.h"
#include "hanabi/conventions/reactor0/decision.h"
#include "hanabi/conventions/reactor0/state_eval.h"
#include "test_harness.h"
#include "test_reactor0/test_reactor0_helpers.h"

using namespace hanabi;
using namespace hanabi::test;
using namespace hanabi::test::reactor0;
using hanabi::reactor0::ClueTier;

namespace {

Action rank_clue(const Game& g, int giver, int target, int value) {
  auto touched = g.state.clue_touched(g.state.hands[target], ClueKind::RANK, value);
  return Action{ClueAction{giver, target, std::move(touched),
                           BaseClue{ClueKind::RANK, value}}};
}

// The gate's verdict on one clue, built through `analyse_clues` as `take_action`
// builds it.
bool admissible(const Game& g, const Action& clue) {
  const auto& ca = std::get<ClueAction>(clue);
  PerformAction perform{PerformRank{ca.target, ca.clue.value}};
  auto cands = hanabi::reactor0::analyse_clues(g, {{perform, clue}});
  EXPECT_EQ(cands.size(), 1u) << "guard: the candidate survived analysis";
  if (cands.size() != 1) return false;
  EXPECT_EQ(cands.front().tier, ClueTier::LOW) << "guard: the clue is LOW";
  return hanabi::reactor0::clue_is_admissible(g, cands.front());
}

// Every hand inert (Bob's and Cathy's chops duplicated in their own hands), so a
// clue that gets no play is LOW. Pace 2 and 2 tokens: below 2a's window
// (`pace() >= 3`), inside 1a's (`pace() >= 1 && clue_tokens < 8`).
Game pace_two() {
  SetupOptions opts;
  opts.hands = {
      {"y1", "g1", "b1", "p1", "y5"},
      {"p4", "p4", "g4", "b4", "y4"},
      {"b3", "b3", "g3", "y3", "p3"},
  };
  opts.play_stacks = {0, 0, 0, 0, 0};
  opts.starting = TestPlayer::ALICE;
  opts.clue_tokens = 2;
  // Ten 1s (three copies each) and one r2 (two copies): pace 13 -> 2, max score kept.
  opts.discarded = {"r1", "r1", "y1", "y1", "g1", "g1", "b1", "b1", "p1", "p1", "r2"};
  use_reactor0(opts);
  return setup(std::move(opts));
}

}  // namespace

TEST(Reactor0KnownPlayOccupies, AKnownPlayHoldsALowClueBack) {
  Game g = pace_two();
  g = fully_known(std::move(g), TestPlayer::ALICE, /*slot=*/1, "y1");
  g.elim();
  ASSERT_EQ(g.state.pace(), 2) << "guard: pace 2";
  ASSERT_EQ(g.meta[order_at(g, TestPlayer::ALICE, 1)].status, CardStatus::NONE)
      << "guard: the y1 carries no stamp";

  EXPECT_TRUE(hanabi::reactor0::requires_high_tier(g)) << "the known y1 occupies her";
  EXPECT_FALSE(admissible(g, rank_clue(g, 0, 1, 4)))
      << "a LOW clue is not given over a play she can make";
}

TEST(Reactor0KnownPlayOccupies, WithoutAKnownPlayTheLowClueStillPasses) {
  Game g = pace_two();
  ASSERT_EQ(g.state.pace(), 2) << "guard: pace 2";

  EXPECT_FALSE(hanabi::reactor0::requires_high_tier(g)) << "nothing to play";
  EXPECT_TRUE(admissible(g, rank_clue(g, 0, 1, 4)))
      << "below pace 3 an unoccupied Alice may give any clue (2a)";
}
