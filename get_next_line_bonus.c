/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas <khatlas@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:13:07 by khatlas           #+#    #+#             */
/*   Updated: 2022/05/07 21:47:27 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*free_all(char *hold)
{
	if (hold)
		free (hold);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_static	ctnr[1024];
	char			*hold;
	char			*out;
	int				len;

	hold = NULL;
	out = NULL;
	len = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	while (len > 0 && !(ft_strchr(ctnr[fd].store, '\n')))
	{
		len = read (fd, ctnr[fd].buff, BUFFER_SIZE);
		if (*(ctnr[fd].buff) == '\0' || len == -1)
			return (free_all(hold));
		(ctnr[fd].buff)[len] = '\0';
		ctnr[fd].store = store_append(ctnr[fd].store, ctnr[fd].buff, &hold);
	}
	len = 0;
	while ((ctnr[fd].store)[len] != '\n' && (ctnr[fd].store)[len] != '\0')
		len++;
	ctnr[fd].store = generate_string(ctnr[fd].store, &out, &hold, len);
	return (out);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*ln;
// 	int		i;
// 	FILE	*read_txt;
// 	FILE	*read2_txt;

// 	read_txt = fopen("read.txt", "w+");
// 	fprintf(read_txt, "asdf\nqwer\nzxcv\npokemon\nubuntu\npalm");
// 	fclose(read_txt);
// 	read2_txt = fopen("read2.txt", "w+");
// 	fprintf(read2_txt, "the\nquick\nbrown\nfox\njumped\nover");
// 	fclose(read2_txt);
// 	//1
// 	printf("document 1:\n");
// 	fd = open("read.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		ln = get_next_line(fd);
// 		printf("%s\n", ln);
// 		free (ln);
// 		i++;
// 	}
// 	//2
// 	printf("document 2:\n");
// 	fd2 = open("read2.txt", O_RDONLY);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		ln = get_next_line(fd2);
// 		printf("%s\n", ln);
// 		free (ln);
// 		i++;
// 	}
// 	//1
// 	printf("document 1:\n");
// 	i = 0;
// 	while (i < 3)
// 	{
// 		ln = get_next_line(fd);
// 		printf("%s\n", ln);
// 		free (ln);
// 		i++;
// 	}
// 	//2
// 	printf("document 2:\n");
// 	i = 0;
// 	while (i < 3)
// 	{
// 		ln = get_next_line(fd2);
// 		printf("%s\n", ln);
// 		free (ln);
// 		i++;
// 	}
// 	close (fd);
// 	close (fd2);
// 	system("leaks a.out");
// 	return (0);
// }
