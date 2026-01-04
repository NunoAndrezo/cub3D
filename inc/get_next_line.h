/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:09:13 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 13:06:50 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_data
{
	size_t	i;
	size_t	len;
	char	*line;
	int		j;
	int		n;
	size_t	full_len;
}			t_data;

char	*get_next_line(int fd);
void	ft_get_line(char s[BUFFER_SIZE], t_data *data);
void	ft_clean_str(char s[BUFFER_SIZE], t_data *data);
void	ft_error_handler(char s[BUFFER_SIZE], t_data *data);

#endif
