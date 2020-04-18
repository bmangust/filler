/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akraig <akraig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:45:02 by akraig            #+#    #+#             */
/*   Updated: 2020/04/18 16:19:19 by akraig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(void)
{
	t_map 	*map;

	map = init_map();
	get_player(map);
	// if (map->c == 'O')
	// 	write(2, "\nI am O\n", 8);
	// else
	// 	write(2, "\nI am X\n", 8);
	if (errno != 0)
		return (free_map(&map));
	while (get_map(map) != ERROR)
		if (!count_enemies(map))
		{
			if (safe_play(map) == NO_CANDIDATES)
				break;
		}
		else if (next_move(map) == NO_CANDIDATES)
			break;
	return (free_map(&map));
}
