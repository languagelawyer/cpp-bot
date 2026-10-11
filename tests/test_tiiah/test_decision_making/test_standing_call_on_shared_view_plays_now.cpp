// A standing call that plays on the SHARED view is played now, when only our own
// unnamed hole cards hold our private stacks back (tiiah/CONVENTION.md §2k, v20.11.0,
// the user's ruling). The decision-level form of
// `test_standing_call_survives_and_plays.cpp`'s per-card tests.
//
// It replaces replay 2018874 T47 (v23.37.0). That game was played under the three-bucket
// convention v23.0.0 replaced, so under today's rules will-bot69 misread its own T7 card
// (the b1, read `{y3}`) and every view of its seat drifted from there; any reading change
// upstream moved the T47 position the replay pinned.
//
// The shape of 2018874 T47: will-bot69's o44 was stable-called `{b5}`, blue was on 4 on
// every shared view and on 3 on its own, and its unnamed hole card could have been the
// b4. Before v20.11.0 the `{b5}` was neither playable on its belief nor in every world
// of its own hole cards, and section 4 gave a stall instead.
#include <gtest/gtest.h>

#include <variant>
#include <vector>

#include "hanabi/basics/action.h"
#include "hanabi/basics/card.h"
#include "hanabi/basics/game.h"
#include "hanabi/basics/identity_set.h"
#include "test_harness.h"
#include "test_tiiah/test_tiiah_helpers.h"

using namespace hanabi;
using namespace hanabi::test;
using namespace hanabi::test::tiiah;

namespace {

// Alice holds a card clued blue and 5, called to play. Blue is on 3 on her own stacks
// and on 4 on the shared view; her first play went into the hole unnamed and could be
// the b4 the shared view counts. Neither partner holds a playable card, so no clue
// competes with the play. Not late: with few cards left §2m (v23.13.0) plays any
// called card in a thin endgame, which would hide this rule.
Game shared_view_call(bool shared_ahead) {
  SetupOptions opts;
  opts.variant_name = "Throw It in a Hole (5 Suits)";
  opts.hands = {
      {"xx", "xx", "xx", "xx", "xx"},
      {"g4", "y3", "p4", "r2", "r3"},
      {"b2", "y4", "g3", "p3", "r4"},
  };
  opts.play_stacks = std::vector<int>{0, 0, 0, 3, 0};
  opts.clue_tokens = 5;
  use_tiiah(opts);
  Game g = setup(std::move(opts));
  g = hidden_action(std::move(g), TestPlayer::ALICE, /*slot=*/5, /*reached_the_hole=*/true);
  if (shared_ahead) {
    g.with_state([](State& st) { st = st.with_common_floor({0, 0, 0, 4, 0}); });
  }
  g = pre_clue(std::move(g), TestPlayer::ALICE, 1, {"blue", "5"});
  const int ours = order_at(g, TestPlayer::ALICE, 1);
  g.with_meta(ours, [](ConvData& m) {
    m.status = CardStatus::CALLED_TO_PLAY;
    m.signal_turn = 1;
  });
  g.state.current_player_index = static_cast<int>(TestPlayer::ALICE);
  return g;
}

}  // namespace

TEST(TiiahStandingCallDecision, ACallPlayableOnTheSharedViewPlaysNow) {
  Game g = shared_view_call(/*shared_ahead=*/true);
  ASSERT_EQ(g.state.play_stacks[3], 3) << "guard: our own stacks lag";
  const int ours = order_at(g, TestPlayer::ALICE, 1);
  PerformAction action = g.take_action();
  const auto* play = std::get_if<PerformPlay>(&action);
  ASSERT_NE(play, nullptr) << "the called b5, not a section-4 stall";
  EXPECT_EQ(play->target, ours);
}

// The negatives -- a call unplayable on every view, a shared view ahead that no hole
// card of ours explains, our own view ahead -- are the per-card tests in
// `test_standing_call_survives_and_plays.cpp`: today a called card with nothing better
// to do is played anyway, so the decision does not separate them.
