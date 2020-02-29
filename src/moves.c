#include "filler.h"

int		get_heat(t_map *map, t_piece *p, t_dot dot)
{
	t_dot	*pcur;

	pcur = init_dot(-1, -1);
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

	index[1] = best->j - p->height + 1;			//p->height + 1;
	while (index[1] <= best->j)					//is able to move down
	{
		index[0] = best->i - p->width + 1;		//p->width + 1;
		while (index[0] <= best->i)				//is able to move right
		{
			coord = init_dot(index[0], index[1]);
			if (is_placeable(coord, map, p) &&
				!find_dot(map->placeable, coord))
//				map->candidates[index[1]][index[0]]->is_placeable = 1;
			{
				coord->heat = get_heat(map, p, *coord);
				add_last_dot(&map->placeable, coord);
			}
			else
				delete_dot(coord);
			index[0]++;							//try to move right
		}
		index[1]++;								//try to move down
	}
}

/*
**	searches map for player symbol (O or X)
**	and askes for all points, where we can add figure
*/

void	process_map(t_map *map, t_piece *p)
{
	int		index[2];
	int		bias;
	t_dot	*dot;

	index[1] = -1;
	while (++index[1] < map->height)
	{
		bias = 0;
		if (ft_strchrn(map->map[index[1]], map->c) == -1)
			continue;
		while ((index[0] = ft_strchrn(map->map[index[1]] + bias, map->c)) != -1)
		{
			dot = init_dot(index[0] + bias, index[1]);
			get_candidates(map, p, dot);
			free(dot);
			bias = bias + index[0] + 1;
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
		return (1);
	return (0);
}

//t_dot	*choose_min_sum_candidate(t_dot *dots, t_map *map, t_piece *p)
//{
//	t_dot	*dot;
//	t_dot	*best;
//
//	dot = dots;
//	best = dot;
//	while ((dot = dot->next) != NULL)
//		if (dot->heat > best->heat)
//			best = dot;
//	return (best);
//}

/*
**	chooses best candidate based of compare function f
*/

t_dot	*choose_candidate(t_dot *dots, t_map *map, int comp(t_dot, t_dot, t_map))
{
	t_dot	*dot;
	t_dot	*best;

	dot = dots;
	best = dot;
	if (!dot)
		return (NULL);
	while ((dot = dot->next) != NULL)
		if (comp(*dot, *best, *map))
			best = dot;

	return (best);
}

int		is_placeable(t_dot *coord, t_map *map, t_piece *p)
{
	int tmp[2];
	int was_intersection;

	tmp[1] = 0;
	was_intersection = 0;
	while (tmp[1] < p->height)
	{
		tmp[0] = 0;
		while (tmp[0] < p->width)
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


void	next_move(t_map *map)
{
	t_piece	*p;
	t_dot	*dot;

	p = init_piece();
	calculate_heatmap(map);
	process_map(map, p);
//	map_dots(map->placeable, &print_dot_heat);
	dot = choose_candidate(map->placeable, map, &is_lower_heat);
//	dot = choose_min_sum_candidate(map->placeable, map, p);
	printf("%d %d\n", dot->j, dot->i);
	map_a_map(map, &reset_heatmap);
	clear_dots(&(map->placeable));
	delete_piece(&p);
}