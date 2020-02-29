#include "filler.h"

int		main(void)
{
	t_map 	*map;
	int i = -1;

	map = init_map();
	get_player(map);
	if (errno == 0)
		get_map(map);
	if (errno != 0)
	{
		free_map(&map);
		return (0);
	}
	while (++i < 100)
	{
		next_move(map);
		get_map(map);
	}
	free_map(&map);


	return 0;
}
