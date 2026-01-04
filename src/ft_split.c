/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:04:36 by nuno              #+#    #+#             */
/*   Updated: 2026/01/04 13:04:37 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static size_t	ft_count_words(char const *s, char c);
static int		ft_fill(char **argv, char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**word_argv;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	word_argv = (char **)malloc(sizeof(char *) * (words + 1));
	if (word_argv == NULL)
		return (NULL);
	word_argv[words] = NULL;
	if (ft_fill(word_argv, s, c))
		return (NULL);
	return (word_argv);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	words;
	bool	in_word;

	words = 0;
	while (*s != '\0')
	{
		in_word = false;
		while (*s != '\0' && *s == c)
			s++;
		while (*s != '\0' && *s != c)
		{
			if (in_word == false)
			{
				words++;
				in_word = true;
			}
			s++;
		}
	}
	return (words);
}

static int	ft_free(char **word_argv)
{
	int	i;

	i = 0;
	while (word_argv[i])
	{
		free(word_argv[i]);
		i++;
	}
	free(word_argv);
	return (1);
}

static int	ft_fill(char **word_argv, char const *s, char c)
{
	size_t	len;
	int		a;

	a = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			word_argv[a] = malloc(len + 1);
			if (word_argv[a] == NULL)
				return (ft_free(word_argv));
			ft_memcpy_normal(word_argv[a], s - len, len);
			word_argv[a++][len] = '\0';
		}
	}
	word_argv[a] = NULL;
	return (0);
}
