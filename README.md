# ♟️ Chess Game - Terminal-Based Chess Engine in C

[![C](https://img.shields.io/badge/C-99-blue?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Linux](https://img.shields.io/badge/Linux-Ready-red?style=flat-square&logo=linux)](https://www.linux.org/)
[![License](https://img.shields.io/badge/License-MIT-black?style=flat-square)](LICENSE)

> A fully-functional, console-based chess game implementation in C supporting two-player gameplay, complete chess rules, move validation, undo/redo functionality, and game state persistence.

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Tech Stack](#-tech-stack)
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [How to Play](#-how-to-play)
- [Game Rules Implementation](#-game-rules-implementation)
- [Architecture](#-architecture)
- [Commands Reference](#-commands-reference)
- [Future Enhancements](#-future-enhancements)
- [License](#-license)

---

## 📊 Overview

This is a comprehensive chess game engine built from scratch in C. It implements the complete set of chess rules, including special moves (castling, en passant) and game-ending conditions (checkmate, stalemate, draw).

**Key Achievement**: Full chess rule implementation with move validation, check/checkmate detection, and game state management in ~2000 lines of C code.

---

## ✨ Features

### ♟️ Game Mechanics

| Feature | Description |
|---------|-------------|
| **Two-Player Mode** | Human vs Human gameplay on same terminal |
| **Full Chess Board** | Standard 8x8 board with all pieces correctly positioned |
| **All Piece Types** | Pawn, Rook, Knight, Bishop, Queen, King |
| **Piece Movement** | Each piece follows standard chess movement rules |
| **Move Validation** | Automatic verification that moves are legal |
| **Capture System** | Capture opponent pieces and track captured pieces |

### 🎯 Special Moves

| Move | Implementation | Description |
|------|-----------------|-------------|
| **Castling** | ✅ Implemented | King + Rook special move |
| **En Passant** | ✅ Implemented | Pawn special capture |
| **Pawn Promotion** | ✅ Implemented | Promote to Queen/Rook/Bishop/Knight |
| **Check Detection** | ✅ Implemented | Identifies threatening moves |
| **Checkmate** | ✅ Implemented | Game-ending condition |

### 🎮 Game Management

| Feature | Description |
|---------|-------------|
| **Save Game** | Persist game state to file for later resumption |
| **Load Game** | Resume previously saved games |
| **Undo Moves** | Go back to previous board state |
| **Redo Moves** | Go forward to undone board state |
| **Resign** | Allow player to concede defeat |
| **Draw Offer** | Propose and accept draws |
| **Move History** | Track all moves made in game |

### 🏁 Game-Ending Conditions

- **Checkmate**: One player has no legal moves and is in check
- **Stalemate**: One player has no legal moves but is not in check
- **Draw by Agreement**: Both players agree to draw
- **Resignation**: One player gives up
- **Insufficient Material**: Not enough pieces to checkmate

---

## 🛠️ Tech Stack

| Component | Technology |
|-----------|-----------|
| **Language** | C (C99 standard) |
| **Compiler** | GCC, Clang |
| **Build Tool** | Make |
| **Platform** | Linux/Mac/Windows (MinGW) |
| **Memory Management** | Manual (malloc/free) |
| **Storage** | File I/O for saving games |

---

## 📂 Project Structure

```plaintext
Chess/
├── Makefile                      # Build configuration
├── README.md                     # This file
│
├── src/                          # Source code
│   ├── main.c                   # Entry point & game loop
│   ├── board.c                  # Board initialization & display
│   ├── board.h
│   ├── move.c                   # Move validation logic
│   ├── move.h
│   ├── pieces.c                 # Piece movement rules
│   ├── pieces.h
│   ├── check.c                  # Check/checkmate detection
│   ├── check.h
│   ├── game.c                   # Game state management
│   ├── game.h
│   ├── io.c                     # User input/output
│   ├── io.h
│   ├── file_io.c               # Save/load game
│   ├── file_io.h
│   └── util.c                   # Utility functions
│       └── util.h
│
├── pieces/                       # Individual piece logic
│   ├── pawn.c
│   ├── pawn.h
│   ├── rook.c
│   ├── rook.h
│   ├── knight.c
│   ├── knight.h
│   ├── bishop.c
│   ├── bishop.h
│   ├── queen.c
│   ├── queen.h
│   ├── king.c
│   └── king.h
│
├── headers/                      # Global definitions
│   ├── types.h                  # Data structure definitions
│   ├── constants.h              # Game constants
│   └── config.h                 # Configuration options
│
├── tests/                        # Unit tests
│   ├── test_board.c
│   ├── test_moves.c
│   ├── test_check.c
│   └── test_pieces.c
│
├── docs/                         # Documentation
│   ├── game_rules.md            # Detailed game rules
│   ├── architecture.md          # System architecture
│   └── testing_guide.md         # Testing instructions
│
└── games/                        # Saved game files
    └── game_1.chess            # Example saved game
```

---

## 🚀 Installation

### Prerequisites

- **GCC or Clang compiler**
- **Make build tool**
- **Linux/Mac terminal** or **Windows (MinGW)**

### Linux/Mac Installation

1. **Clone repository**:
   ```bash
   git clone https://github.com/Ahmed122000/chess.git
   cd chess
   ```

2. **Compile project**:
   ```bash
   make
   ```
   This generates the `chess` executable.

3. **Run game**:
   ```bash
   make run
   # Or directly:
   ./chess
   ```

4. **Clean build artifacts**:
   ```bash
   make clean
   ```

### Windows Installation (MinGW)

1. Install MinGW with GCC compiler
2. Clone repository:
   ```bash
   git clone https://github.com/Ahmed122000/chess.git
   cd chess
   ```

3. Compile:
   ```bash
   gcc -o chess src/*.c pieces/*.c -lm
   ```

4. Run:
   ```bash
   chess.exe
   ```

---

## 🎮 How to Play

### Starting a Game

```
$ ./chess

    ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
    ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟
    . . . . . . . .
    . . . . . . . .
    . . . . . . . .
    . . . . . . . .
    ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙
    ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖

White's turn. Enter move or command:
```

### Move Format

Moves are entered as coordinates in the format: `[SOURCE] [DESTINATION]`

**Examples**:
```
A2 A3     # Pawn moves from A2 to A3
E2 E4     # Pawn moves from E2 to E4 (two squares)
E1 G1     # White castles kingside
B8 C6     # Knight moves from B8 to C6
```

**Format**:
- Column: A-H (left to right)
- Row: 1-8 (bottom to top)
- Case insensitive: `a2 a3` or `A2 A3`

---

### Special Commands

| Command | Action |
|---------|--------|
| `S` or `SAVE` | Save current game |
| `L` or `LOAD` | Load previously saved game |
| `RE` or `RESIGN` | Concede defeat (other player wins) |
| `DRAW` | Offer/accept draw |
| `U` or `UNDO` | Undo last move |
| `R` or `REDO` | Redo previously undone move |
| `H` or `HELP` | Display help message |
| `Q` or `QUIT` | Exit game |

---

### Example Game Session

```
$ ./chess

8 ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜ 8
7 ♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟ 7
6 . . . . . . . . 6
5 . . . . . . . . 5
4 . . . . . . . . 4
3 . . . . . . . . 3
2 ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙ 2
1 ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖ 1
  A B C D E F G H

White's turn. Enter move (e.g., E2 E4):
E2 E4

Black's turn. Enter move:
E7 E5

White's turn. Enter move:
G1 F3

[Game continues...]
```

---

## ♟️ Game Rules Implementation

### Pawn Rules ✅

- **Movement**: Forward one square (or two on first move)
- **Capture**: Diagonally forward
- **En Passant**: Special capture of adjacent pawn
- **Promotion**: Becomes Queen/Rook/Bishop/Knight on reaching 8th rank

### Rook Rules ✅

- **Movement**: Any number of squares horizontally or vertically
- **Capture**: Same as movement
- **Blocking**: Cannot move through other pieces

### Knight Rules ✅

- **Movement**: L-shaped (2+1 squares)
- **Jumping**: Can jump over other pieces
- **Capture**: Move to square with opponent piece

### Bishop Rules ✅

- **Movement**: Any number of squares diagonally
- **Capture**: Same as movement
- **Color Constraint**: Stays on same color squares

### Queen Rules ✅

- **Movement**: Combines rook + bishop
- **Movement Squares**: Horizontal, vertical, diagonal
- **Range**: Any number of squares

### King Rules ✅

- **Movement**: One square in any direction
- **Castling**: Special move with rook (kingside/queenside)
- **Check**: Cannot move into check

### Special Rules ✅

| Rule | Implementation |
|------|-----------------|
| **Check** | King is under attack; player must respond |
| **Checkmate** | King is in check with no legal moves; opponent wins |
| **Stalemate** | Player has no legal moves but not in check; draw |
| **Castling** | Kingside (O-O) and queenside (O-O-O) |
| **En Passant** | Pawn captures adjacent pawn's double advance |
| **Pawn Promotion** | Pawn reaching 8th/1st rank becomes queen/other piece |
| **Draw by 50-Move Rule** | 50 moves without capture/pawn move |
| **Three-Fold Repetition** | Same position occurs 3 times |

---

## 🏗️ Architecture

### Data Structures

#### Piece Structure
```c
typedef struct {
    char type;      // 'P', 'R', 'N', 'B', 'Q', 'K'
    char color;     // 'W' (White) or 'B' (Black)
    int moves;      // Number of times moved
    int row, col;   // Current position
} Piece;
```

#### Board Structure
```c
typedef struct {
    Piece board[8][8];
    int white_castled;
    int black_castled;
    Piece captured[32];  // Track captured pieces
    int move_count;
} GameBoard;
```

#### Move Structure
```c
typedef struct {
    int from_row, from_col;
    int to_row, to_col;
    char piece_type;
    int is_capture;
    int is_check;
} Move;
```

### Module Architecture

```
┌─────────────────┐
│   main.c        │ (Game Loop)
└────────┬────────┘
         │
    ┌────┴─────────┬────────────────┐
    ▼              ▼                ▼
┌────────┐    ┌────────┐       ┌──────────┐
│ move.c │    │game.c  │       │ check.c  │
└────┬───┘    └───┬────┘       └────┬─────┘
     │            │                 │
     └────────────┴─────────────────┘
              │
         ┌────┴────────────┐
         ▼                 ▼
    ┌────────┐        ┌──────────┐
    │pieces/ │        │file_io.c │
    │*.c     │        └──────────┘
    └────────┘
```

---

## 🧪 Testing

### Run Tests
```bash
make test
```

### Test Cases
- Board initialization
- Move validation for each piece
- Check detection
- Checkmate detection
- Save/load game state
- Undo/redo functionality

---

## 🐛 Troubleshooting

### Issue: "Command not found: make"
**Solution**: Install build-essential
```bash
sudo apt-get install build-essential  # Linux
brew install make                      # Mac
```

### Issue: Chess pieces don't display correctly
**Solution**: Use terminal with UTF-8 support
```bash
export LANG=en_US.UTF-8
```

### Issue: File not found when saving
**Solution**: Create `games/` directory
```bash
mkdir -p games
```

---

## 📈 Future Enhancements

- [ ] AI opponent (minimax algorithm)
- [ ] ELO rating system
- [ ] Move time tracking
- [ ] Graphical UI (Ncurses)
- [ ] Network play (TCP/IP)
- [ ] Chess notation (PGN format)
- [ ] Endgame tablebases
- [ ] Performance analysis
- [ ] Game tutorials
- [ ] Multiple languages

---

## 📝 Contributing

1. Fork repository
2. Create feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open Pull Request

---

## 📄 License

This project is licensed under the **MIT License** - see [LICENSE](LICENSE) for details.

---

## 🙏 Acknowledgments

- [Wikipedia Chess Rules](https://en.wikipedia.org/wiki/Rules_of_chess) for rules reference
- [Coding Game Archive](https://www.codingame.com/) for inspiration
- Community feedback and contributions

---

## 👨‍💻 Authors

**Ahmed Hesham** - [@Ahmed122000](https://github.com/Ahmed122000)
**Ayman Mohamed** - [@Eng-Ayman-Mohamed](https://github.com/Eng-Ayman-Mohamed)

**Built with ❤️ for learning C programming and game development**
