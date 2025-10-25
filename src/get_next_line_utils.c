/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:29:32 by hladeiro          #+#    #+#             */
/*   Updated: 2024/05/13 21:14:33 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_copy_str(char buf[BUFFER_SIZE], char *str, t_data *data)
{
	while (data->line && data->line[data->j])
		str[data->i++] = data->line[data->j++];
	data->j = 0;
	while (buf[data->j])
	{
		str[data->i] = buf[data->j++];
		if (str[data->i] == '\n')
		{
			str[data->i + 1] = 0;
			free(data->line);
			data->line = str;
			ft_clean_str(buf, data);
			return ;
		}
		data->i++;
	}
	str[data->i] = 0;
	if (data->line)
		free(data->line);
	data->line = str;
	*buf = 0;
}

static void	ft_get_len(char s[BUFFER_SIZE], t_data *data)
{
	data->i = 0;
	data->len = 0;
	while (s[data->len] && s[data->len] != '\n')
		data->len++;
	if (s[data->len] == '\n')
	{
		data->len++;
		data->n = 1;
	}
	while (data->line && data->line[data->i])
		data->i++;
	data->len += data->i;
}

void	ft_clean_str(char s[BUFFER_SIZE], t_data *data)
{
	data->len = 0;
	data->i = 0;
	data->full_len = 0;
	while (s[data->full_len])
		data->full_len++;
	while (s[data->len] && s[data->len] != '\n')
		data->len++;
	if (s[data->len] == '\n')
	{
		if (s[data->len] == '\n')
			s[data->len++] = 0;
		while (s[data->i] || data->len < data->full_len)
		{
			if (!s[data->len])
			{
				while (data->i < data->len)
					s[data->i++] = 0;
				return ;
			}
			else
				s[data->i++] = s[data->len++];
		}
	}
	else
		*s = 0;
}

void	ft_get_line(char s[BUFFER_SIZE], t_data *data)
{
	char	*str;

	if (!s)
		return ;
	ft_get_len(s, data);
	str = malloc((data->len) + 1);
	if (!str)
		return ;
	data->j = 0;
	data->i = 0;
	ft_copy_str(s, str, data);
}

void	ft_error_handler(char s[BUFFER_SIZE], t_data *data)
{
	if (data->line)
		free(data->line);
	data->line = NULL;
	ft_clean_str(s, data);
}
