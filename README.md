# So Long... and Thanks for All the Fish

A small 2D top-down game built in C using the MiniLibX graphics library, as part of the 42 school curriculum.

## Table of Contents

- [How to play](#how-to-play)
- [Getting started](#getting-started)
- [Map format](#map-format)
- [Enemies](#enemies)
- [Code organization](#code-organization)
  - [Programme input](#programme-input)
  - [Map validation](#map-validation)
  - [Init resources](#init-resources)
  - [Key hooks](#key-hooks)
  - [Movements](#movements)

---

## How to Play

You control a character navigating a tile-based 2D world. Your goal is simple:

> **Collect every collectible on the map, then reach the exit.**

- Move using `W A S D` or the arrow keys.
- You **cannot** walk through walls.
- Every time you move, the current **step count** is printed in the terminal.
- The step count is also shown **on screen** in the top-left corner.
- The exit only opens once **all collectibles have been picked up** — stepping on it before that does nothing.
- If you step on an **enemy patrol** (`D`), you lose immediately.
- Press `ESC` or close the window to quit at any time.

The game does not run in real time — nothing moves unless you press a key.

---

## Getting Started

### Requirements

- Linux (or macOS with adapted MiniLibX)
- A C compiler (`gcc`)
- X11 libraries: `libXext`, `libX11`

### Build

```bash
make
```

### Run

```bash
./so_long maps/your_map.ber
```

The program takes exactly one argument: a path to a `.ber` map file.

### Clean

```bash
make clean    # removes object files
make fclean   # removes object files and the binary
make re       # full rebuild
```

---

## Map Format

Maps are plain text files with the `.ber` extension. They must follow these rules:

| Character | Meaning                  |
|:---------:|--------------------------|
| `0`       | Empty floor              |
| `1`       | Wall (impassable)        |
| `C`       | Collectible (pick up all)|
| `E`       | Exit (reach after all C) |
| `P`       | Player starting position |
| `D`       | Enemy patrol *(bonus)*   |

### Validity rules

- The map must be **rectangular** — all rows the same length.
- The entire **perimeter must be walls** (`1`) — no open edges.
- There must be **exactly 1 player** (`P`) and **exactly 1 exit** (`E`).
- There must be **at least 1 collectible** (`C`).
- There must be a **valid path** from `P` to `E` passing through all `C` tiles.
- Any invalid map causes the program to exit cleanly with an error message.

### Example — minimal valid map

```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

### Example — larger map with enemies

```
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00D0000000000000000000C1
1111111111111111111111111111111111
```

---

## Enemies

Tiles marked `D` represent **enemy patrols**. They are static obstacles:

- The player **loses immediately** upon stepping onto a `D` tile.
- During **map validation**, `D` tiles are treated as walls — the flood-fill path checker will not cross them, so a valid path must exist that avoids all enemies.
- Enemies have a **sprite animation** (like the player), cycling through frames each render tick.

---

## Code Organization

### Programme Input

The entry point (`main` in [so_long.c](so_long.c)) does the following in order:

1. Checks that exactly one argument is provided.
2. Validates the file extension is `.ber`.
3. Loads and validates the map.
4. Initializes the MiniLibX connection and window.
5. Starts the event loop.

### Map Validation

Handled across [map_loader.c](map_loader.c), [map_checker.c](map_checker.c), [map_checker_utils.c](map_checker_utils.c), and [map_path_check.c](map_path_check.c):

1. **Load** — reads the file into a string, splits into a `char **` grid.
2. **Character check** — only `0 1 C E P D \n` are allowed; rows must all be the same length.
3. **Edge check** — every cell on the perimeter must be `1`.
4. **Object count** — exactly 1 `P`, exactly 1 `E`, at least 1 `C`.
5. **Path check** — a recursive flood-fill from `P` verifies that all `C` tiles and `E` are reachable (enemies and walls block the flood).

### Init Resources

Handled in [gui_handler.c](gui_handler.c):

- Opens a MiniLibX connection and retrieves screen dimensions.
- Checks the map fits on screen.
- Creates the window sized to `map_width × 64` by `map_height × 64` pixels.
- Loads all sprite images (wall, floor, collectible, exit, player, patrol).
- Animated objects (`P`, `D`) load a circular linked list of frames that cycle each render tick.

### Key Hooks

| Event | ID | Hook used |
|---|---|---|
| Key release | 3 | `mlx_key_hook()` |
| Close window | 17 | `mlx_hook()` |
| Render loop | — | `mlx_loop_hook()` |

### Movements

Two control schemes are supported simultaneously:

| Direction | Key 1 | Key 2  |
|:---------:|:-----:|:------:|
| Up        | `W`   | `↑`    |
| Down      | `S`   | `↓`    |
| Left      | `A`   | `←`    |
| Right     | `D`   | `→`    |
| Quit      | `ESC` | *(window × button)* |

Each keypress triggers [moves.c](moves.c), which:

1. Computes the target cell from the current position + direction.
2. Checks what is on that cell (`0`, `1`, `C`, `E`, `D`).
3. Acts accordingly — blocks on walls, collects on `C`, loses on `D`, wins on `E` if all collected.
4. Updates the player position in the map grid and prints the step count.

<p style="text-align:right;">
  <a href="#so-long-and-thanks-for-all-the-fish">Go to the top</a>
</p>
