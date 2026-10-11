#include "hanabi/conventions/tiiah/idle_stall.h"

#include <algorithm>
#include <utility>
#include <variant>
#include <vector>

#include "hanabi/basics/state.h"
#include "hanabi/conventions/reactor0/calls.h"
#include "hanabi/conventions/reactor0/decision.h"
#include "hanabi/conventions/reactor0/facts.h"
#include "hanabi/endgame/forced_endgame.h"
#include "hanabi/logging/decide_trace.h"

namespace hanabi::tiiah {

namespace {

// The clue `chosen` performs, as the Action the reading takes; nullopt for a play or
// a discard.
std::optional<Action> as_clue(const Game& game, const PerformAction& chosen) {
  const State& s = game.state;
  ClueKind kind;
  int target = -1;
  int value = 0;
  if (const auto* c = std::get_if<PerformColour>(&chosen)) {
    kind = ClueKind::COLOUR;
    target = c->target;
    value = c->value;
  } else if (const auto* r = std::get_if<PerformRank>(&chosen)) {
    kind = ClueKind::RANK;
    target = r->target;
    value = r->value;
  } else {
    return std::nullopt;
  }
  for (const Clue& clue : s.all_valid_clues(target)) {
    if (clue.kind == kind && clue.value == value) {
      return Action{ClueAction{s.our_player_index, target,
                               s.clue_touched(s.hands[target], kind, value), clue.base()}};
    }
  }
  return std::nullopt;
}

// Bob's card `o` is the LAST USABLE COPY of its identity (the user's sense of
// critical): it is not trash, and every copy not yet discarded is in his hand. A lone
// critical card counts, and so do both copies of an unplayable 4 held together.
bool last_usable_copy(const State& s, int bob, int o) {
  const auto id = s.deck[o].id();
  if (!id || s.is_basic_trash(*id)) return false;
  const int discarded =
      static_cast<int>(s.discard_stacks[id->suit_index][id->rank - 1].size());
  int held = 0;
  for (int p : s.hands[bob]) {
    if (s.deck[p].id() == *id) ++held;
  }
  return held == s.card_count[id->to_ord()] - discarded;
}

bool holds_last_usable_copy(const State& s, int bob) {
  for (int o : s.hands[bob]) {
    if (last_usable_copy(s, bob, o)) return true;
  }
  return false;
}

// A clue that SAVES Bob's cards is no stall: it newly touches one of his critical cards,
// or his chop is a GOOD card -- not trash, a free chuck or a same-hand dupe -- and the
// clue moves his chop or gives him a known safe discard. That covers the referential
// discards and trash reveals that save a good chop (the user's ruling, self-play 9000115
// T22: a 4 touching sim-bob's p4 chop). Replays 2025193 T50 (the 4 on yagami's critical
// chop), 2026350 T52 (the 5 naming the b5), 2011327 T22 (Red revealing an r2 as trash
// over a critical g5 chop).
bool saves_bobs_chop(const Game& game, const Action& clue, int bob) {
  const State& s = game.state;
  const auto& ca = std::get<ClueAction>(clue);
  if (ca.target == bob) {
    for (int o : ca.list_) {
      if (!s.deck[o].clued && last_usable_copy(s, bob, o)) return true;
    }
  }
  const auto chop = game.chop(bob);
  if (!chop || !s.deck[*chop].id() || hanabi::reactor0::chop_is_expendable(game, bob)) {
    return false;
  }
  const Game hypo = game.simulate(clue);
  if (hypo.chop(bob) != chop) return true;
  const auto before = game.common.thinks_trash(game, bob);
  for (int o : hypo.common.thinks_trash(hypo, bob)) {
    if (std::find(before.begin(), before.end(), o) == before.end()) return true;
  }
  return false;
}

bool holds_a_play(const State& s, int bob) {
  for (int o : s.hands[bob]) {
    const auto id = s.deck[o].id();
    if (id && s.is_playable(*id)) return true;
  }
  return false;
}

}  // namespace

PerformAction no_idle_stall(const Game& game, const PerformAction& chosen) {
  const State& s = game.state;
  if (!s.variant->throw_it_in_a_hole) return chosen;
  if (s.clue_tokens >= 8 || s.cards_left <= 0) return chosen;
  const auto clue = as_clue(game, chosen);
  if (!clue) return chosen;
  const int bob = s.next_player_index(s.our_player_index);
  if (holds_a_play(s, bob) || !holds_last_usable_copy(s, bob)) return chosen;
  // Not in a forced endgame: a stall one of its rules requires is no idle stall (the
  // user's clarification, self-play 9000170 T58).
  if (hanabi::endgame::forced_endgame_action(game)) return chosen;
  // A save is no stall.
  if (saves_bobs_chop(game, *clue, bob)) return chosen;
  // A clue that gets a card played is not a stall.
  const auto read = hanabi::reactor0::analyse_clues(game, {{chosen, *clue}});
  if (read.empty()) return chosen;
  const auto& r = read.front().reading;
  if (r.stable_outcome == hanabi::reactor0::Outcome::PLAY ||
      r.reacter_side.outcome == hanabi::reactor0::Outcome::PLAY ||
      r.receiver_side.outcome == hanabi::reactor0::Outcome::PLAY) {
    return chosen;
  }
  const auto instead = hanabi::reactor0::choose_action(game);
  if (!instead) return chosen;
  // A LOCKED Alice has no chop. Her discard would then be a blind throw of a card
  // she was told to keep -- unless it is a chuck she knows is safe -- and that loses
  // more than the stall does: self-play threw a critical card 19 times in 51.
  if (const auto* d = std::get_if<PerformDiscard>(&*instead);
      d && !game.chop(s.our_player_index)) {
    const auto chuck = hanabi::reactor0::action_lists(game, s.our_player_index).chuck;
    if (std::find(chuck.begin(), chuck.end(), d->target) == chuck.end()) {
      hanabi::logging::log_branch("tiiah.no_idle_stall_locked", {{"bob", bob}});
      return chosen;
    }
  }
  hanabi::logging::log_branch("tiiah.no_idle_stall",
                              {{"bob", bob}, {"shape", hanabi::reactor0::shape_name(r.shape)}});
  return *instead;
}

}  // namespace hanabi::tiiah
