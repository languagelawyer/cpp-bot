// Linked into every test binary: a test fails on any violation of the stack
// invariant (`hanabi/basics/stack_invariant.h`, v23.34.0, the user's rule). The
// live bot, self_play and replay_log only log one.
#include "hanabi/basics/stack_invariant.h"

namespace {
const bool kStrictInvariants = (hanabi::set_strict_invariants(true), true);
}  // namespace
