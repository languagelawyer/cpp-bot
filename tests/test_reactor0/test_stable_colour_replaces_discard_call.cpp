// A stable colour clue may call to play a card already called to DISCARD, and the
// play call replaces the discard call at every seat, the receiver's own included
// (reactor0/CONVENTION.md §1b priority 5, v23.30.0, the user's ruling; replay 2026832
// T7-T11). Until v23.30.0 a CTD'd target had to be VISIBLY playable, a test of the
// deck the receiver cannot make on its own card: every other seat read the play, and
// the receiver kept its discard call.
#include <gtest/gtest.h>

#include "hanabi/basics/game.h"
#include "test_reactor0/test_reactor0_helpers.h"

using namespace hanabi;
using namespace hanabi::test;
using namespace hanabi::test::reactor0;

namespace {

void call_to_discard(Game& g, TestPlayer player, int slot) {
  const int o = order_at(g, player, slot);
  g.with_meta(o, [](ConvData& m) {
    m.status = CardStatus::CALLED_TO_DISCARD;
    m = m.reason(0).signal(0);
  });
}

}  // namespace

// We are the receiver: Cathy's Yellow to us (her Bob) touches our slot 2, which an
// earlier clue called to discard. We cannot see it, and read the play all the same.
TEST(Reactor0StableColourReplacesDiscardCall, TheReceiverReadsThePlay) {
  SetupOptions opts;
  opts.hands = {
      {"xx", "xx", "xx", "xx", "xx"},
      {"r4", "g2", "b2", "p2", "g3"},
      {"g1", "r3", "b3", "p4", "r4"},
  };
  opts.starting = TestPlayer::CATHY;
  use_reactor0(opts);
  Game g = setup(opts);
  call_to_discard(g, TestPlayer::ALICE, 2);

  g = take_turn(std::move(g), "Cathy clues yellow to Alice (slot 2)");

  EXPECT_EQ(status_at(g, TestPlayer::ALICE, 2), CardStatus::CALLED_TO_PLAY)
      << "the play call replaces the discard call";
  expect_infs(g, std::nullopt, TestPlayer::ALICE, 2, {"y1"});
}

// The same clue as a seat that can see the card: Alice's Yellow to Bob calls his
// CTD'd y1 to play, as it always did.
TEST(Reactor0StableColourReplacesDiscardCall, ASeatThatSeesTheCardReadsItAlike) {
  SetupOptions opts;
  opts.hands = {
      {"xx", "xx", "xx", "xx", "xx"},
      {"r4", "y1", "b2", "p2", "g3"},
      {"g1", "r3", "b3", "p4", "r4"},
  };
  use_reactor0(opts);
  Game g = setup(opts);
  call_to_discard(g, TestPlayer::BOB, 2);

  g = take_turn(std::move(g), "Alice clues yellow to Bob");

  EXPECT_EQ(status_at(g, TestPlayer::BOB, 2), CardStatus::CALLED_TO_PLAY);
  expect_infs(g, std::nullopt, TestPlayer::BOB, 2, {"y1"});
}

// The giver still never calls a card it can see is dead: Bob's CTD'd slot 2 is a y3
// with yellow on 0, and Alice's Yellow reads as a mistake (`target_play`'s
// consistency test), so it is never offered.
TEST(Reactor0StableColourReplacesDiscardCall, TheGiverNeverCallsADeadCard) {
  SetupOptions opts;
  opts.hands = {
      {"xx", "xx", "xx", "xx", "xx"},
      {"r4", "y3", "b2", "p2", "g3"},
      {"g1", "r3", "b3", "p4", "r4"},
  };
  use_reactor0(opts);
  Game g = setup(opts);
  call_to_discard(g, TestPlayer::BOB, 2);

  g = take_turn(std::move(g), "Alice clues yellow to Bob");

  EXPECT_EQ(last_clue_interp(g), ClueInterp::MISTAKE);
  EXPECT_NE(status_at(g, TestPlayer::BOB, 2), CardStatus::CALLED_TO_PLAY);
}
