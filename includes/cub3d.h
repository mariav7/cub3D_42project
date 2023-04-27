/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:41:46 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/27 19:05:19 by mflores-         ###   ########.fr       */
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
# define WIN1_SX 1280
# define WIN1_SY 720
# define FILE_TYPE ".cub"
# define TEX_TYPE ".xpm"
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
# define ERR_FILE_ISDIR "File: is a directory"
# define ERR_FILE_NOTFOUND "File"
# define ERR_FILE_EMPTY "File: is empty"
# define ERR_FILE_INVALID "File: element(s) missing"
# define ERR_ID_INVALID "File: invalid identifier(s)"
# define ERR_ID_DOUBLES "File: double identifier(s)"
# define ERR_MLX "Minilibx: initialization failed"
# define ERR_MLX_WIN "Minilibx: new window failed"
# define ERR_TEX "Texture: invalid texture file type, [.xpm] needed"
# define ERR_TEX_INVALID "File: invalid texture(s)"
# define ERR_TEX_ISDIR "Texture: is a directory"
# define ERR_TEX_NOTFOUND "Texture"
# define ERR_COLOR_INVALID "File: invalid floor/ceiling RGB color(s)"
# define ERR_TEXCO_FORMAT "File: invalid format in textures/colors/map"
# define ERR_MAP_ISFIRST "File: invalid format, map always has to be last"
# define ERR_MAP_INVALID "File: invalid map"
# define ERR_MAP_NOTCLOSED "Map: invalid, needs to be surrounded by walls"
# define ERR_MAP_CHARS "Map: invalid map characters"
# define ERR_MAP_SPACES "Map: spaces inside map"
# define ERR_NB_PLAYER "Map: needs 1 player position [N,S,W,E]"

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

typedef struct s_map	t_map;
typedef struct s_tex	t_tex;
typedef struct s_data	t_data;

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

struct s_data
{
	void	*mlx_ptr;
	void	*window;
	t_map	*map;
	t_tex	*tex;
};

/******************************************************************************/
/*                                                                            */
/*                               PROTOTYPES                                   */
/*                                                                            */
/******************************************************************************/

/* main.c */
int				key_event(int key_code, t_data *d);
int				close_window(t_data *d);

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
void			ignore_spaces(char *str, int *index);
long long		ft_atoll(const char *str);

/* textures.c */
int				fill_textures(t_tex *tex, char *line, int *i);
int				check_textures(t_data **d, char **err_msg);

/* colors.c */
int				fill_colors(t_tex *tex, char *line, int *i, char **err_msg);

/* map.c */
void			fill_map(int *i, int nb_line, t_data **d);
int				check_map(t_map *m, char **err_msg);

/*------------------------------ END PARSING ---------------------------------*/

/*------------------------------ UTILS ---------------------------------------*/

/* exit_utils.c */
void			free_tab(void **tab);
void			basic_error_message(char *err, void *free_this, int fd);
void			error_exit(t_data *d, char *err, void *free_this);
void			free_n_exit_safe(t_data *d);

/*------------------------------ END UTILS -----------------------------------*/

#endif
