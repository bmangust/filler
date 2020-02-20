#include "filler.h"

int		main(void)
{
	t_map 	*map;

	map = init_map();
	get_player(map);
	if (errno == 0)
		get_map(map);
	while (42)
	{
		next_move(map);
		get_map(map);
	}
	free_map(map);


	return 0;
}
