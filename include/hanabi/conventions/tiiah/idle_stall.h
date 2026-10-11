// NO IDLE STALL (Throw It in a Hole, the user's ruling; replay 2027469 T57).
//
// Unless it is a forced endgame, Alice may not give a clue that gets no card played
// while Bob has no playable card and holds a critical one -- the last usable copy of
// an identity, every undiscarded copy of which is in his hand. The token is worth
// more in Bob's hands: in 2027469 will-bot67's trash-revealing 1 to yagami spent the
// only clue yagami could have given will-bot69 for its r5, and the game was lost.
//
// Not idle stalls, so kept: a stall a forced endgame requires (self-play 9000170 T58),
// and a save -- a clue that newly touches Bob's critical card, or moves his chop or
// gives him a safe discard while that chop is a good card (self-play 9000115 T22). A
// locked Alice keeps her clue too, rather than throw a card blind.
//
// A guard on the chosen action, so it overrides the endgame search too
// (tiiah/CONVENTION.md §2x).
#pragma once

#include "hanabi/basics/action.h"
#include "hanabi/basics/game.h"

namespace hanabi::tiiah {

// `chosen`, or -- when it is such a clue -- the play/discard phase's action instead.
PerformAction no_idle_stall(const Game& game, const PerformAction& chosen);

}  // namespace hanabi::tiiah
