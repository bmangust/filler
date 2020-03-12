/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:45:02 by akraig            #+#    #+#             */
/*   Updated: 2020/03/12 19:45:04 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (count_enemies(map))
			safe_play(map);
		else if (next_move(map) == NO_CANDIDATES)
			break;
	free_map(&map);
	return 0;
}
