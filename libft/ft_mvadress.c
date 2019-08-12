/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mvadress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoukhli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 12:17:34 by ymoukhli          #+#    #+#             */
/*   Updated: 2019/04/19 12:59:38 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_mvadress(char **sr, int j)
{
	char *s;

	s = ft_stmdup(sr[0], j);
	free(sr[0]);
	sr[0] = s;
}