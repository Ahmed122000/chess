
# Chess Game in C

This is a terminal-based chess game implemented in C. It supports standard chess rules and allows two players to play on a single machine. The game supports saving and loading games, resigning, drawing, undoing/redoing moves, and detecting check/checkmate conditions.

## Features
- **Two-player mode**: Play against a friend on the same machine.
- **Full chessboard setup**: All standard chess pieces (Pawn, Rook, Knight, Bishop, Queen, King) are implemented.
- **Game-saving and loading**: Save your game progress and load it later.
- **Undo/Redo moves**: Go back and forth between previous moves.
- **Resign**: Player can resign early to end the game.
- **Draw**: Support for offering and accepting draws.
- **Check detection**: Warns the player if their King is in check.

## Requirements

To run this project, you need:
- A C compiler (like `gcc`).
- Basic development libraries (standard C library).

## Installation

1. **Clone the repository** (or download the project files):

   ```bash
   git clone https://github.com/yourusername/chess_game.git
   cd chess_game
   ```

2. **Compile the project**:

   Run `make` in the project directory to compile the program.

   ```bash
   make
   ```

   This will generate the `chess` executable.

3. **Run the game**:

   Once compiled, you can run the chess game:

   ```bash
   make run
   ```

## How to Play

1. **Board Layout**:
   - The game follows the standard chess rules with an 8x8 grid.
   - Players take turns, with Player 1 (White) going first.

2. **Move Format**:
   - To move a piece, input the starting and ending positions in the form of two pairs of coordinates (e.g., `A2 A3` or `a2 a3`).
   - To save the game, type `S`.
   - To load a saved game, type `L`.
   - To resign, type `RE` (e.g., `re` or `RE`).
   - To offer or accept a draw, type `DRAW`.

3. **Special Commands**:
   - `s` or `S`: Save the game.
   - `l` or `L`: Load the saved game.
   - `RE` or `re`: Resign from the game.
   - `DRAW`: Offer a draw (can be accepted by the other player).
   - `u` or `U`: Undo the previous move.
   - `r` or `R`: Redo a previously undone move.

4. **Game Over**:
   - The game ends when one player wins (by checkmate) or the game is drawn.
   - Players can resign at any time by typing `RE` followed by confirming the action.

## Project Structure

The project is organized as follows:

```
.
├── Makefile                # Build instructions
├── README.md               # This file
├── chess.c                 # Main game logic
├── global.c                # Global variables and functions
├── pieces/                 # Folder for individual chess piece logic (e.g., bishop.c, king.c)
├── utilities/              # Helper functions (e.g., board_controller.c, delay.c)
└── headers/                # Header files for global variables and functions
    ├── pieces/             # Header files for chess pieces
    └── utilities/          # Header files for utilities
```

### Key Files:
- **`main.c`**: Entry point for the game. Controls the game loop.
- **`global.c`**: Stores global variables like the game board, player turn, etc.
- **`pieces/`**: Contains the logic for each chess piece (e.g., `pawn.c`, `king.c`, etc.).
- **`utilities/`**: Helper files for saving/loading games, handling moves, board printing, etc.
- **`Makefile`**: Used to build and clean the project.

## Credits

This project was developed by [Eng: Ahmed Hesham](https://github.com/ahmed122000) & [Eng: Ayman Mohamed](https://github.com/Eng-Ayman-Mohamed)  as a project to practice C programming.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to fork this project and improve upon it! If you find any bugs or have feature suggestions, open an issue or submit a pull request.
