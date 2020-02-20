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

/*
**	return position to place the piece
*/

void	find_position(t_map *map, t_piece *p)
{
	int		i[2];
	t_dot	*dot;

	dot = map->dots;

}

void	next_move(t_map *map)
{
	t_piece	*p;
	int		x;
	int		y;

	x = 8;
	y = 2;
	p = init_piece();
	process_map(map, p);
	ft_printf("%d %d", x, y);
}