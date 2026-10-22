# Development

## Toolchain

- `g++` and `make`.
- SFML with the graphics, window, system and audio modules: `libsfml-dev` on Debian and Ubuntu,
  `sfml` through Homebrew on macOS (the Makefile links the libraries by name, so they must be on
  the default library path).
- A 1920 by 1080 display, since the window opens in full screen at that size.

## Recipes

```sh
make              # compile every .cpp and link ./tetris
make re           # clean and rebuild from scratch
make clean        # remove the object files
make fclean       # remove the object files and the binary
./tetris          # run from the repository root, Resources/ is loaded by relative path
```

There is no test suite. The compiler flags are `-Wall -Werror -Wextra`; no language standard is
forced, the compiler default applies.

## Known limits

- The resolution is fixed at 1920 by 1080 in `main.cpp`; on another display SFML picks the
  closest full screen mode or fails to open the window.
- Escape in game quits the program directly, without passing through the pause screen.
- The menu reloads its textures from disk at every frame (`Menu::Draw`), which is wasteful but
  harmless at 60 frames per second.
- Settled pieces are deleted through an explicit destructor call rather than `delete`, and the
  boards replaced on restart are the only objects freed: the program relies on the process
  exit to release the rest.
