# Architecture

Tetris is one C++ program, `tetris`, built from the ten `.cpp` files at the repository root with
SFML for the window, the drawing, the events and the music. There is no namespace and no
subdirectory: every class is a header and a source file side by side.

## Files

```
Makefile              g++ -Wall -Werror -Wextra, -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
main.cpp              window creation, music, the event loop and the state switches
AbstractEntity.h      the Draw / Update interface shared by Board, BlockEntity and Menu
Board.{h,cpp}         the grid, the falling piece, the queue, collisions, lines, score, drawing
BlockEntity.{h,cpp}   one piece: shape matrix, colour, position, fall timer, moves and rotations
EntityFactory.{h,cpp} the seven shapes and the random pick
Menu.{h,cpp}          the menu, pause and game over screens
Config.{h,cpp}        grid size, block size, board origin on screen, current level
ColorManager.{h,cpp}  the palette, one colour per shape plus the border colour
ResourceManager.{h,cpp}  the default font, loaded once
TimeManager.{h,cpp}   the clock between two updates
GameManager.{h,cpp}   the current state
Resources/            arial.ttf, images/ (background, logo, sprites/ buttons), sound/Tetris.ogg
```

## Classes

| Class | Role |
|-------|------|
| `AbstractEntity` | Pure interface: `Draw(window)` and `Update(window)`. |
| `Board` | Owns the 10 by 20 grid of colour indices, the piece in flight, the three next pieces, the score and the lines count; detects collisions, settles pieces, removes full rows, draws everything in game. |
| `BlockEntity` | A piece: a matrix of booleans, a colour index, a column and a row; falls on its own timer, moves left and right inside the grid, rotates by transposing its matrix, draws itself at its board position or at any screen position (for the queue). |
| `EntityFactory` | Holds the seven shape matrices (S, Z, J, O, T, L, I) and creates a `BlockEntity` with a random shape; the colour index is the shape index. |
| `Menu` | Draws the background, the logo, a title (Menu, Pause or Game Over) and two buttons whose sprites depend on the state and on the selected choice. |
| `Config` | Singleton set once from `main`: 10 columns, 20 rows, 40 pixel blocks, the board origin centred horizontally at a tenth of the height, and the level. |
| `ColorManager` | Singleton with eight colours; index 1 to 7 are the pieces, index 8 the border. |
| `ResourceManager` | Singleton that loads `Resources/arial.ttf` on first use. |
| `TimeManager` | Singleton (static local) built on `std::chrono`; `Update()` stamps the frame, `GetElapsedTime()` gives the milliseconds since the previous one. |
| `GameManager` | Singleton holding the state: 0 playing, 1 menu, 2 pause, 3 game over. |

## Game loop

`main` opens a 1920 by 1080 full screen window capped at 60 frames per second, initialises
`Config`, starts the theme in a loop and enters the SFML event loop.

- In a menu state, a mouse wheel step moves the choice between 1 and 2 and Enter applies it:
  from the menu, choice 1 spawns the first piece and starts playing; from the pause, choice 1
  resumes and choice 2 rebuilds the board and returns to the menu; from the game over, choice 1
  rebuilds the board and returns to the menu. Choice 2 on the menu and on the game over screen
  closes the window.
- In the playing state, the arrows, `Z`, `Space` and `P` act on the first entity of the board;
  Escape closes the window.

Each frame clears the window, switches to the game over state if `Board::IsGameEnded()`, then
either updates and draws the board or draws the menu.

## Board update

`Board::Update` stamps the clock, draws the grid, the borders, the next pieces and the score,
then runs `UpdateBlocks`: for the piece in flight it first tests the row below (`TryCollisions`);
a hit on the first row ends the game, any other hit settles the piece into the grid and pulls the
next one from the queue. A piece reaching the bottom row settles the same way. Otherwise
`BlockEntity::Update` adds the elapsed time and drops the piece one row when `1 / level` seconds
have passed. `CheckLines` then removes every full row, shifts the rows above down, and raises the
level every second removed line.

## Scoring

| Event | Points |
|-------|--------|
| Soft drop (Down) | 1 per row |
| Hard drop (Space) | 2 per row |
| 1, 2, 3 or 4 lines at once | 40, 100, 300 or 1200, times the level |

The level starts at 1 and increases by one every two lines removed; the fall delay is `1 / level`
seconds per row, so level 2 is twice as fast as level 1.

## Resources

| File | Used by |
|------|---------|
| `Resources/arial.ttf` | `ResourceManager`, for the score and the menu titles |
| `Resources/images/background.png`, `logo.png` | `Menu` |
| `Resources/images/sprites/*-button.png`, `*-selected.png` | `Menu`, play, resume, menu and exit buttons |
| `Resources/sound/Tetris.ogg` | `main`, looped for the whole session |

All paths are relative, so the binary must be started from the repository root.
