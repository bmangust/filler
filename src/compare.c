/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/18 16:02:00 by akraig            #+#    #+#             */
/*   Updated: 2020/04/18 16:23:08 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	filter to select place based on distance to center 
*/

int		is_closer_to_ceneter(t_dot dot, t_dot best, t_map map)
{
	int64_t d[2];
	d[0] = ft_absint(map.width / 2 - dot.i) +
			ft_absint(map.height / 2 - dot.j);
	d[1] = ft_absint(map.width / 2 - best.i) +
			ft_absint(map.height / 2 - best.j);
	return d[0] < d[1] ? 1 : 0;
}

/*
**	filter to select place with lowest heat for current piece
*/

int		is_lower_heat(t_dot dot, t_dot best, t_map map)
{
	(void) map;
	if (dot.heat < best.heat)
		return (FIRST_IS_BETTER);
	else if (dot.heat == best.heat)
		return (SIMILAR_DOTS);
	return (SECOND_IS_BETTER);
}

/*
**	chooses best candidate based on comparator function
**	if compatarator shows qeual result - choose closest to edge
*/

t_dot	*choose_candidate(t_dot *dots, t_map *map, int comp(t_dot, t_dot, t_map))
{
	t_dot	*dot;
	t_dot	*best;
	int 	res[2];

	dot = dots;
	best = dot;
	if (!dot)
		return (NULL);
	while ((dot = dot->next) != NULL)
		if ((res[0] = comp(*dot, *best, *map)) == FIRST_IS_BETTER)
			best = dot;
		else if (res[0] == SIMILAR_DOTS &&
		(res[1] = is_closer_to_ceneter(*dot, *best, *map)) == SECOND_IS_BETTER)
			best = dot;
	return (best);
}

/*
**	finds out if it is possible to place current piece <p> in position <coord>
*/

int		is_placeable(t_dot *coord, t_map *map, t_piece *p)
{
	int tmp[2];
	int was_intersection;

	if (coord->i < 0 || coord->j < 0)
		return (0);
	tmp[1] = 0;
	was_intersection = 0;
	while (tmp[1] < p->height && coord->j + p->height - 1 < map->height)
	{
		tmp[0] = 0;
		while (tmp[0] < p->width && coord->i + p->width - 1 < map->width)
			if (p->map[tmp[1]][tmp[0]] == '.' || (p->map[tmp[1]][tmp[0]] == '*'
				&& map->map[coord->j + tmp[1]][coord->i + tmp[0]] == '.'))
				tmp[0] += 1;
			else if (!was_intersection && p->map[tmp[1]][tmp[0]] == '*' &&
					map->map[coord->j + tmp[1]][coord->i + tmp[0]] == map->c)
			{
				was_intersection = 1;
				tmp[0] += 1;
			}
			else
				return (0);
		tmp[1] += 1;
	}
	return (was_intersection);
}
