// Self-play TIIAH & Black (6 Suits) seed 159 (human_vs_bot_diagnostics/9000159_23_30.md),
// played by the exp/scream-discard candidate (v23.30.0 plus that experiment). Seats:
// 0 sim-alice, 1 sim-bob, 2 sim-cathy. Both snapshots replay under this build.
//
// T36: sim-cathy, at 1 clue, saw sim-alice's chop was the k1 -- critical, and playable
// with black on 0 -- and locked her with a 5 (rung 3.10). The user: "sim-cathy is
// expected to clue black here to get the black 1 to play. Once sim-alice plays black
// 1, sim-bob should discard a card (since he is at 0 clues) that is least likely to be
// critical - in this case, the yellow 4 since he sees it in sim-cathy's hand."

#include <gtest/gtest.h>

#include <variant>

#include "hanabi/basics/action.h"
#include "hanabi/basics/card.h"
#include "hanabi/basics/convention.h"
#include "hanabi/basics/game.h"
#include "hanabi/basics/identity.h"
#include "hanabi/logging/state_snapshot.h"
#include "replay_helpers.h"
#include "test_harness.h"

// Variant: Throw It in a Hole & Black (6 Suits). 3 players.

namespace {

constexpr int kBlack = 5;

// sim-cathy's STATE at T36 (our_player_index 2).
const char* kCathyT36 = R"json(
{
  "bot": "sim-cathy",
  "ch": "STATE",
  "current_player_index": 2,
  "debug": {
    "cards_left": 20,
    "clue_tokens": 1,
    "common_play_stacks": [
      1,
      1,
      1,
      3,
      5,
      0
    ],
    "current_player_index": 2,
    "discards": [
      {
        "order": 8,
        "rank": 2,
        "suit": 0
      },
      {
        "order": 0,
        "rank": 4,
        "suit": 0
      },
      {
        "order": 24,
        "rank": 3,
        "suit": 2
      },
      {
        "order": 23,
        "rank": 4,
        "suit": 2
      },
      {
        "order": 29,
        "rank": 1,
        "suit": 3
      },
      {
        "order": 4,
        "rank": 1,
        "suit": 3
      },
      {
        "order": 32,
        "rank": 2,
        "suit": 3
      },
      {
        "order": 19,
        "rank": 4,
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
              5,
              1
            ],
            "inferred": 1047691263,
            "info_lock": null,
            "order": 34,
            "possible": 1047691263,
            "slot": 1,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": [
              0,
              5
            ],
            "inferred": 1040216602,
            "info_lock": null,
            "order": 30,
            "possible": 1047691263,
            "slot": 2,
            "status": "CHOP_MOVED",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": true,
            "id": [
              5,
              3
            ],
            "inferred": 134221956,
            "info_lock": null,
            "order": 20,
            "possible": 134221956,
            "slot": 3,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              0,
              3
            ],
            "inferred": 134221956,
            "info_lock": null,
            "order": 3,
            "possible": 134221956,
            "slot": 4,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              0,
              3
            ],
            "inferred": 134221956,
            "info_lock": null,
            "order": 1,
            "possible": 134221956,
            "slot": 5,
            "status": "NONE",
            "trash": false,
            "urgent": false
          }
        ],
        "name": "sim-alice",
        "player": 0
      },
      {
        "cards": [
          {
            "clued": false,
            "focused": false,
            "id": [
              5,
              4
            ],
            "inferred": 909143931,
            "info_lock": null,
            "order": 31,
            "possible": 909143931,
            "slot": 1,
            "status": "CHOP_MOVED",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              1,
              3
            ],
            "inferred": 138547332,
            "info_lock": null,
            "order": 27,
            "possible": 138547332,
            "slot": 2,
            "status": "CHOP_MOVED",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              2,
              3
            ],
            "inferred": 134352900,
            "info_lock": null,
            "order": 22,
            "possible": 134352900,
            "slot": 3,
            "status": "CHOP_MOVED",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              1,
              4
            ],
            "inferred": 256,
            "info_lock": null,
            "order": 7,
            "possible": 256,
            "slot": 4,
            "status": "CHOP_MOVED",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              2,
              5
            ],
            "inferred": 536887312,
            "info_lock": null,
            "order": 6,
            "possible": 536887312,
            "slot": 5,
            "status": "CHOP_MOVED",
            "trash": false,
            "urgent": false
          }
        ],
        "name": "sim-bob",
        "player": 1
      },
      {
        "cards": [
          {
            "clued": false,
            "focused": false,
            "id": null,
            "inferred": 1047560191,
            "info_lock": null,
            "order": 33,
            "possible": 1047560191,
            "slot": 1,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": null,
            "inferred": 268443904,
            "info_lock": null,
            "order": 17,
            "possible": 268443904,
            "slot": 2,
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
            "order": 13,
            "possible": 524288,
            "slot": 3,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": false,
            "focused": false,
            "id": null,
            "inferred": 637554272,
            "info_lock": null,
            "order": 12,
            "possible": 637554272,
            "slot": 4,
            "status": "NONE",
            "trash": false,
            "urgent": false
          },
          {
            "clued": true,
            "focused": false,
            "id": [
              3,
              4
            ],
            "inferred": 262144,
            "info_lock": 262144,
            "order": 10,
            "possible": 262144,
            "slot": 5,
            "status": "NONE",
            "trash": false,
            "urgent": false
          }
        ],
        "name": "sim-cathy",
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
        "v": "Discard"
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
        "k": "discard",
        "v": "None"
      },
      {
        "k": "clue",
        "v": "Discard"
      },
      {
        "k": "clue",
        "v": "Reveal"
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
        "k": "clue",
        "v": "Lock"
      },
      {
        "k": "clue",
        "v": "Reveal"
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
        "v": "Play"
      }
    ],
    "pairwise_play_stacks": [
      [
        1,
        1,
        1,
        4,
        5,
        0
      ],
      [
        1,
        1,
        1,
        3,
        5,
        0
      ],
      [
        1,
        1,
        1,
        3,
        5,
        0
      ]
    ],
    "pending_reactions": [],
    "play_stacks": [
      1,
      1,
      1,
      4,
      5,
      0
    ],
    "strikes": 0,
    "superpositions": [
      {
        "holder": 1,
        "order": 18,
        "superposition": 33818624
      }
    ],
    "turn_count": 36,
    "waiting": []
  },
  "game_id": 9000159,
  "replay": {
    "actions": [
      {
        "order": 0,
        "p": 0,
        "rank": 4,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 1,
        "p": 0,
        "rank": 3,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 2,
        "p": 0,
        "rank": 2,
        "suit": 3,
        "t": "draw"
      },
      {
        "order": 3,
        "p": 0,
        "rank": 3,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 4,
        "p": 0,
        "rank": 1,
        "suit": 3,
        "t": "draw"
      },
      {
        "order": 5,
        "p": 1,
        "rank": 1,
        "suit": 4,
        "t": "draw"
      },
      {
        "order": 6,
        "p": 1,
        "rank": 5,
        "suit": 2,
        "t": "draw"
      },
      {
        "order": 7,
        "p": 1,
        "rank": 4,
        "suit": 1,
        "t": "draw"
      },
      {
        "order": 8,
        "p": 1,
        "rank": 2,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 9,
        "p": 1,
        "rank": 4,
        "suit": 4,
        "t": "draw"
      },
      {
        "order": 10,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 11,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 12,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 13,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "order": 14,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "giver": 0,
        "kind": "R",
        "list": [
          9,
          7
        ],
        "t": "clue",
        "target": 1,
        "value": 4
      },
      {
        "clues": 7,
        "max": 25,
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
          14,
          13,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 6,
        "max": 25,
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
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 6,
        "max": 25,
        "score": 0,
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
          13,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 4,
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
        "order": 16,
        "p": 1,
        "rank": 2,
        "suit": 4,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 5,
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
        "order": 17,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 6,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "R",
        "list": [
          15
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 7,
        "t": "turn"
      },
      {
        "order": 16,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 18,
        "p": 1,
        "rank": 4,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 8,
        "t": "turn"
      },
      {
        "order": 15,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 19,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 9,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 4,
        "p": 0,
        "rank": 1,
        "suit": 3,
        "t": "discard"
      },
      {
        "order": 20,
        "p": 0,
        "rank": 3,
        "suit": 5,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 10,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          19
        ],
        "t": "clue",
        "target": 2,
        "value": 4
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 11,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "C",
        "list": [
          2
        ],
        "t": "clue",
        "target": 0,
        "value": 3
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 12,
        "t": "turn"
      },
      {
        "order": 2,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 21,
        "p": 0,
        "rank": 5,
        "suit": 4,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 13,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 8,
        "p": 1,
        "rank": 2,
        "suit": 0,
        "t": "discard"
      },
      {
        "order": 22,
        "p": 1,
        "rank": 3,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 14,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "R",
        "list": [
          20,
          3,
          1
        ],
        "t": "clue",
        "target": 0,
        "value": 3
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
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
          9
        ],
        "t": "clue",
        "target": 1,
        "value": 4
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 16,
        "t": "turn"
      },
      {
        "order": 9,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 23,
        "p": 1,
        "rank": 4,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 17,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 19,
        "p": 2,
        "rank": 4,
        "suit": 4,
        "t": "discard"
      },
      {
        "order": 24,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 18,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 0,
        "p": 0,
        "rank": 4,
        "suit": 0,
        "t": "discard"
      },
      {
        "order": 25,
        "p": 0,
        "rank": 3,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
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
        "rank": 4,
        "suit": 2,
        "t": "discard"
      },
      {
        "order": 26,
        "p": 1,
        "rank": 1,
        "suit": 1,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 20,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "C",
        "list": [
          21
        ],
        "t": "clue",
        "target": 0,
        "value": 4
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 21,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "C",
        "list": [
          26,
          7
        ],
        "t": "clue",
        "target": 1,
        "value": 1
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
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
        "order": 27,
        "p": 1,
        "rank": 3,
        "suit": 1,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
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
        "rank": 3,
        "suit": 2,
        "t": "discard"
      },
      {
        "order": 28,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 24,
        "t": "turn"
      },
      {
        "order": 21,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 29,
        "p": 0,
        "rank": 1,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 25,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          28
        ],
        "t": "clue",
        "target": 2,
        "value": 0
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 26,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "R",
        "list": [
          6
        ],
        "t": "clue",
        "target": 1,
        "value": 5
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 27,
        "t": "turn"
      },
      {
        "order": 25,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 30,
        "p": 0,
        "rank": 5,
        "suit": 0,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 28,
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
        "order": 31,
        "p": 1,
        "rank": 4,
        "suit": 5,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 29,
        "t": "turn"
      },
      {
        "order": 28,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 32,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
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
          27,
          22
        ],
        "t": "clue",
        "target": 1,
        "value": 3
      },
      {
        "clues": 1,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 31,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "R",
        "list": [
          17,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 4
      },
      {
        "clues": 0,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 32,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 32,
        "p": 2,
        "rank": 2,
        "suit": 3,
        "t": "discard"
      },
      {
        "order": 33,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 1,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 33,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 29,
        "p": 0,
        "rank": 1,
        "suit": 3,
        "t": "discard"
      },
      {
        "order": 34,
        "p": 0,
        "rank": 1,
        "suit": 5,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 34,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          13,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 1,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 35,
        "t": "turn"
      }
    ],
    "all_plays": false,
    "convention": "tiiah",
    "deck": [
      [
        0,
        4
      ],
      [
        0,
        3
      ],
      [
        3,
        2
      ],
      [
        0,
        3
      ],
      [
        3,
        1
      ],
      [
        4,
        1
      ],
      [
        2,
        5
      ],
      [
        1,
        4
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
        3,
        4
      ],
      [
        2,
        1
      ],
      null,
      [
        3,
        5
      ],
      [
        3,
        1
      ],
      [
        4,
        3
      ],
      [
        4,
        2
      ],
      null,
      [
        3,
        4
      ],
      [
        4,
        4
      ],
      [
        5,
        3
      ],
      [
        4,
        5
      ],
      [
        2,
        3
      ],
      [
        2,
        4
      ],
      [
        2,
        3
      ],
      [
        3,
        3
      ],
      [
        1,
        1
      ],
      [
        1,
        3
      ],
      [
        0,
        1
      ],
      [
        3,
        1
      ],
      [
        0,
        5
      ],
      [
        5,
        4
      ],
      [
        3,
        2
      ],
      null,
      [
        5,
        1
      ]
    ],
    "names": [
      "sim-alice",
      "sim-bob",
      "sim-cathy"
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
      "variant_name": "Throw It in a Hole & Black (6 Suits)"
    },
    "our_player_index": 2,
    "rlocks": true,
    "variant": "Throw It in a Hole & Black (6 Suits)",
    "zcs_turn": -1
  },
  "ts": "2026-10-11T04:37:03.909",
  "turn": 36
}
  )json";

