#include "filler.h"

int		get_heat(t_map *map, t_piece *p, t_dot dot)
{
	t_dot	*pcur;

	pcur = init_dot(-1, -1, 0);
	while (++pcur->j < p->height)
	{
		pcur->i = -1;
		while (++pcur->i < p->width)
			if (p->map[pcur->j][pcur->i] == '*')
				dot.heat += map->heatmap[dot.j + pcur->j][dot.i + pcur->i];
	}
	return (dot.heat);
}

/*
**	get all possible positions to place a piece near selected dot
*/

void	get_candidates(t_map *map, t_piece *p, t_dot *best)
{
	t_dot	*coord;
	int		index[2];

	index[1] = best->j - p->height;			//p->height + 1;
	while (++index[1] <= best->j && index[1] >= 0)					//is able to move down
	{
		index[0] = best->i - p->width;		//p->width + 1;
		while (++index[0] <= best->i && index[0] >= 0)				//is able to move right
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

int		is_closer_to_ceneter(t_dot dot, t_dot best, t_map map)
{
	int64_t d[2];
	d[0] = ft_absint(map.width / 2 - dot.i) +
			ft_absint(map.height / 2 - dot.j);
	d[1] = ft_absint(map.width / 2 - best.i) +
		   ft_absint(map.height / 2 - best.j);
	return d[0] < d[1] ? 1 : 0;
}

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
**	chooses best candidate based of compare function f
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

int		is_placeable(t_dot *coord, t_map *map, t_piece *p)
{
	int tmp[2];
	int was_intersection;

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
	return (was_intersection ? 1 : 0);
}


int		next_move(t_map *map)
{
	t_piece	*p;
	t_dot	*dot;

	p = init_piece();
	calculate_heatmap(map);
	process_map(map, p);
//	map_dots(map->placeable, &print_dot_heat);					//show heats for selected dots
	dot = choose_candidate(map->placeable, map, &is_lower_heat);
	if (dot)
		ft_printf("%d %d\n", dot->j, dot->i);
	else
	{
		ft_fprintf(2, "no candidates\n");
		ft_printf("%d %d\n", 0, 0);
		delete_piece(&p);
		return (NO_CANDIDATES);
	}
	map_a_map(map, &reset_heatmap);
	clear_dots(&(map->placeable));
	delete_piece(&p);
	clear_map(map);
	return (OK);
}

void	safe_play(t_map *map)
{
	t_piece	*p;
	t_dot	*dot;

	ft_fprintf(2, "=============safe play=============\n");
	p = init_piece();
	process_map(map, p);
	dot = choose_candidate(map->placeable, map, &is_closer_to_ceneter);
	if (dot)
		ft_printf("%d %d\n", dot->j, dot->i);
	else
	{
		ft_fprintf(2, "no candidates\n");
		ft_printf("%d %d\n", 0, 0);
		delete_piece(&p);
	}
	clear_dots(&(map->placeable));
	delete_piece(&p);
	clear_map(map);
}
