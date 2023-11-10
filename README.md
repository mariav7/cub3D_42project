<div align="center">

![Demo:](misc/demo.gif)

---
Coded with 💗 by: [mflores-](https://github.com/mariav7) and [nmunoz](https://github.com/nmunoz)

</div>

## Project

[**Subject PDF**](misc/en.subject.pdf)

The purpose of cub3D is to render a 3D maze in [C](https://en.cppreference.com/w/c/language) using the graphic library [miniLibX](https://github.com/42Paris/minilibx-linux) and using [raycasting](https://en.wikipedia.org/wiki/Ray_casting), inspired by the iconic game [Wolfenstein3D](https://www.snokido.fr/jeu/wolfenstein-3d).

The project encourages a deep understanding of graphics programming and serves as a hands-on exploration of classic video game rendering techniques.

---

## Supported feautures

The project's requirements:
* Keys to move:
  * `W` move forward
  * `A` move left
  * `S` move backward
  * `D` move right
  * `⬅️` rotate left
  * `➡️` rotate right
* To exit:
  * press the `ESC` button
  * click the `X` on the window
* Map files must be (`.cub`) type
* Valid maps must be composed of the following characters only:
  * `0` for an empty space
  * `1` for walls
  * `N` or `S` or `W` or `E` for the player's view starting position (North, South, West, East)
* Maps must be closed/surrounded by walls

---

## Installation

**Clone repository and compile program:**
```bash
git clone git@github.com:mariav7/cub3D_42project.git
cd cub3D_42project && make
```

**Run the program:**
```bash
./cub3D maps/map1.ber
```

**Run the program with valgrind to test for leaks:**
```bash
chmod +xr leak_test.sh && ./leak_test.sh
```

---