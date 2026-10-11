#include "hanabi/basics/stack_invariant.h"

#include <atomic>
#include <stdexcept>
#include <utility>
#include <variant>

#include "hanabi/basics/action.h"
#include "hanabi/basics/game.h"
#include "hanabi/basics/state.h"
#include "hanabi/logging/decide_trace.h"

namespace hanabi {

namespace {

std::atomic<bool> g_strict{false};

// The identities none of whose copies can have been played, by our own sight:
// every copy is in the discard pile or in a partner's hand.
//
// A card in the pile counts only when it was DISCARDED on the wire -- a discard,
// or outside Throw It in a Hole a play that failed, which the server shows. A
// hidden play booked into the pile as a strike is left out: whether it landed is
// our inference, not our sight, and a wrong one is a different bug. Our own
// settled strikes (`tiiah::settle`) are not even seen. An INVERTED suit is skipped
// altogether: its Discard button is the one that stacks a card, so a copy in the
// pile may have landed.
// Each comes with the orders of the copies seen.
std::vector<std::pair<Identity, std::vector<int>>> all_unplayed_in_sight(const State& s) {
  std::vector<bool> thrown(s.deck.size(), false);
  for (const auto& turn : s.action_list) {
    for (const Action& a : turn) {
      if (const auto* d = std::get_if<DiscardAction>(&a)) {
        if (d->order >= 0 && d->order < static_cast<int>(thrown.size())) thrown[d->order] = true;
      }
    }
  }
  std::vector<std::vector<int>> seen(s.card_count.size());
  auto count = [&](int order) {
    if (order < 0 || order >= static_cast<int>(s.deck.size())) return;
    const auto id = s.deck[order].id();
    if (!id) return;
    const int ord = id->to_ord();
    if (ord >= 0 && ord < static_cast<int>(seen.size())) seen[ord].push_back(order);
  };
  for (const auto& suit : s.discard_stacks) {
    for (const auto& pile : suit) {
      for (int o : pile) {
        if (o >= 0 && o < static_cast<int>(thrown.size()) && thrown[o]) count(o);
      }
    }
  }
  for (int p = 0; p < static_cast<int>(s.hands.size()); ++p) {
    if (p == s.our_player_index) continue;
    for (int o : s.hands[p]) count(o);
  }

  std::vector<std::pair<Identity, std::vector<int>>> out;
  for (Identity id : s.all_ids) {
    if (s.variant->suits[id.suit_index].suit_type.inverted) continue;
    const int ord = id.to_ord();
    if (ord >= static_cast<int>(s.card_count.size())) continue;
    const int copies = s.card_count[ord];
    if (copies > 0 && static_cast<int>(seen[ord].size()) >= copies) {
      out.emplace_back(id, seen[ord]);
    }
  }
  return out;
}

// Does a view standing at `stacks` hold `id` as played? Reversed suits count down
// from 6, so the test is the one `tiiah::stack_rests_on_this_copy` asks.
bool at_or_past(const State& s, const std::vector<int>& stacks, Identity id) {
  if (id.suit_index >= static_cast<int>(stacks.size())) return false;
  const int h = stacks[id.suit_index];
  return s.variant->suits[id.suit_index].suit_type.reversed ? h <= id.rank : h >= id.rank;
}

}  // namespace

std::vector<StackViolation> stacks_past_unplayed_in_sight(const Game& game) {
  const State& s = game.state;
  std::vector<StackViolation> out;
  for (const auto& [id, seen] : all_unplayed_in_sight(s)) {
    auto check = [&](const char* view, int seat, const std::vector<int>& stacks) {
      if (at_or_past(s, stacks, id)) {
        out.push_back(StackViolation{view, seat, id, stacks[id.suit_index], seen});
      }
    };
    check("private", -1, s.play_stacks);
    check("common", -1, s.common_play_stacks);
    for (int p = 0; p < static_cast<int>(s.pairwise_play_stacks.size()); ++p) {
      if (p == s.our_player_index) continue;  // unused
      check("pair", p, s.pairwise_play_stacks[p]);
    }
  }
  return out;
}

bool unplayed_in_sight(const State& s, Identity id) {
  for (const auto& [u, seen] : all_unplayed_in_sight(s)) {
    if (u == id) return true;
  }
  return false;
}

void set_strict_invariants(bool on) { g_strict.store(on); }
bool strict_invariants() { return g_strict.load(); }

void check_stack_invariant(const Game& game, std::string_view where) {
  const auto violations = stacks_past_unplayed_in_sight(game);
  if (violations.empty()) return;
  const State& s = game.state;
  std::string what;
  for (const StackViolation& v : violations) {
    hanabi::logging::log_branch("invariant.stack_past_unplayed",
                                {{"where", where},
                                 {"turn", s.turn_count},
                                 {"view", v.view},
                                 {"view_seat", v.view_seat},
                                 {"card", s.log_id(v.id)},
                                 {"stack", v.stack},
                                 {"seen", v.seen}});
    if (!what.empty()) what += "; ";
    what += v.view;
    if (v.view_seat >= 0) what += " " + std::to_string(v.view_seat);
    what += " stands at " + std::to_string(v.stack) + " past unplayed " + s.log_id(v.id) +
            " (seen:";
    for (int o : v.seen) what += " o" + std::to_string(o);
    what += ")";
  }
  if (strict_invariants()) {
    throw std::logic_error("stack invariant (" + std::string(where) + ", seat " +
                           std::to_string(s.our_player_index) + ", turn " +
                           std::to_string(s.turn_count) + "): " + what);
  }
}

}  // namespace hanabi
