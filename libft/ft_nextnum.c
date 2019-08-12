/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nextnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoukhli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:58:26 by ymoukhli          #+#    #+#             */
/*   Updated: 2019/08/10 20:06:24 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nextnum(char *str, int i)
{
	while (ft_iswhit(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '\n' || str[i] == ',')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}
