/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 15:43:52 by max               #+#    #+#             */
/*   Updated: 2020/04/18 16:23:29 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	returns integer part of a root or -1 if argument is negative
*/

int		ft_sqrt(int a)
{
	int root;

	if (a < 0)
		return (-1);
	else if (a == 0)
		return (0);
	root = 1;
	while (root * root <= a)
		root++;
	return (root);
}
