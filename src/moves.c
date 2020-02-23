#include "filler.h"

void	process_map(t_map *map, t_piece *p)
{
	int		i;
	int		j;
	int		bias;

	j = -1;
	bias = 0;
	while (++j < map->height)
	{
		if (ft_strchrn(map->map[j], map->c) == -1)
			continue;
		while ((i = ft_strchrn(map->map[j] + bias, map->c)) != -1)
		{
			get_free_space(map, i + bias, j, p);
			bias = bias + i + 1;
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
	int d[2];

	d[0] = ft_sqrt(ft_pow((map.width - dot.i), 2) +
			ft_pow((map.height - dot.j), 2));
	d[1] = ft_sqrt(ft_pow((map.width - best.i), 2) +
			ft_pow((map.height - best.j), 2));
	return d[0] < d[1] ? 1 : 0;
}

t_dot	*choose_candidate(t_map *map)
{
	t_dot	*dot;
	t_dot	*best;

	dot = map->dots;
	best = dot;
	while (dot)
	{
		if (is_closer_to_ceneter(*dot, *best, *map))
		{
			best = dot;
			ft_printf("found better dot: (%d %d)\n", best->i, best->j);
		}
		dot = dot->next;
	}
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

/*
**	return position to place the piece
*/

t_dot	*find_position(t_map *map, t_piece *p)
{
	t_dot	*best;
	t_dot	*coord;

	best = choose_candidate(map);
	coord = init_dot(best->i - p->width + 1, best->j - p->height + 1);
	while (coord->j <= best->j)				//is able to move down
	{
		while (coord->i <= best->i)			//is able to move right
		{
			if (is_placeable(coord, map, p))
				return (coord);
			coord->i += 1;						//try to move right
		}
		coord->j += 1;							//try to move down
	}
	//try to find another dot (or not?)
	return (NULL);
}

void	next_move(t_map *map)
{
	t_piece	*p;
	t_dot	*coord;

	p = init_piece();
	process_map(map, p);
	coord = find_position(map, p);
	ft_printf("%d %d\n", coord->j, coord->i);
	delete_piece(p);
	delete_dot(coord);
}