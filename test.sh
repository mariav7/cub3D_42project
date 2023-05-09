#! /bin/bash
make && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/map1.cub