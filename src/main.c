/*
Copyright (c) 2004-2021, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <math.h>
#include "../includes/cub3d.h"

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:


#define title "Hola"



int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

int main(void)
{
	t_game *game = init_game(
			init_screen(screenWidth, screenHeight, title),
			init_player(0, 0.66, 22, 12)
	);
	if (!game)
		return 1;
	if(game->screen->img != 0)
		  mlx_clear_window(game->screen->holder, game->screen->window->holder);
	game->screen->img = draw_map(game);
	if(!game->screen->img)
		return (1);
	display_image(game->screen, game->screen->img);
	mlx_hook(game->screen->window->holder, 2, KeyPressMask, exit_game, game);
	mlx_hook(game->screen->window->holder, 17, KeyPressMask, exit_game, game);
	mlx_hook(game->screen->window->holder, 2, 1L << 0, handle_move, game);
	//exit_game(game);
	mlx_loop(game->screen->holder);
  return 0;
}
