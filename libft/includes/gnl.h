/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 22:48:17 by mflores-          #+#    #+#             */
/*   Updated: 2023/03/31 10:19:06 by mflores-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

/******************************************************************************/
/*                                                                            */
/*                                LIBS                                        */
/*                                                                            */
/******************************************************************************/

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

/******************************************************************************/
/*                                                                            */
/*                                MACROS                                      */
/*                                                                            */
/******************************************************************************/

// Redefine buffer_size if needed with flag -D BUFFER_SIZE=nbr_you_want
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE BUFSIZ
# endif

/******************************************************************************/
/*                                                                            */
/*                               PROTOTYPES                                   */
/*                                                                            */
/******************************************************************************/

/*
    Returns a line read from a file descriptor
    
    Compilation:
		cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 file.c
        
    1024 is the number of file descriptors a process can open on an 
	UNIX based operating system 
	Command : ulimit -n 
*/
char	*get_next_line(int fd);

/*---------------------------- GNL_UTILS -------------------------------------*/

size_t	gnl_strlen(const char *s);
char	*gnl_strchr(const char *s, int c);
char	*gnl_free(char *stash, char *buff);
char	*gnl_strjoin(char *stash, char *buffer);

/*-------------------------- END GNL_UTILS -----------------------------------*/

#endif