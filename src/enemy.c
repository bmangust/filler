/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:44:42 by akraig            #+#    #+#             */
/*   Updated: 2020/03/12 19:44:43 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	i[0] - y coord
**	i[1] - x coord
**	i[2] - cnt enemies
**	finds out if enemy is alive and counts enemy dots
**	if enemy is already dead - just return 0 (not alive)
*/

int		count_enemies(t_map *map)
{
	int i[3];

	i[0] = -1;
	i[2] = 0;
	if (!map->is_alive)
		return (0);
	while (++i[0] < map->height)
	{
		i[1] = -1;
		while (++i[1] < map->width)
			if (ft_toupper(map->map[i[0]][i[1]]) == map->enemy)
				i[2]++;
	}
	if (i[2] == map->cnt_enemies)
		map->is_alive = 0;
	else
		map->cnt_enemies = i[2];
	return (map->is_alive);
}
