// THE STACK INVARIANT (v23.34.0, the user's rule; tiiah/CONVENTION.md §1.3).
//
// A seat's stack views never stand at or past a card none of whose copies can
// have been played: every copy is in the discard pile or in a hand the seat can
// see. A critical card in a partner's hand is the plain case; both copies of a 3
// in partners' hands is another.
//
// Outside Throw It in a Hole the stacks are public and this never fires. Inside
// it, every view a seat holds is a belief -- its own (`play_stacks`), what it
// shares with each partner (`pairwise_play_stacks`), and what every seat knows
// (`common_play_stacks`) -- and a belief past such a card is false. Replay
// 2027454 T41: will-bot67's common view and both partner rows took a g3 while it
// could see the other two (`human_vs_bot_diagnostics/2027454.md`).
#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "hanabi/basics/identity.h"

namespace hanabi {

class Game;
struct State;

struct StackViolation {
  std::string view;    // "private", "pair" or "common"
  int view_seat = -1;  // a pair row's partner; -1 for the other two views
  Identity id;         // the card none of whose copies can have been played
  int stack = 0;       // where the view stands in its suit
  std::vector<int> seen;  // the orders of the copies in sight, pile and hands
};

// Every view of `game`'s seat that stands at or past such a card.
std::vector<StackViolation> stacks_past_unplayed_in_sight(const Game& game);

// Is `id` such a card, by `s`'s seat's sight? Then no hole card can be it, and no
// view may book it: Throw It in a Hole's shared settles ask this before they name a
// card (tiiah/CONVENTION.md §1e).
bool unplayed_in_sight(const State& s, Identity id);

// Strict mode turns a violation into a `std::logic_error`. The test binaries set
// it (tests/strict_invariants.cpp); the live bot, self_play and replay_log do
// not, and only log it.
void set_strict_invariants(bool on);
bool strict_invariants();

// Logs each violation as `invariant.stack_past_unplayed`, naming the call site
// `where`, and throws in strict mode.
void check_stack_invariant(const Game& game, std::string_view where);

}  // namespace hanabi
