/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoukhli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:00:24 by ymoukhli          #+#    #+#             */
/*   Updated: 2019/08/10 15:01:08 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * ~~addon~~
 */
char	*ft_file(char *file)
{
	int		fd;
	int		rd;
	char	buf[BUF_SIZE + 1];
	char	*str_file;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd < 0 || read(fd, buf, 0) < 0)
		return (NULL);
	str_file = ft_strnew(0);
	while ((rd = read(fd, buf, BUF_SIZE)))
	{
		tmp = str_file;
		buf[rd] = '\0';
		if (!(str_file = ft_strjoin(str_file, buf)))
		{
			free(tmp);
			close(fd);
			return (NULL);
		}
		free(tmp);
	}
	close(fd);
	return (str_file);
}
