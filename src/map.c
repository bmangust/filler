/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:45:48 by akraig            #+#    #+#             */
/*   Updated: 2020/03/12 19:45:50 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_map 	*init_map(void)
{
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	map->height = 0;
	map->width = 0;
	map->c = 0;
	map->placeable_candidates = 0;
	map->cnt_enemies = 0;
	map->is_alive = 1;
	map->map = NULL;
	map->heatmap = NULL;
	map->enemies = NULL;
	map->placeable = NULL;
	map->candidates = NULL;
	return (map);
}

int		get_player(t_map *map)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(0, &line)) > 0 &&
			!(ft_strstr(line, "$$$") &&
			ft_strstr(line, "akraig")))
		free(line);
	if (ret == ERROR)
		return set_errno(EIO);
	if (map && ft_strstr(line, "akraig"))
	{
		map->c = ft_strstr(line, "p1") ? 'O' : 'X';
		map->enemy = map->c == 'O' ? 'X' : 'O';
		map->enemynew = map->c == 'O' ? 'x' : 'o';
	}
	else
		return set_errno(EINVAL);
	return (OK);
}

int		get_map(t_map *map)
{
	char	*line;
	int		lines;

	while (get_next_line(0, &line) && !ft_strstr(line, "Plateau"))
		free(line);
	map->width = map->width ? map->width : ft_atoi(ft_strrchr(line, ' '));
	map->height = map->height ? map->height : ft_atoi(ft_strchr(line, ' '));
	free(line);
	lines = -1;
	get_next_line(0, &line);
	free(line);
	map->map = (char**)malloc(sizeof(char*) * map->height + 1);
	while (++lines < map->height)
	{
		if (get_next_line(0, &line) == -1)
			return set_errno(EIO);
		map->map[lines] = ft_strdup(line + 4);
		free(line);
	}
	map->map[lines] = NULL;
	map_a_map(map, &replace_lowercase_c);
	return (OK);
}

void	clear_map(t_map *map)
{
	int i;

	if (!map)
		return;
	i = -1;
	while (++i < map->height)
		free(map->map[i]);
	map->map = NULL;
}


int 	free_map(t_map **map)
{
	if (!map || !*map)
		return (0);
	clear_map(*map);
	clear_dots(&((*map)->enemies));
	free(*map);
	*map = NULL;
	return (0);
}