// sim-bob's view of the same position, cut back to T36 (our_player_index 1).
const char* kBobT36 = R"json(
{
  "bot": "sim-bob",
  "ch": "STATE",
  "current_player_index": 1,
  "game_id": 9000159,
  "replay": {
    "actions": [
      {
        "order": 0,
        "p": 0,
        "rank": 4,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 1,
        "p": 0,
        "rank": 3,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 2,
        "p": 0,
        "rank": 2,
        "suit": 3,
        "t": "draw"
      },
      {
        "order": 3,
        "p": 0,
        "rank": 3,
        "suit": 0,
        "t": "draw"
      },
      {
        "order": 4,
        "p": 0,
        "rank": 1,
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
        "rank": 4,
        "suit": 3,
        "t": "draw"
      },
      {
        "order": 11,
        "p": 2,
        "rank": 1,
        "suit": 2,
        "t": "draw"
      },
      {
        "order": 12,
        "p": 2,
        "rank": 5,
        "suit": 1,
        "t": "draw"
      },
      {
        "order": 13,
        "p": 2,
        "rank": 5,
        "suit": 3,
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
        "kind": "R",
        "list": [
          9,
          7
        ],
        "t": "clue",
        "target": 1,
        "value": 4
      },
      {
        "clues": 7,
        "max": 25,
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
          14,
          13,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 6,
        "max": 25,
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
        "rank": 3,
        "suit": 4,
        "t": "draw"
      },
      {
        "clues": 6,
        "max": 25,
        "score": 0,
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
          13,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 4,
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
        "order": 16,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 5,
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
        "order": 17,
        "p": 2,
        "rank": 4,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 6,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "R",
        "list": [
          15
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 7,
        "t": "turn"
      },
      {
        "order": 16,
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
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 8,
        "t": "turn"
      },
      {
        "order": 15,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 19,
        "p": 2,
        "rank": 4,
        "suit": 4,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 9,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 4,
        "p": 0,
        "rank": 1,
        "suit": 3,
        "t": "discard"
      },
      {
        "order": 20,
        "p": 0,
        "rank": 3,
        "suit": 5,
        "t": "draw"
      },
      {
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 10,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          19
        ],
        "t": "clue",
        "target": 2,
        "value": 4
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 11,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "C",
        "list": [
          2
        ],
        "t": "clue",
        "target": 0,
        "value": 3
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 12,
        "t": "turn"
      },
      {
        "order": 2,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 21,
        "p": 0,
        "rank": 5,
        "suit": 4,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 13,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 8,
        "p": 1,
        "rank": 2,
        "suit": 0,
        "t": "discard"
      },
      {
        "order": 22,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 14,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "R",
        "list": [
          20,
          3,
          1
        ],
        "t": "clue",
        "target": 0,
        "value": 3
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
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
          9
        ],
        "t": "clue",
        "target": 1,
        "value": 4
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 16,
        "t": "turn"
      },
      {
        "order": 9,
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
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 17,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 19,
        "p": 2,
        "rank": 4,
        "suit": 4,
        "t": "discard"
      },
      {
        "order": 24,
        "p": 2,
        "rank": 3,
        "suit": 2,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 18,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 0,
        "p": 0,
        "rank": 4,
        "suit": 0,
        "t": "discard"
      },
      {
        "order": 25,
        "p": 0,
        "rank": 3,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
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
        "rank": 4,
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
        "clues": 5,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 20,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "C",
        "list": [
          21
        ],
        "t": "clue",
        "target": 0,
        "value": 4
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 21,
        "t": "turn"
      },
      {
        "giver": 0,
        "kind": "C",
        "list": [
          26,
          7
        ],
        "t": "clue",
        "target": 1,
        "value": 1
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
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
        "order": 27,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
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
        "rank": 3,
        "suit": 2,
        "t": "discard"
      },
      {
        "order": 28,
        "p": 2,
        "rank": 1,
        "suit": 0,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 24,
        "t": "turn"
      },
      {
        "order": 21,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 29,
        "p": 0,
        "rank": 1,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 4,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 25,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          28
        ],
        "t": "clue",
        "target": 2,
        "value": 0
      },
      {
        "clues": 3,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 26,
        "t": "turn"
      },
      {
        "giver": 2,
        "kind": "R",
        "list": [
          6
        ],
        "t": "clue",
        "target": 1,
        "value": 5
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 27,
        "t": "turn"
      },
      {
        "order": 25,
        "p": 0,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 30,
        "p": 0,
        "rank": 5,
        "suit": 0,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 28,
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
        "order": 31,
        "p": 1,
        "rank": -1,
        "suit": -1,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 29,
        "t": "turn"
      },
      {
        "order": 28,
        "p": 2,
        "rank": -1,
        "suit": -1,
        "t": "play"
      },
      {
        "order": 32,
        "p": 2,
        "rank": 2,
        "suit": 3,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
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
          27,
          22
        ],
        "t": "clue",
        "target": 1,
        "value": 3
      },
      {
        "clues": 1,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 31,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "R",
        "list": [
          17,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 4
      },
      {
        "clues": 0,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 32,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 32,
        "p": 2,
        "rank": 2,
        "suit": 3,
        "t": "discard"
      },
      {
        "order": 33,
        "p": 2,
        "rank": 4,
        "suit": 1,
        "t": "draw"
      },
      {
        "clues": 1,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 0,
        "num": 33,
        "t": "turn"
      },
      {
        "failed": false,
        "order": 29,
        "p": 0,
        "rank": 1,
        "suit": 3,
        "t": "discard"
      },
      {
        "order": 34,
        "p": 0,
        "rank": 1,
        "suit": 5,
        "t": "draw"
      },
      {
        "clues": 2,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 1,
        "num": 34,
        "t": "turn"
      },
      {
        "giver": 1,
        "kind": "C",
        "list": [
          13,
          10
        ],
        "t": "clue",
        "target": 2,
        "value": 3
      },
      {
        "clues": 1,
        "max": 25,
        "score": 0,
        "t": "status"
      },
      {
        "cpi": 2,
        "num": 35,
        "t": "turn"
      }
    ],
    "all_plays": false,
    "convention": "tiiah",
    "deck": [
      [
        0,
        4
      ],
      [
        0,
        3
      ],
      [
        3,
        2
      ],
      [
        0,
        3
      ],
      [
        3,
        1
      ],
      [
        4,
        1
      ],
      null,
      [
        1,
        4
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
        3,
        4
      ],
      [
        2,
        1
      ],
      [
        1,
        5
      ],
      [
        3,
        5
      ],
      [
        3,
        1
      ],
      [
        4,
        3
      ],
      [
        4,
        2
      ],
      [
        2,
        4
      ],
      null,
      [
        4,
        4
      ],
      [
        5,
        3
      ],
      [
        4,
        5
      ],
      null,
      [
        2,
        4
      ],
      [
        2,
        3
      ],
      [
        3,
        3
      ],
      [
        1,
        1
      ],
      null,
      [
        0,
        1
      ],
      [
        3,
        1
      ],
      [
        0,
        5
      ],
      null,
      [
        3,
        2
      ],
      [
        1,
        4
      ],
      [
        5,
        1
      ],
      [
        3,
        3
      ]
    ],
    "names": [
      "sim-alice",
      "sim-bob",
      "sim-cathy"
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
      "variant_name": "Throw It in a Hole & Black (6 Suits)"
    },
    "our_player_index": 1,
    "rlocks": true,
    "variant": "Throw It in a Hole & Black (6 Suits)"
  },
  "ts": "2026-10-11T04:37:03.981",
  "turn": 36
}
  )json";

}  // namespace

