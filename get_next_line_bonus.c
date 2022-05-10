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

static char	*store_append(char *store, char *buff)
{
	char	*temp;

	if (store == NULL)
		return (ft_strdup(buff));
	else
	{
		temp = store;
		store = ft_strjoin(store, buff);
		free (temp);
		return (store);
	}
}

static char	*generate_strings(char *store, int len, char **out)
{
	char	*temp;

	if (store[len] == '\n')
	{
		temp = store;
		*out = ft_substr(store, 0, len + 1);
		store = ft_strdup(store + len + 1);
		free (temp);
		return (store);
	}
	else
	{
		*out = ft_strdup(store);
		free(store);
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

static int	check_null(char *buffer, int len, char **store)
{
	if (*buffer == '\0')
		return (1);
	if (*store)
	{
		if (**store == '\0' && len == 0)
		{
			free (*store);
			*store = NULL;
			return (1);
		}
	}
	else if (len == 0)
	{
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_static	ctnr[OPEN_MAX];
	char			*out;
	int				len;

	out = NULL;
	len = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > OPEN_MAX)
		return (NULL);
	while (len > 0 && !(ft_strchr(ctnr[fd].store, '\n')))
	{
		len = read (fd, ctnr[fd].buff, BUFFER_SIZE);
		if (len == -1 || check_null(ctnr[fd].buff, len, &(ctnr[fd].store)))
			return (NULL);
		(ctnr[fd].buff)[len] = '\0';
		ctnr[fd].store = store_append(ctnr[fd].store, ctnr[fd].buff);
	}
	len = 0;
	while ((ctnr[fd].store)[len] != '\n' && (ctnr[fd].store)[len] != '\0')
		len++;
	ctnr[fd].store = generate_strings(ctnr[fd].store, len, &out);
	return (out);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*ln;
// 	char	*ln2;
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
// 		ln2 = get_next_line(fd2);
// 		printf("%s\n", ln2);
// 		free (ln2);
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
// 		ln2 = get_next_line(fd2);
// 		printf("%s\n", ln2);
// 		free (ln2);
// 		i++;
// 	}
// 	close (fd);
// 	close (fd2);
// 	system("leaks a.out");
// 	return (0);
// }
