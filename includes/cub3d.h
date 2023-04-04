/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:41:46 by mflores-          #+#    #+#             */
/*   Updated: 2023/04/03 12:19:55 by mflores-         ###   ########.fr       */
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

/******************************************************************************/
/*                                                                            */
/*                                MACROS                                      */
/*                                                                            */
/******************************************************************************/

/* OTHER MACROS */
#define	WIN1_SX		242
#define	WIN1_SY		242
# define FILE_TYPE ".cub"
# define TITLE "Cub3D"

/* ERROR MESSAGES */
# define ERR_USAGE "\tusage: ./cub3d map.cub"
# define ERR_MSG "Error:"
# define ERR_MALLOC "\tmalloc: Could not allocate memory.\n"
# define ERR_FILE "\tfile: invalid file type, [.cub] needed"

/* Colors */
# define DEFAULT "\001\e[00;39m\002"
# define GREY "\001\e[1;90m\002"
# define RED "\001\e[1;91m\002"
# define GREEN "\001\e[0;92m\002"
# define YELLOW "\001\e[1;93m\002"
# define BLUE "\001\e[1;94m\002"
# define MAGENTA "\001\e[1;95m\002"
# define PINK "\001\e[0;35m\002"
# define PURPLE "\001\e[0;34m\002"
# define CYAN "\001\e[1;96m\002"
# define WHITE "\001\e[0;97m\002"

/******************************************************************************/
/*                                                                            */
/*                              STRUCTURES                                    */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*                               PROTOTYPES                                   */
/*                                                                            */
/******************************************************************************/

/*------------------------------ MAIN -------------------------------------*/
void	coucou(void);
/*----------------------------- END MAIN ----------------------------------*/

/*------------------------------ UTILS -------------------------------------*/

/* exit_utils.c */
void	basic_error_message(char *err, void *free_this);

/*----------------------------- END UTILS ----------------------------------*/

#endif
