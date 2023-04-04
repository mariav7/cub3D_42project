/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:41:46 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/04 17:40:59 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# include <limits.h>
# include <math.h>

/******************************************************************************/
/*                                                                            */
/*                                MACROS                                      */
/*                                                                            */
/******************************************************************************/

/* OTHER MACROS */
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
// # define UP 65362
// # define DOWN 65364

/* ERROR MESSAGES */
# define ERR_USAGE "\tusage: ./cub3d map.cub"
# define ERR_MSG "Error:"
# define ERR_CALLOC "\tcalloc: structures"
# define ERR_MALLOC "\tmalloc: could not allocate memory\n"
# define ERR_FILE "\tfile: invalid file type, [.cub] needed"
# define ERR_MLX "Minilibx: initialization failed"
# define ERR_MLX_WIN "Minilibx: new window failed"

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

typedef struct s_map t_map;
typedef struct s_data t_data;

struct s_map
{
	int		height;
	int		width;
};

struct s_data
{
	void	*mlx_ptr;
	void	*window;
	t_map	*map;
};

/******************************************************************************/
/*                                                                            */
/*                               PROTOTYPES                                   */
/*                                                                            */
/******************************************************************************/

/*------------------------------ PARSING -------------------------------------*/

void	check_file(char *file);
void	init_structs(t_data **d, t_map **m);
void	init_game(t_data *d);

/*------------------------------ END PARSING ---------------------------------*/

/*------------------------------ UTILS ---------------------------------------*/

/* exit_utils.c */
void	basic_error_message(char *err, void *free_this);
void	error_exit(t_data *d, char *err, void *free_this);
void	free_n_exit_safe(t_data *d);

/*------------------------------ END UTILS -----------------------------------*/

#endif
