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
*/

int		get_distance(t_dot *enemy, t_dot *cur)
{
	int64_t diff[3];

	diff[0] = ft_absint(enemy->i - cur->i);
	diff[1] = ft_absint(enemy->j - cur->j);
	diff[2] = diff[0] + diff[1];
	return (diff[2]);
}

void	get_heatmap(t_map *map)
{
	int	i[2];

	map->heatmap = (int**)malloc(sizeof(int*) * map->height);
	i[1] = -1;
	while (++i[1] < map->width)
	{
		map->heatmap[i[1]] = (int*)malloc(sizeof(int) * map->width);
		i[0] = -1;
		while (++i[0] < map->width)
			map->heatmap[i[1]][i[0]] = INT16_MAX;
	}
}

void	find_enemy(t_map *map, t_dot *enemy, int i, int j)
{
	if (map->map[j][i] == map->enemy ||	map->map[j][i] == map->enemynew)
		i++;
	if (i == map->width)
	{
		i = 0;
		j++;
	}
	while (map->map[j][i] != map->enemy ||
			map->map[j][i] != map->enemynew)
	{
		i++;
		if (i == map->width)
		{
			i = 0;
			j++;
		}
	}
	enemy->i = i;
	enemy->j = j;
}

void 	update_neighbours(int **heatmap, t_dot *cur)
{
	int i[2];

	i[0] = cur->i - 1;
	i[1] = cur->j;

}

void	fill_heatmap(t_map *map)
{
	t_dot	*cur;
	t_dot	*next;
	t_dot	*prev;


	cur = init_dot(0, 0);
	next = init_dot(0, 0);
	prev = init_dot(0, 0);
	while (cur->j < map->height && cur->i < map->width)
	{
		find_enemy(map, next, cur->i, cur->j);
		while (cur->i != next->i && cur->j != next->j)
		{
			if (cur->i == map->width)
			{
				cur->i = 0;
				cur->j++;
			}
			map->heatmap[cur->j][cur->i] = get_distance(next, cur);
			cur->i++;
		}
		update_neighbours(map, cur);
	}




}

void	get_enemies(t_map *map)
{

}