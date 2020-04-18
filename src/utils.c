/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:02:00 by akraig            #+#    #+#             */
/*   Updated: 2020/04/18 16:23:01 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		get_distance(t_dot enemy, t_dot cur)
{
	int64_t diff[3];

	diff[0] = ft_absint(enemy.i - cur.i);
	diff[1] = ft_absint(enemy.j - cur.j);
	diff[2] = diff[0] + diff[1];
	return (diff[2]);
}

void 	replace_lowercase_c(t_map *map, t_dot *cur)
{
	if (map->map[cur->j][cur->i] == ft_tolower(map->c))
		map->map[cur->j][cur->i] = map->c;
}

void	reset_heatmap(t_map *map, t_dot *cur)
{
	map->heatmap[cur->j][cur->i] = INT16_MAX;
}

void	map_a_map(t_map *map, void f(t_map*, t_dot*))
{
	t_dot	*cur;

	cur = init_dot(-1, -1, 0);
	if (!map || !map->map)
		return ;
	while (++cur->j < map->height)
	{
		cur->i = -1;
		while (++cur->i < map->width)
			f(map, cur);
	}
	free(cur);
}

/*
**	optional functions
*/

void	set_dot(t_dot *target, t_dot source)
{
	target->i = source.i;
	target->j = source.j;
}

void	print_array(t_map *map, t_dot *cur)
{
	int **arr;

	arr = map->heatmap;
	ft_fprintf(2, "%- 5d", arr[cur->j][cur->i]);
	if (cur->i == map->width - 1)
		ft_fprintf(2, "\n");
}