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

int		get_distance(t_dot enemy, t_dot cur)
{
	int64_t diff[3];

	diff[0] = ft_absint(enemy.i - cur.i);
	diff[1] = ft_absint(enemy.j - cur.j);
	diff[2] = diff[0] + diff[1];
	return (diff[2]);
}

//вынести поиск врагов в отдельную функцию
//(или забить, хз как скажется на производительности)

void	get_heatmap(t_map *map)
{
	int	i[2];

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

int		is_enemy(t_map *map, t_dot *dot)
{
	if (map->map[dot->j][dot->i] == map->enemy ||
		map->map[dot->j][dot->i] == map->enemynew)
		return (1);
	return (0);
}

int		is_new_enemy(t_map *map, t_dot *dot)
{
	if (map->map[dot->j][dot->i] == map->enemynew)
		return (1);
	return (0);
}

void	set_dot(t_dot *target, t_dot source)
{
	target->i = source.i;
	target->j = source.j;
}

t_dot	*get_next_enemy(t_map *map, t_dot *enemy, int only_new)
{
	t_dot	*tmp;
//	(void)	only_new;

	if (!map || !map->enemies)
		return (NULL);
	tmp = enemy ? enemy->next : map->enemies;
	if (only_new)
		while (tmp && tmp->c != map->enemynew)
			tmp = tmp->next;
	return (tmp);
}

/*
**	checks if enemies list already has current dot
*/

int 	check_enemies(t_map *map, t_dot *cur)
{
	t_dot *tmp;

	if (!map || !map->enemies)
		return (1);
	tmp = map->enemies;
	while (tmp)
	{
		if (tmp->i == cur->i && tmp->j == cur->j)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}


void	reset_heatmap(t_map *map, t_dot *cur)
{
	map->heatmap[cur->j][cur->i] = INT16_MAX;
}

/*
**	updates enemies list, adds all enemy dots to a list
*/

void	update_enemies(t_map *map, t_dot *cur)
{
	int		c;
	t_dot	*dot;

	dot = NULL;
	c = map->map[cur->j][cur->i];
	if (is_enemy(map, cur) && !(dot = find_dot(map->enemies, cur)))
		add_last_dot(&(map->enemies), init_dot(cur->i, cur->j, c));
	else if (dot)
		dot->c = c;
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

void	calculate_heat_new(t_map *map, t_dot *cur)
{
	t_dot	*enemy;

	if (map->map[cur->j][cur->i] == map->c)
	{
		map->heatmap[cur->j][cur->i] = 0;
		return ;
	}
	else if (is_new_enemy(map, cur))
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

void 	replace_lowercase_c(t_map *map, t_dot *cur)
{
	if (map->map[cur->j][cur->i] == ft_tolower(map->c))
		map->map[cur->j][cur->i] = map->c;
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

void	print_array(t_map *map, t_dot *cur)
{
	int **arr;

	arr = map->heatmap;
	ft_fprintf(2, "%- 5d", arr[cur->j][cur->i]);
	if (cur->i == map->width - 1)
		ft_fprintf(2, "\n");
}

/*
**	goes through all dots in a map and
*/

void	calculate_heatmap(t_map *map)
{
	if (!map->heatmap)
		get_heatmap(map);
	map_a_map(map, &update_enemies);
	map_a_map(map, &calculate_heat);
//	map_a_map(map, &print_array);
}