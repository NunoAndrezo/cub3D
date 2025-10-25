/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:29:27 by hladeiro          #+#    #+#             */
/*   Updated: 2025/01/05 21:16:37 by nneves-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE + 1];
	t_data		data;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	data.n = 0;
	data.i = 1;
	data.line = NULL;
	while (!data.n)
	{
		if (!*str)
		{
			data.i = read(fd, str, BUFFER_SIZE);
			if (data.i > BUFFER_SIZE)
			{
				ft_error_handler(str, &data);
				return (data.line);
			}
			if (data.i == 0)
				return (data.line);
			str[data.i] = 0;
		}
		ft_get_line(str, &data);
	}
	return (data.line);
}
