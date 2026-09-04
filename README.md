# Cub3D

A 3D graphical project developed in C using **raycasting** and the **MiniLibX** graphical library, inspired by the early 3D games such as *Wolfenstein 3D*.

This project is part of the **42 curriculum** and focuses on understanding how a 2D map can be transformed into a real-time 3D-like environment using mathematical calculations and raycasting.

## 🎮 About the Project

**Cub3D** consists of creating a first-person 3D environment from a 2D map.

The player can move through the map and look around while the program calculates the walls visible from the player's position using **raycasting**.

The project combines:

* C programming
* Mathematics
* Raycasting
* 2D map parsing
* Texture management
* Real-time rendering
* Keyboard and window events
* Memory management

## ✨ Features

* First-person 3D-style view.
* Raycasting-based rendering.
* Player movement.
* Camera rotation.
* Wall collision detection.
* Textured walls.
* Different textures depending on wall orientation.
* Map parsing and validation.
* `.cub` configuration file parsing.
* Window and keyboard event handling.
* Error handling.
* Proper resource and memory management.

## 🧭 How Raycasting Works

The game world is represented by a **2D map**, but the player sees it as a 3D environment.

For each vertical column of the screen, a ray is cast from the player's position in the direction of the camera.

The program calculates:

1. The direction of the ray.
2. The first wall hit by the ray.
3. The distance between the player and the wall.
4. The height of the wall on the screen.
5. The corresponding wall texture.
6. The portion of the texture that should be displayed.

This process is repeated for each vertical column of the window to create the final 3D perspective.

## 🗺️ Map & Configuration

The game is launched using a `.cub` configuration file.

The file contains information such as:

* North texture
* South texture
* West texture
* East texture
* Floor color
* Ceiling color
* Game map

Example:

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

### Map Characters

| Symbol | Meaning             |
| ------ | ------------------- |
| `1`    | Wall                |
| `0`    | Empty space         |
| `N`    | Player facing North |
| `S`    | Player facing South |
| `E`    | Player facing East  |
| `W`    | Player facing West  |

The map must respect the project's validity requirements, including being properly enclosed by walls and containing a valid player position.

## 🕹️ Controls

| Key   | Action              |
| ----- | ------------------- |
| `W`   | Move forward        |
| `S`   | Move backward       |
| `A`   | Move left           |
| `D`   | Move right          |
| `←`   | Rotate camera left  |
| `→`   | Rotate camera right |
| `ESC` | Exit the game       |

## 🛠️ Technologies

* **C**
* **MiniLibX**
* **Raycasting**
* **Makefile**
* **Git**
* **Unix/Linux**
* Mathematical calculations using trigonometry

## 🧠 Concepts Practiced

This project allowed me to develop a deeper understanding of:

* Raycasting algorithms.
* Trigonometry (`sin`, `cos`, etc.).
* Angles and player orientation.
* Vectors and directions.
* Distance calculations.
* Perspective projection.
* 2D grid/map manipulation.
* File parsing.
* Texture loading.
* Event handling.
* Collision detection.
* Dynamic memory allocation.
* Structures and pointers.
* Memory management.
* Graphical programming with MiniLibX.

## 👥 Team Project

This project was developed as a team project with:

**Noura Akebli**
**Oumaima Chachi**

We divided the implementation into different components and worked together to integrate the parsing, rendering, player movement, textures, and raycasting system into a functional 3D environment.

## 🚀 Installation

Clone the repository:

```bash
git clone <repository-url>
cd Cub3D
```

Compile the project:

```bash
make
```

## ▶️ Usage

Run the game with a valid `.cub` configuration file:

```bash
./cub3D path/to/map.cub
```

Example:

```bash
./cub3D maps/map.cub
```

A graphical window will open and display the 3D environment.

## 🧹 Makefile Commands

```bash
make
make clean
make fclean
make re
```

* `make` — compiles the project.
* `make clean` — removes object files.
* `make fclean` — removes object files and the executable.
* `make re` — cleans and recompiles the project.

## 📁 Project Structure

```text
Cub3D/
├── Makefile
├── includes/
│   └── cub3d.h
├── src/
│   ├── parsing/
│   ├── raycasting/
│   ├── rendering/
│   ├── movement/
│   ├── textures/
│   └── ...
├── maps/
│   └── *.cub
├── textures/
│   └── ...
└── README.md
```

> The exact organization may vary depending on the implementation.

## 🎯 Project Objective

The main objective of **Cub3D** was to understand the fundamental principles behind early 3D graphics engines and implement a simplified raycasting engine from scratch in C.

The project required combining **mathematics, algorithms, parsing and graphical programming** to transform a 2D map into an interactive 3D environment.

## 👤 Authors

**Noura Akebli**
**Oumaima Chachi**

42 Network
