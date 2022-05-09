/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:13:07 by khatlas           #+#    #+#             */
/*   Updated: 2022/05/08 15:32:44 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*store_append(char *store, char *buff, char **hold)
{
	if (store == NULL)
		store = ft_strdup (buff);
	else
	{
		*hold = ft_strjoin(store, buff);
		free (store);
		return (*hold);
	}
	return (store);
}

static char	*free_all(char *hold)
{
	if (hold)
		free (hold);
	return (NULL);
}

static char	*generate_string(char *store, char **out, char **hold, int len)
{
	if (store[len] == '\n')
	{
		*out = ft_substr(store, 0, len + 1);
		*hold = ft_strdup(&(store[len + 1]));
		free (store);
		return (*hold);
	}
	else
	{
		if (store[0] == '\0')
			store = NULL;
		free (*hold);
		*out = ft_strdup(store);
		return (NULL);
	}
}

static char	*ft_strchr(const char *str, int c)
{
	c = c % 128;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *) str);
		str++;
	}
	if (c == 0)
		return ((char *) str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_static	ctnr;
	char			*hold;
	char			*out;
	int				len;

	hold = NULL;
	out = NULL;
	len = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	while (len > 0 && !(ft_strchr(ctnr.store, '\n')))
	{
		len = read (fd, ctnr.buff, BUFFER_SIZE);
		if (*(ctnr.buff) == '\0' || len == -1)
			return (free_all(hold));
		(ctnr.buff)[len] = '\0';
		ctnr.store = store_append(ctnr.store, ctnr.buff, &hold);
	}
	len = 0;
	while ((ctnr.store)[len] != '\n' && (ctnr.store)[len] != '\0')
		len++;
	ctnr.store = generate_string(ctnr.store, &out, &hold, len);
	return (out);
}

// #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*ln;
// 	int		i;
// 	FILE	*read_txt;

// 	read_txt = fopen("read.txt", "w+");
// 	fprintf(read_txt, "asdf\nqwer\nzxcv\npokemon\nubuntu\npalm");
// 	fclose(read_txt);
// 	fd = open("read.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 7)
// 	{
// 		ln = get_next_line(fd);
// 		printf("%s\n", ln);
// 		free (ln);
// 		i++;
// 	}
// 	close (fd);
// 	system("leaks a.out");
// 	return (0);
// }
