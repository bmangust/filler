/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:44:42 by akraig            #+#    #+#             */
/*   Updated: 2020/04/18 17:33:07 by akraig           ###   ########.fr       */
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

int			count_enemies(t_map *map)
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

int			is_enemy(t_map *map, t_dot *dot)
{
	if (map->map[dot->j][dot->i] == map->enemy ||
		map->map[dot->j][dot->i] == map->enemynew)
		return (1);
	return (0);
}

// static int	is_new_enemy(t_map *map, t_dot *dot)
// {
// 	if (map->map[dot->j][dot->i] == map->enemynew)
// 		return (1);
// 	return (0);
// }

/*
**	updates enemies list, adds all enemy dots to a list
*/

void		update_enemies(t_map *map, t_dot *cur)
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

/*
**	returns next enemy in list (amonf all on only new)
*/

t_dot		*get_next_enemy(t_map *map, t_dot *enemy, int only_new)
{
	t_dot	*tmp;

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
**	NOT USED
*/

int 		check_enemies(t_map *map, t_dot *cur)
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
