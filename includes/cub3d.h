/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:41:46 by mflores-          #+#    #+#             */
/*   Updated: 2023/05/03 10:38:46 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

/******************************************************************************/
/*                                                                            */
/*                                LIBS                                        */
/*                                                                            */
/******************************************************************************/

// # include <mlx.h>
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include <list.h>
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
# include <errno.h>
# include <string.h>

/******************************************************************************/
/*                                                                            */
/*                                MACROS                                      */
/*                                                                            */
/******************************************************************************/

/* GENERAL MACROS */
# define FILE_TYPE ".cub"
# define TEX_TYPE ".xpm"
# define TITLE "Cub3D"
# define screenWidth 640
# define screenHeight 480
# define mapWidth 24
# define mapHeight 24

/* MINIMAP MACROS */
# define MINIMAP_PIXEL_SIZE 128
# define MINIMAP_VIEW_DIST 4
# define MINIMAP_PLAYER 0x14D7E5
# define MINIMAP_WALL 0x808080
# define MINIMAP_FLOOR 0xE6E6E6
# define MINIMAP_SPACE 0x404040

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
# define ERR_FILE_ISDIR "File: is a directory"
# define ERR_FILE_NOTFOUND "File"
# define ERR_FILE_EMPTY "File: is empty"
# define ERR_FILE_INVALID "File: element(s) missing"
# define ERR_ID_INVALID "File: invalid identifier(s)"
# define ERR_MLX "Minilibx: initialization failed"
# define ERR_MLX_WIN "Minilibx: new window failed"
# define ERR_TEX_FILE "Texture: invalid texture file type, [.xpm] needed"
# define ERR_TEX_ISDIR "Texture: is a directory"
# define ERR_TEX_NOTFOUND "Texture"
# define ERR_COLOR_INVALID "File: invalid floor/ceiling RGB color(s)"
# define ERR_TEXCO_FORMAT "File: invalid format in textures/colors/map"
# define ERR_MAP_ISFIRST "Map: invalid format, map always has to be last"
# define ERR_MAP_INVALID "Map: invalid map"
# define ERR_MAP_NOTCLOSED "Map: invalid, needs to be surrounded by walls"
# define ERR_MAP_CHARS "Map: invalid map characters"
# define ERR_MAP_SPACES "Map: spaces inside map"
# define ERR_MAP_PLAYER "Map: needs 1 player position [N,S,W,E]"
# define ERR_MAP_PATH "Map: player needs space to move"

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

/******************************************************************************/
/*                                                                            */
/*                              STRUCTURES                                    */
/*                                                                            */
/******************************************************************************/

typedef struct s_map			t_map;
typedef struct s_tex			t_tex;
typedef struct s_data			t_data;
typedef struct s_game			t_game;
typedef struct s_screen			t_screen;
typedef struct s_window			t_window;
typedef struct s_image			t_image;
typedef struct s_player			t_player;
typedef struct s_minimap		t_minimap;
typedef struct s_screen_utils	t_screen_utils;
typedef struct s_minimap_img	t_minimap_img;

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

struct s_screen_utils {
    int		bits_per_pixel;
	int		line_length;
	int		endian;
	char 	*addr;
};

struct s_image
{
	t_img	*holder;
	char	*addr;
};

struct s_window
{
    void *holder;
};

struct s_screen
{
    void 		*holder;
    t_window	*window;
    t_image		*img;
    t_screen_utils	*utils;
};

struct	s_player
{
	double	move_speed;
	double	rot_speed;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
};

struct s_game
{
	t_screen	*screen;
	t_player	*player;
};

struct s_map
{
	int		height;
	int		width;
	int		fd;
	char	*path;
	char	**file;
	char	**map;
	int		pos_x;
	int		pos_y;
	char	dir;
	double	d_data[8];
	int		i_data[10];
};

struct s_tex
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	int				*flo;
	int				*ce;
	unsigned long	hex_flo;
	unsigned long	hex_ce;
};

struct s_minimap_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
};

struct s_minimap
{
	char			**map;
	t_minimap_img	*img;
	int				size;
	int				offset_x;
	int				offset_y;
	int				view_dist;
	int				tile_size;
};

struct s_data
{
	t_game	*game;
	t_map	*map;
	t_tex	*tex;
	t_minimap_img	minimap;
};

/******************************************************************************/
/*                                                                            */
/*                               PROTOTYPES                                   */
/*                                                                            */
/******************************************************************************/

/*------------------------------ NICO ---------------------------------------*/

t_screen	*init_screen(int width, int height, char *name);
t_image		*init_image(t_screen *screen, int width, int height);
void		image_put_pixel(t_screen *screen, t_image *image, int x, int y, int color);
void		display_image(t_screen *screen, t_image *image);
t_game 		*init_game(t_screen *screen, t_player *player);
t_player	 *init_player(t_data *d);
int			handle_move(int key_code, t_data *d);
void		rotate(t_game *game, int right);
int			exit_game(t_data *d);
t_image		*draw_map(t_data *d);
void		refresh(t_data *d);
t_list		*list_textures_init();

/*----------------------------- END NICO -------------------------------------*/

/*------------------------------ SCREEN --------------------------------------*/

/* minimap.c */
void			display_minimap(t_data *data);

/*------------------------------ END SCREEN ----------------------------------*/

/*------------------------------ DEBUG ---------------------------------------*/

/* print_structs.c */
void			print_struct_textures(t_tex *t);
void			print_struct_map(t_map *m);
void			debug(t_data *d);

/*------------------------------ END DEBUG -----------------------------------*/

/*------------------------------ INIT ----------------------------------------*/

/* init.c */
void			init_structs(t_data **d, int fd, char *file);
void			start_game(t_data *d);

/*------------------------------ END INIT ------------------------------------*/

/*------------------------------ PARSING -------------------------------------*/

/* check_file.c */
int				file_ext(char *file, char *file_ext);
int				is_file_dir(char *file);
int				check_file(int ac, char **av);

/* parsing.c */
void			parse_file(t_data **d);

/* parsing_utils.c */
int				has_only_spaces(char *str);
int				is_special_char(char c, int check_zero);
void			ignore_spaces(char *str, int *index, int add);
long long		ft_atoll(const char *str);
unsigned long	rgb_to_hex(int *rgb);

/* textures.c */
int				fill_textures(t_tex *tex, char *line, int *i);
int				check_textures(t_data **d, char **err_msg);

/* colors.c */
int				fill_colors(t_tex *tex, char *line, int *i, char **err_msg);

/* fill_map.c */
void			fill_map(int *i, int nb_line, t_data **d);

/* check_map.c */
int				check_map(t_map *m, char **err_msg);

/* map_utlis.c */
int				check_between_walls(t_map *map, int i, int x, int j);
int				ft_check_chars(char *str, char const *set);
size_t			ft_strlend(const char *s);

/*------------------------------ END PARSING ---------------------------------*/

/*------------------------------ UTILS ---------------------------------------*/

/* exit_utils.c */
void			free_tab(void **tab);
void			basic_error_message(char *err, void *free_this, int fd);
void			error_exit(t_data *d, char *err, void *free_this);
void			free_n_exit_safe(t_data *d);

/*------------------------------ END UTILS -----------------------------------*/

#endif
