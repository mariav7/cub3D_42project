/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:41:46 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/14 20:16:49 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/******************************************************************************/
/*                                                                            */
/*                                LIBS                                        */
/*                                                                            */
/******************************************************************************/

//# include <mlx.h>
# include "../mlx/mlx.h"
# include "../list/list.h"
# include <X11/X.h>
# include <libft.h>
# include <ft_printf.h>
# include <gnl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>

/******************************************************************************/
/*                                                                            */
/*                                MACROS                                      */
/*                                                                            */
/******************************************************************************/

/* GENERAL MACROS */
# define WIN1_SX 1280
# define WIN1_SY 720
# define FILE_TYPE ".cub"
# define TITLE "Cub3D"

/* KEYS */
# define LOOK_LEFT 65361
# define LOOK_RIGHT 65363
# define MOVE_LEFT 97
# define MOVE_RIGHT 100
# define MOVE_FORWARD 119
# define MOVE_BACKWARDS 115
# define ESCAPE 65307

/* ERROR MESSAGES */
# define ERR_USAGE "Usage: ./cub3d map.cub"
# define ERR_MSG "Error"
# define ERR_CALLOC "Calloc: could not allocate memory"
# define ERR_MALLOC "Malloc: could not allocate memory"
# define ERR_FILE "File: invalid file type, [.cub] needed"
# define ERR_ISDIR "File: is a directory"
# define ERR_FILE_NOTFOUND "File"
# define ERR_FILE_EMPTY "File: is empty"
# define ERR_MLX "Minilibx: initialization failed"
# define ERR_MLX_WIN "Minilibx: new window failed"
# define ERR_MLX_IMG "Minilibx: new image failed"
# define ERR_TEX_INVALID "File: invalid texture(s)"
# define ERR_COLOR_INVALID "File: invalid floor/ceiling RGB color(s)"

/* COLORS */
# define DEFAULT "\001\e[00;39m\002"
# define GREY "\001\e[1;90m\002"
# define RED "\001\e[1;31m\002"
# define GREEN "\001\e[1;32m\002"
# define YELLOW "\001\e[1;33m\002"
# define BLUE "\001\e[1;34m\002"
# define PURPLE "\001\e[1;35m\002"
# define CYAN "\001\e[1;36m\002"
# define WHITE "\001\e[1;37m\002"

/* VIEW SETTINGS */

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define NUM_TEXTURES 2
# define TILE_SIZE_TEXTURE 64
# define FOV 90

/* PLAYER SETTINGS */
# define PLAYER_MOVE 1.0

/* FLOATS */
# define X 0
# define Y 1
# define ANGLE 2
# define RAY_ANGLE 3
# define DISTANCE_TO_WALL 4
# define RAY_DIR_X 5
# define RAY_DIR_Y 6
# define STEP_X 7
# define STEP_Y 8
# define DELTA_X 9
# define DELTA_Y 10
# define X_POS 11
# define Y_POS 12

/* INTS */
# define HIT_WALL 0
# define WALL_HEIGHT 1
# define WALL_TEXTURE 2
# define MAP_X 3
# define MAP_Y 4

/******************************************************************************/
/*                                                                            */
/*                              STRUCTURES                                    */
/*                                                                            */
/******************************************************************************/

typedef struct s_map	t_map;
typedef struct s_tex	t_tex;
typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_view	t_view;

struct s_player
{
	float floats[13];
    int ints[5];
};

struct s_map
{
	int		height;
	int		width;
	int		fd;
	char	*path;
	char	*file;
};

struct s_tex
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	int				*flo;
	int				*ce;
};

struct s_view
{
	//t_list	*textures;
	int 	textures[NUM_TEXTURES][TILE_SIZE_TEXTURE * TILE_SIZE_TEXTURE];
	void 	*mlx_ptr;
	void 	*win_ptr;
	void 	*img_ptr;
	int 	*buffer[SCREEN_HEIGHT];
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char 	*addr;
};

struct s_data
{
	int			map[10][10];
	t_view		*view;
	t_map		*map_after;
	t_tex		*tex;
	t_player	*player;
};

/******************************************************************************/
/*                                                                            */
/*                               PROTOTYPES                                   */
/*                                                                            */
/******************************************************************************/

/*------------------------------ GAME ----------------------------------------*/

//void	will_hit(t_data *d);

/*------------------------------ END GAME ------------------------------------*/

/*------------------------------ VIEW ----------------------------------------*/

void	view_hooks(t_data *d);

/*------------------------------ END VIEW ------------------------------------*/

/*------------------------------ DEBUG ---------------------------------------*/

/* print_structs.c */
void    	debug(t_data *d);

/*------------------------------ END DEBUG -----------------------------------*/

/* main.c */
int			key_event(int key_code, t_data *d);
int			close_window(t_data *d);

/*------------------------------ INIT ----------------------------------------*/

/* init.c */
void		init_structs(t_data **d, int fd, char *file);
void 		view_init(t_data *d);
void		start_game(t_data *d);

/*------------------------------ END INIT ------------------------------------*/

/*------------------------------ PARSING -------------------------------------*/

/* check_file.c */
int			check_file(int ac, char **av);

/* parsing.c */
void		parse_file(t_data **d);

/* fill_colors.c */
int			fill_colors(t_tex *tex, char *line, int *j);

/* parsing_utils.c */
long long	ft_atoll(const char *str);

/*------------------------------ END PARSING ---------------------------------*/

/*------------------------------ UTILS ---------------------------------------*/

/* exit_utils.c */
void		free_tab(void **tab);
void		basic_error_message(char *err, void *free_this, int fd);
void		error_exit(t_data *d, char *err, void *free_this);
void		free_n_exit_safe(t_data *d);

/*------------------------------ END UTILS -----------------------------------*/

#endif
