#include "filler.h"

t_map 	*init_map(void)
{
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	map->height = 0;
	map->width = 0;
	map->c = 0;
	map->map = NULL;
	map->dots = NULL;
	return (map);
}

int		get_player(t_map *map)
{
	char *line;

	if (get_next_line(0, &line) == ERROR)
		return set_errno(EIO);
	if (map && ft_strnstr(line, "$$$", 3))
		map->c = ft_strstr(line, "p1") ? 'O' : 'X';
	else
		return set_errno(EINVAL);
	return (0);
}

int		get_map(t_map *map)
{
	char	*line;
	int		lines;

	get_next_line(0, &line);
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
		map->map[lines] = line + 4;
	}
	map->map[lines] = NULL;
	return (0);
}

void	clear_map(t_map *map)
{
	int i;

	if (!map)
		return;
	i = -1;
	while (++i < map->height)
		free(map->map[i]);
}


void	free_map(t_map *map)
{
	if (!map)
		return;
	clear_map(map);
	clear_dots(&map->dots);
	free(map);
}