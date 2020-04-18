/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:02:00 by akraig            #+#    #+#             */
/*   Updated: 2020/04/18 16:23:03 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	heatmap algo:
**	1. calculate heatmap
**	each point get score depends on distance from enemy
**	2. among all possible positions (calculated in moves.c)
**	select one with lowest score
**	3. TODO: analyze enemy direction and try to counter his way
**	this can be done by searching lowercase letters and
**	select pieces closer to them
**	4. TODO: safe play - touch edge and cut as big part as possible
**	this should be done only if there's no threat of being trapped!
**	if we are close to edge and can touch it this move - place a piece
**	5. TODO: FIX FREEING NOT ALLOCATED POINTER WHEN ENEMY IS LOCKED
**	5. TODO: filling the board when the enemy is dead
*/

void	get_heatmap(t_map *map)
{
	int		i[2];

	if (!map->heatmap)
		map->heatmap = (int**)malloc(sizeof(int*) * map->height);
	i[1] = -1;
	while (++i[1] < map->height)
	{
		map->heatmap[i[1]] = (int*)malloc(sizeof(int) * map->width);
		i[0] = -1;
		while (++i[0] < map->width)
		{
			if (map->map[i[1]][i[0]] == '.')
				map->heatmap[i[1]][i[0]] = INT16_MAX;
		}
	}
}

void	calculate_heat(t_map *map, t_dot *cur)
{
	t_dot	*enemy;

	if (map->map[cur->j][cur->i] == map->c)
	{
		map->heatmap[cur->j][cur->i] = 0;
		return ;
	}
	else if (is_enemy(map, cur))
	{
		map->heatmap[cur->j][cur->i] = 999;
		return ;
	}
	enemy = NULL;
	cur->heat_max = 999;
	while ((enemy = get_next_enemy(map, enemy, 0)))
	{
		cur->heat = get_distance(*enemy, *cur);
		cur->heat_max = cur->heat < cur->heat_max ?
						cur->heat : cur->heat_max;
	}
	map->heatmap[cur->j][cur->i] = cur->heat_max;
}

/*
**	calculates heat based only on new enemies
**	-------------not used now----------------
*/

void	calculate_heat_new(t_map *map, t_dot *cur)
{
	t_dot	*enemy;

	if (map->map[cur->j][cur->i] == map->c)
	{
		map->heatmap[cur->j][cur->i] = 0;
		return ;
	}
	else if (is_enemy(map, cur))
	{
		map->heatmap[cur->j][cur->i] = 999;
		return ;
	}
	enemy = NULL;
	cur->heat_max = 999;
	while ((enemy = get_next_enemy(map, enemy, 1)))
	{
		cur->heat = get_distance(*enemy, *cur);
		cur->heat_max = cur->heat < cur->heat_max ?
						cur->heat : cur->heat_max;
	}
	map->heatmap[cur->j][cur->i] = cur->heat_max;
}

/*
**	calculates distance from enemy for every point on a map
*/

void	calculate_heatmap(t_map *map)
{
	if (!map->heatmap)
		get_heatmap(map);
	map_a_map(map, &update_enemies);
	map_a_map(map, &calculate_heat);
	// map_a_map(map, &print_array);
}
/*
**	caclulate summary heat for selected position,
**	heap is stored in selected position
*/

int		get_heat(t_map *map, t_piece *p, t_dot dot)
{
	t_dot	*pcur;

	if (!map->heatmap)
		return (0);
	pcur = init_dot(-1, -1, 0);
	dot.heat = 0;
	while (++pcur->j < p->height)
	{
		pcur->i = -1;
		while (++pcur->i < p->width)
			if (p->map[pcur->j][pcur->i] == '*')
				dot.heat += map->heatmap[dot.j + pcur->j][dot.i + pcur->i];
	}
	return (dot.heat);
}
