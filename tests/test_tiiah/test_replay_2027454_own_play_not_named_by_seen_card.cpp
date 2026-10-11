// Replay 2027454 T40-T44 (TIIAH & Gray Pink (6 Suits)): human diagnostic
// human_vs_bot_diagnostics/2027454.md (v23.34.0, the user's rule). Our own blind play
// is never named, in any view, as an identity we can see is gone.
//
// T40: yagami's Blue to will-bot69 pairs will-bot67's o39 with will-bot69's r5. The
// bucket names green, so the team reads o39 as the g3; will-bot67 sees both g3s (o12
// thrown at T30, will-bot69's o10) and reads `{y2,p3}`. T41: it played o39, the y2.
// Until v23.34.0 `note_hidden_action` named the play by the team's reading, so its
// common view and both pair rows took a g3 with the critical g3 in will-bot69's hand.

#include <gtest/gtest.h>

#include "hanabi/basics/action.h"
#include "hanabi/basics/game.h"
#include "hanabi/basics/identity.h"
#include "hanabi/basics/identity_set.h"
#include "hanabi/basics/stack_invariant.h"
#include "hanabi/logging/state_snapshot.h"
#include "replay_helpers.h"
#include "test_harness.h"

// T44, will-bot67's seat: o39 is in the hole as `{y2,p3}`, and no view of ours has
// green past 2.
// Variant: Throw It in a Hole & Gray Pink (6 Suits). 3 players, our_player_index=1.
TEST(TiiahReplay2027454, OwnPlayIsNotNamedByACardWeSeeIsGone) {
  const char* kSnapshotJson = R"json(
{
  "bot": "will-bot67",
  "ch": "STATE",
  "current_player_index": 1,
  "database_id": 2027454,
  "debug": {
    "cards_left": 12,
    "clue_tokens": 3,
    "common_play_stacks": [
      5,
      1,
      3,
      4,
      2,
      3
    ],
    "current_player_index": 1,
    "discards": [
      {
        "order": 29,
        "rank": 1,
        "suit": 0
      },
      {
        "order": 28,
        "rank": 1,
        "suit": 0
      },
      {
        "order": 24,
        "rank": 2,
        "suit": 0
      },
      {
        "order": 27,
        "rank": 4,
        "suit": 1
      },
      {
        "order": 23,
        "rank": 1,
        "suit": 2
      },
      {
        "order": 2,
        "rank": 1,
        "suit": 2
      },
      {
        "order": 12,
        "rank": 3,
        "suit": 2
      },
      {
        "order": 30,
        "rank": 4,
        "suit": 2
      },
      {
        "order": 20,
        "rank": 2,
        "suit": 3
      },
      {
        "order": 8,
        "rank": 3,
        "suit": 4
      }
    ],
    "endgame_turns": null,
    "hands": [
      {
        "cards": [
          {
            "clued": false,
            "focused": false,
            "id": [
              3,
              4
            ],
            "inferred": 838261740,
            "info_lock": null,
            "order": 42,
            "possible": 838261740,
            "slot": 1,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": [
              1,
              1
            ],
            "inferred": 805733356,
            "info_lock": null,
            "order": 33,
            "possible": 805733356,
            "slot": 2,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              4,
              4
            ],
            "inferred": 32505856,
            "info_lock": null,
            "order": 25,
            "possible": 32505856,
            "slot": 3,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": true,
            "id": [
              2,
              4
            ],
            "inferred": 8192,
            "info_lock": null,
            "order": 17,
            "possible": 8192,
            "slot": 4,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              4,
              4
            ],
            "inferred": 8388608,
            "info_lock": null,
            "order": 0,
            "possible": 8388608,
            "slot": 5,
            "status": "NONE",
            "trash": false,
            "urgent": false
          }
        ],
        "name": "yagami_black",
        "player": 0
      },
      {
        "cards": [
          {
            "clued": false,
            "focused": false,
            "id": null,
            "inferred": 838261740,
            "info_lock": null,
            "order": 40,
            "possible": 838261740,
            "slot": 1,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": null,
            "inferred": 838261740,
            "info_lock": null,
            "order": 36,
            "possible": 838261740,
            "slot": 2,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": null,
            "inferred": 16161196,
            "info_lock": null,
            "order": 31,
            "possible": 16161260,
            "slot": 3,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": null,
            "inferred": 192,
            "info_lock": null,
            "order": 16,
            "possible": 224,
            "slot": 4,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": true,
            "id": null,
            "inferred": 805306368,
            "info_lock": null,
            "order": 9,
            "possible": 805306368,
            "slot": 5,
            "status": "NONE",
            "trash": false,
            "urgent": false
          }
        ],
        "name": "will-bot67",
        "player": 1
      },
      {
        "cards": [
          {
            "clued": false,
            "focused": false,
            "id": [
              4,
              1
            ],
            "inferred": 838261740,
            "info_lock": null,
            "order": 41,
            "possible": 838261740,
            "slot": 1,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": [
              2,
              5
            ],
            "inferred": 833637292,
            "info_lock": null,
            "order": 37,
            "possible": 837835756,
            "slot": 2,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": [
              2,
              2
            ],
            "inferred": 833637292,
            "info_lock": null,
            "order": 35,
            "possible": 837835756,
            "slot": 3,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              3,
              5
            ],
            "inferred": 524288,
            "info_lock": null,
            "order": 15,
            "possible": 524288,
            "slot": 4,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": [
              2,
              3
            ],
            "inferred": 6624,
            "info_lock": null,
            "order": 10,
            "possible": 6624,
            "slot": 5,
            "status": "NONE",
            "trash": false,
            "urgent": false
          }
        ],
        "name": "will-bot69",
        "player": 2
      }
    ],
    "in_progress": true,
    "max_ranks": [
      5,
      5,
      5,
      5,
      5,
      5
    ],
    "move_history": [
      {
        "k": "clue",
        "v": "Play"
      },
      {
        "k": "clue",
        "v": "Play"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Play"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Reactive"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Discard"
      },
      {
        "k": "clue",
        "v": "Discard"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Play"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Reactive"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Reactive"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Discard"
      },
      {
        "k": "discard",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Play"
      },
      {
        "k": "clue",
        "v": "Reactive"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Reactive"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Play"
      },
      {
        "k": "clue",
        "v": "Reactive"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      },
      {
        "k": "play",
        "v": "None"
      }
    ],
    "pairwise_play_stacks": [
      [
        5,
        1,
        3,
        4,
        2,
        3
      ],
      [
        0,
        0,
        0,
        0,
        0,
        0
      ],
      [
        5,
        1,
        3,
        4,
        2,
        3
      ]
    ],
    "pending_reactions": [],
    "play_stacks": [
      5,
      1,
      2,
      4,
      2,
      3
    ],
    "strikes": 0,
    "turn_count": 44,
    "waiting": []
  },
  "game_id": 6244,
  "replay": {
    "actions": [
      {
        "order": 0,
        "p": 0,
        "rank": 4,
        "suit": 4,
        "t": "draw"
      },
      {
        "order": 1,
        "p": 0,
        "rank": 2,
        "suit": 4,
        "t": "draw"
      },
      {
        "order": 2,
        "p": 0,
        "rank": 1,
        "suit": 2,
        "t": "draw"
      },
      {
        "order": 3,
        "p": 0,
        "rank": 2,
        "suit": 3,
        "t": "draw"
      },
      {
        "order": 4,
        "p": 0,
        "rank": 4,
        "suit": 3,
        "t": "draw"
      },
      {
        "order": 5,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 6,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 7,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 8,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 9,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 10,
        "p": 2,
        "rank": 3,
        "suit": 2,
        "t": "draw"
      },
      {
        "order": 11,
        "p": 2,
        "rank": 3,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 12,
        "p": 2,
        "rank": 3,
        "suit": 2,
        "t": "draw"
      },
      {
        "order": 13,
        "p": 2,
        "rank": 1,
        "suit": 4,
        "t": "draw"
      },
      {
        "order": 14,
        "p": 2,
        "rank": 1,
        "suit": 3,
        "t": "draw"
      },
      {
        "giver": 0,
        "kind": "C",
        "list": [
          6
        ],
        "t": "clue",
        "target": 1,
        "value": 2
      },
      {
        "clues": 7,
        "max": 30,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 1,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          14
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 6,
        "max": 30,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 2,
        "t": "turn"
      },
      {
        "order": 14,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 15,
        "p": 2,
        "rank": 5,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 6,
        "max": 30,
        "score": 1,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 3,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "C",
        "list": [
          13
        ],
        "t": "clue",
        "target": 2,
        "value": 4
      },
      {
        "clues": 5,
        "max": 30,
        "score": 1,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 4,
        "t": "turn"
      },
      {
        "order": 6,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 16,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 30,
        "score": 2,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 5,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "C",
        "list": [
          5,
          16
        ],
        "t": "clue",
        "target": 1,
        "value": 1
      },
      {
        "clues": 4,
        "max": 30,
        "score": 2,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 6,
        "t": "turn"
      },
      {
        "order": 3,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 17,
        "p": 0,
        "rank": 4,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 30,
        "score": 3,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 7,
        "t": "turn"
      },
      {
        "order": 5,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 18,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 30,
        "score": 4,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 8,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "R",
        "list": [
          0,
          4,
          17
        ],
        "t": "clue",
        "target": 0,
        "value": 4
      },
      {
        "clues": 3,
        "max": 30,
        "score": 4,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 9,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "R",
        "list": [
          7,
          9
        ],
        "t": "clue",
        "target": 1,
        "value": 4
      },
      {
        "clues": 2,
        "max": 30,
        "score": 4,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 10,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 8,
        "p": 1,
        "rank": 3,
        "suit": 4,
        "t": "discard"
      },
      {
        "order": 19,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 4,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 11,
        "t": "turn"
      },
      {
        "order": 13,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 20,
        "p": 2,
        "rank": 2,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 5,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 12,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "C",
        "list": [
          18,
          19
        ],
        "t": "clue",
        "target": 1,
        "value": 0
      },
      {
        "clues": 2,
        "max": 30,
        "score": 5,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 13,
        "t": "turn"
      },
      {
        "order": 19,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 21,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 30,
        "score": 6,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 14,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 20,
        "p": 2,
        "rank": 2,
        "suit": 3,
        "t": "discard"
      },
      {
        "order": 22,
        "p": 2,
        "rank": 4,
        "suit": 0,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 6,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 15,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "C",
        "list": [
          11,
          22
        ],
        "t": "clue",
        "target": 2,
        "value": 0
      },
      {
        "clues": 2,
        "max": 30,
        "score": 6,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 16,
        "t": "turn"
      },
      {
        "order": 18,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 23,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 30,
        "score": 7,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 17,
        "t": "turn"
      },
      {
        "order": 11,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 24,
        "p": 2,
        "rank": 2,
        "suit": 0,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 30,
        "score": 8,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 18,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 2,
        "p": 0,
        "rank": 1,
        "suit": 2,
        "t": "discard"
      },
      {
        "order": 25,
        "p": 0,
        "rank": 4,
        "suit": 4,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 8,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 19,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 23,
        "p": 1,
        "rank": 1,
        "suit": 2,
        "t": "discard"
      },
      {
        "order": 26,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 30,
        "score": 8,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 20,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "R",
        "list": [
          7,
          9,
          26
        ],
        "t": "clue",
        "target": 1,
        "value": 5
      },
      {
        "clues": 3,
        "max": 30,
        "score": 8,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 21,
        "t": "turn"
      },
      {
        "order": 1,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 27,
        "p": 0,
        "rank": 4,
        "suit": 1,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 9,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 22,
        "t": "turn"
      },
      {
        "order": 26,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 28,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 23,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 24,
        "p": 2,
        "rank": 2,
        "suit": 0,
        "t": "discard"
      },
      {
        "order": 29,
        "p": 2,
        "rank": 1,
        "suit": 0,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 24,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 27,
        "p": 0,
        "rank": 4,
        "suit": 1,
        "t": "discard"
      },
      {
        "order": 30,
        "p": 0,
        "rank": 4,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 25,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 28,
        "p": 1,
        "rank": 1,
        "suit": 0,
        "t": "discard"
      },
      {
        "order": 31,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 6,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 26,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 29,
        "p": 2,
        "rank": 1,
        "suit": 0,
        "t": "discard"
      },
      {
        "order": 32,
        "p": 2,
        "rank": 5,
        "suit": 0,
        "t": "draw"
      },
      {
        "clues": 7,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 27,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 30,
        "p": 0,
        "rank": 4,
        "suit": 2,
        "t": "discard"
      },
      {
        "order": 33,
        "p": 0,
        "rank": 1,
        "suit": 1,
        "t": "draw"
      },
      {
        "clues": 8,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 28,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "R",
        "list": [
          15,
          32
        ],
        "t": "clue",
        "target": 2,
        "value": 5
      },
      {
        "clues": 7,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 29,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 12,
        "p": 2,
        "rank": 3,
        "suit": 2,
        "t": "discard"
      },
      {
        "order": 34,
        "p": 2,
        "rank": 3,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 8,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 30,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "R",
        "list": [
          7,
          9
        ],
        "t": "clue",
        "target": 1,
        "value": 5
      },
      {
        "clues": 7,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 31,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          0,
          25
        ],
        "t": "clue",
        "target": 0,
        "value": 4
      },
      {
        "clues": 6,
        "max": 30,
        "score": 10,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 32,
        "t": "turn"
      },
      {
        "order": 34,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 35,
        "p": 2,
        "rank": 2,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 6,
        "max": 30,
        "score": 11,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 33,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "R",
        "list": [
          7,
          9
        ],
        "t": "clue",
        "target": 1,
        "value": 5
      },
      {
        "clues": 5,
        "max": 30,
        "score": 11,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 34,
        "t": "turn"
      },
      {
        "order": 7,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 36,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 30,
        "score": 12,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 35,
        "t": "turn"
      },
      {
        "order": 22,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 37,
        "p": 2,
        "rank": 5,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 30,
        "score": 13,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 36,
        "t": "turn"
      },
      {
        "order": 4,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 38,
        "p": 0,
        "rank": 3,
        "suit": 5,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 30,
        "score": 14,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 37,
        "t": "turn"
      },
      {
        "order": 21,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 39,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 30,
        "score": 15,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 38,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "C",
        "list": [
          17
        ],
        "t": "clue",
        "target": 0,
        "value": 2
      },
      {
        "clues": 4,
        "max": 30,
        "score": 15,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 39,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "C",
        "list": [
          15
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 3,
        "max": 30,
        "score": 15,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 40,
        "t": "turn"
      },
      {
        "order": 39,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 40,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 16,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 41,
        "t": "turn"
      },
      {
        "order": 32,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 41,
        "p": 2,
        "rank": 1,
        "suit": 4,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 17,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 42,
        "t": "turn"
      },
      {
        "order": 38,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 42,
        "p": 0,
        "rank": 4,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 30,
        "score": 18,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 43,
        "t": "turn"
      }
    ],
    "all_plays": false,
    "convention": "tiiah",
    "deck": [
      [
        4,
        4
      ],
      [
        4,
        2
      ],
      [
        2,
        1
      ],
      [
        3,
        2
      ],
      [
        3,
        4
      ],
      [
        1,
        1
      ],
      [
        2,
        1
      ],
      [
        5,
        2
      ],
      [
        4,
        3
      ],
      null,
      [
        2,
        3
      ],
      [
        0,
        3
      ],
      [
        2,
        3
      ],
      [
        4,
        1
      ],
      [
        3,
        1
      ],
      [
        3,
        5
      ],
      null,
      [
        2,
        4
      ],
      [
        0,
        2
      ],
      [
        0,
        1
      ],
      [
        3,
        2
      ],
      [
        2,
        2
      ],
      [
        0,
        4
      ],
      [
        2,
        1
      ],
      [
        0,
        2
      ],
      [
        4,
        4
      ],
      [
        5,
        1
      ],
      [
        1,
        4
      ],
      [
        0,
        1
      ],
      [
        0,
        1
      ],
      [
        2,
        4
      ],
      null,
      [
        0,
        5
      ],
      [
        1,
        1
      ],
      [
        3,
        3
      ],
      [
        2,
        2
      ],
      null,
      [
        2,
        5
      ],
      [
        5,
        3
      ],
      null,
      null,
      [
        4,
        1
      ],
      [
        3,
        4
      ]
    ],
    "names": [
      "yagami_black",
      "will-bot67",
      "will-bot69"
    ],
    "num_players": 3,
    "options": {
      "deck_plays": false,
      "detrimental_characters": false,
      "empty_clues": false,
      "num_players": 3,
      "one_extra_card": false,
      "one_less_card": false,
      "speedrun": false,
      "starting_player": 0,
      "variant_name": "Throw It in a Hole & Gray Pink (6 Suits)"
    },
    "our_player_index": 1,
    "rlocks": true,
    "variant": "Throw It in a Hole & Gray Pink (6 Suits)",
    "zcs_turn": -1
  },
  "ts": "2026-10-11T17:07:05.476",
  "turn": 44
}
  )json";
  auto rec = nlohmann::json::parse(kSnapshotJson);
  hanabi::Game game = hanabi::logging::apply_snapshot(rec);

  const hanabi::Identity g3{2, 3};
  const hanabi::Identity y2{1, 2};
  const hanabi::Identity p3{4, 3};
  const auto& m = game.meta[39];
  EXPECT_FALSE(m.named_in_hole.contains(g3)) << "the team's g3 is not booked";
  EXPECT_FALSE(m.private_named.contains(g3));
  EXPECT_EQ(m.superposition, hanabi::IdentitySet::single(y2).add(p3))
      << "a superposition over our own reading";

  const auto& s = game.state;
  EXPECT_EQ(s.common_play_stacks[2], 2) << "common green";
  EXPECT_EQ(s.pairwise_play_stacks[0][2], 2) << "green in the row for yagami";
  EXPECT_EQ(s.pairwise_play_stacks[2][2], 2) << "green in the row for will-bot69";
  EXPECT_EQ(s.play_stacks[2], 2) << "our own green";
  EXPECT_TRUE(hanabi::stacks_past_unplayed_in_sight(game).empty());
}
