# Shooty c

A simple C++ top-down shooter project for fun and learning.

## Description

Shooty c is a barebones top-down shooter game written in C++ using [SFML](https://www.sfml-dev.org/). The project demonstrates basic game architecture, AI pathfinding with navmeshes, and rendering using SFML.

## Getting Started

### Dependencies

- **C++17 or newer**
- **CMake** (for building)
- **SFML 2.5+** (graphics, window, system)
- A C++ compiler (GCC, Clang, or MSVC)
- (Optional) [Make](https://www.gnu.org/software/make/) for Unix-like systems

### Installing

1. **Clone the repository:**
    ```sh
    git clone https://github.com/yourusername/shooty_c.git
    cd shooty_c
    ```

2. **Install SFML:**
    - On Ubuntu:
        ```sh
        sudo apt-get install libsfml-dev
        ```
    - On Windows: Download and install from [SFML downloads](https://www.sfml-dev.org/download.php).

3. **Check/modify asset paths**  
   Make sure the `assets/` folder is in the project root and contains:
   - `fonts/`
   - `navmesh/navmesh.txt`
   - `sprites/`

### Building

From the `src/` directory:

```sh
cd src
cmake .
make
```

This will produce an executable named `main` in the `src/` directory.

### Running

From the `src/` directory:

```sh
./main
```

The game window should open.  
- Use the keyboard to control the player.
- Press `F` to spawn an AI enemy.

### Project Structure

- `src/` — Source code
- `include/` — Header files
- `assets/` — Fonts, sprites, navmesh
- `CMakeLists.txt` — Build configuration

### Example Commands

```sh
# Build
cd src
cmake .
make

# Run
./main
```