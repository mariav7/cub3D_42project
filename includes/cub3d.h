/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmunoz   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 03:32:44 by nmunoz            #+#    #+#             */
/*   Updated: 2023/04/25 03:32:44 by nmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INCLUDES_CUB3D_H
#define INCLUDES_CUB3D_H

# include "../list/list.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <math.h>

# define screenWidth 640
# define screenHeight 480
# define mapWidth 24
# define mapHeight 24

enum double_data {
	CAMERA_X = 0,
	RAY_DIR_X,
	RAY_DIR_Y,
	SIDE_DIST_X,
	SIDE_DIST_Y,
	DELTA_DIST_X,
	DELTA_DIST_Y,
	PERP_WALL_DIST
};

enum int_data {
	MAP_X,
	MAP_Y,
	STEP_X,
	STEP_Y,
	HIT,
	SIDE,
	LINE_HEIGHT,
	DRAW_START,
	DRAW_END,
	COLOR
};

typedef struct s_screen_utils {
    int		bits_per_pixel;
	int		line_length;
	int		endian;
	char 	*addr;
} t_screen_utils;

typedef struct s_image
{
	t_img	*holder;
	char	*addr;
} t_image;

typedef struct s_window
{
    void *holder;
} t_window;

typedef struct s_screen
{
    void 		*holder;
    t_window	*window;
    t_image		*img;
    t_screen_utils	*utils;
} t_screen;

typedef struct	s_player
{
	double	move_speed;
	double	rot_speed;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
} t_player;

typedef struct s_map
{
	int		map[mapWidth][mapHeight];
	double	d_data[8];
	int		i_data[10];
} t_map;

typedef struct s_game
{
	t_screen	*screen;
	t_player	*player;
	t_map		*map;
} t_game;


t_screen	*init_screen(int width, int height, char *name);
t_image		*init_image(t_screen *screen, int width, int height);
void		image_put_pixel(t_screen *screen, t_image *image, int x, int y, int color);
void		display_image(t_screen *screen, t_image *image);
t_game 		*init_game(t_screen *screen, t_player *player);
t_player	*init_player(double planeX, double planeY, double posX, double posY);
int			handle_move(int key_code, t_game *game);
void		rotate(t_game *game, int right);
int			exit_game(t_game *game);
t_map		*init_map();
t_image		*draw_map(t_game *game);
void		refresh(t_game *game);

#endif
