#! /bin/bash

RED=$'\033[0;91m'
YELLOW=$'\033[0;93m'
GREEN=$'\033[0;32m'
RESET=$'\033[0m'

# run cub3D program with valgrind
if ! command -v valgrind &> /dev/null
then
    echo -e "${RED}Error: valgrind could not be found.\n${YELLOW}Please install valgrind before re-launching the script.${RESET}"
    exit 1
else
    make && valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D maps/map1.cub
fi