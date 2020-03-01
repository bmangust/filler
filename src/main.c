#include "filler.h"

int		main(void)
{
	t_map 	*map;
	int i = -1;

	map = init_map();
	get_player(map);
//	if (map->c == 'O')
//		write(2, "\nI am O\n", 8);
//	else
//		write(2, "\nI am X\n", 8);
	if (errno != 0)
	{
		free_map(&map);
		return (0);
	}
	while (get_map(map) != ERROR && ++i < 100)
	{
		if (next_move(map) == NO_CANDIDATES)
			break;
	}
	free_map(&map);
	return 0;
}
