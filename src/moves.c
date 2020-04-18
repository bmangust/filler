/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:09:17 by akraig            #+#    #+#             */
/*   Updated: 2020/04/18 17:47:06 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	get all possible positions to place a piece near selected dot
*/

void	get_candidates(t_map *map, t_piece *p, t_dot *best)
{
	t_dot	*coord;
	int		index[2];

	index[1] = best->j - p->height;
	index[1] = index[1] < 0 ? -1 : index[1];
	while (++index[1] <= best->j)			// && index[1] >= 0
	{
		index[0] = best->i - p->width;
		index[0] = index[0] < 0 ? -1 : index[0];
		while (++index[0] <= best->i)		// && index[0] >= 0
		{
			coord = init_dot(index[0], index[1], 0);
			if (is_placeable(coord, map, p) &&
				!find_dot(map->placeable, coord))
			{
				coord->heat = get_heat(map, p, *coord);
				add_last_dot(&map->placeable, coord);
				map->placeable_candidates++;
			}
			else
				delete_dot(coord);
		}
	}
}

/*
**	searches map for player symbol (O or X)
**	and askes for all points, where we can add figure
*/

void	process_map(t_map *map, t_piece *p)
{
	int		i[2];
	int		bias;
	t_dot	*dot;

	i[1] = -1;
	while (++i[1] < map->height)
	{
		bias = 0;
		if (ft_strchrn(map->map[i[1]], map->c) == -1)
			continue;
		while ((i[0] = ft_strchrn(map->map[i[1]] + bias, map->c)) != -1)
		{
			dot = init_dot(i[0] + bias, i[1], 0);
			get_candidates(map, p, dot);
			free(dot);
			bias = bias + i[0] + 1;
		}
	}
}

/*
**	calculates best position for cure 
*/

int		next_move(t_map *map)
{
	t_piece	*p;
	t_dot	*dot;

	p = init_piece();
	calculate_heatmap(map);
	process_map(map, p);
//	map_dots(map->placeable, &print_dot_heat);	//show heats for selected dots
	dot = choose_candidate(map->placeable, map, &is_lower_heat);
	if (dot)
		ft_printf("%d %d\n", dot->j, dot->i);
	else
	{
		ft_printf("%d %d\n", 0, 0);
		delete_piece(&p);
		return (NO_CANDIDATES);
	}
	map_a_map(map, &reset_heatmap);
	clear_dots(&(map->placeable));
	map->placeable_candidates = 0;
	delete_piece(&p);
	clear_map(map);
	return (OK);
}

/*
**	calculates best position, when enemy is already dead
**	possible reasons: touch all edges (choose biggest self-heat)
**	or just place piece as lower/higher as possible
*/

int		safe_play(t_map *map)
{
	t_piece	*p;
	t_dot	*dot;

	p = init_piece();
	process_map(map, p);
	dot = choose_candidate(map->placeable, map, &is_closer_to_ceneter);
	if (dot)
		ft_printf("%d %d\n", dot->j, dot->i);
	else
	{
		ft_printf("%d %d\n", 0, 0);
		delete_piece(&p);
		return (NO_CANDIDATES);
	}
	clear_dots(&(map->placeable));
	map->placeable_candidates = 0;
	delete_piece(&p);
	clear_map(map);
	return (OK);
}