// Rung 3.5b: a play clue on Bob's critical, playable chop beats the lock.
TEST(TiiahSelfPlay9000159, BlackPlaysTheCriticalChopInsteadOfALock) {
  hanabi::Game game = hanabi::logging::apply_snapshot(nlohmann::json::parse(kCathyT36));
  ASSERT_EQ(game.convention, hanabi::Convention::TIIAH);
  ASSERT_EQ(game.state.clue_tokens, 1);
  const hanabi::PerformAction action = game.take_action();
  const auto* colour = std::get_if<hanabi::PerformColour>(&action);
  ASSERT_NE(colour, nullptr) << "it locked sim-alice with a 5 here before";
  EXPECT_EQ(colour->target, 0);
  EXPECT_EQ(colour->value, kBlack);
}

// The user's line from there: the Black, sim-alice plays the k1 and draws, and
// sim-bob -- locked, at 0 clues -- throws o7, his known y4, whose other copy he can
// see in sim-cathy's hand (o33).
TEST(TiiahSelfPlay9000159, ALockedBobAtZeroCluesThrowsTheY4HeSeesAgain) {
  hanabi::Game g = hanabi::logging::apply_snapshot(nlohmann::json::parse(kBobT36));
  ASSERT_EQ(g.convention, hanabi::Convention::TIIAH);
  ASSERT_EQ(g.state.our_player_index, 1);
  g.catchup = true;
  const auto touched =
      g.state.clue_touched(g.state.hands[0], hanabi::ClueKind::COLOUR, kBlack);
  g.handle_action(hanabi::ClueAction{2, 0, touched,
                                     hanabi::BaseClue{hanabi::ClueKind::COLOUR, kBlack}});
  g.handle_action(hanabi::TurnAction{g.state.turn_count, 0});
  g.handle_action(hanabi::PlayAction{0, 34, -1, -1});  // the k1, into the hole
  // The next card of seed 159's deck (`self_play --print-decks`): o35 b3, o36 k5, o37 r1.
  const int next = g.state.next_card_order;
  const hanabi::Identity drawn = next == 35   ? hanabi::Identity{3, 3}
                                 : next == 36 ? hanabi::Identity{5, 5}
                                              : hanabi::Identity{0, 1};
  ASSERT_GE(next, 35);
  ASSERT_LE(next, 37);
  g.handle_action(hanabi::DrawAction{0, next, drawn.suit_index, drawn.rank});
  g.handle_action(hanabi::TurnAction{g.state.turn_count, 1});
  g.catchup = false;
  ASSERT_EQ(g.state.clue_tokens, 0);
  ASSERT_TRUE(g.common.thinks_locked(g, 1)) << "guard: sim-bob is locked";
  const hanabi::PerformAction action = g.take_action();
  const auto* discard = std::get_if<hanabi::PerformDiscard>(&action);
  ASSERT_NE(discard, nullptr);
  EXPECT_EQ(discard->target, 7) << "the y4, not o27 {y3,p3} for its share of trash";
}
