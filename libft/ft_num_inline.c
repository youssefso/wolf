/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_inline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoukhli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:02:06 by ymoukhli          #+#    #+#             */
/*   Updated: 2019/08/10 16:15:48 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_num_inline(char	*str, int *i)
{
	int u;
	int lvl;
	int num;

	u = *i;
	lvl = 0;
	num = 0;
	while (str[u] != '\0' || str[u] != '\n')
	{
		if (lvl == 0 && ft_isdigit(str[u]))
			lvl = 1;
		else if (lvl == 1 && ft_isdigit(str[u]) == 0)
		{
			lvl = 0;
			num++;
		}
		u++;
	}
	if (str[u] == '\n')
		u++;
	*i = u;
	return (num);
}
