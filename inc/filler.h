#ifndef FILLER_H
# define FILLER_H
# define OK 0
# define NO_CANDIDATES -2
# define SECOND_IS_BETTER 0
# define FIRST_IS_BETTER 1
# define SIMILAR_DOTS 2

# include "ft_printf.h"
# include "errno.h"
# include <stdio.h>

typedef struct		s_dot
{
	int				i;
	int				j;
	int				heat_max;
	int				heat;
	int				c;
	int				free_t;
	int				free_b;
	int				free_l;
	int				free_r;
	struct s_dot	*next;
	struct s_dot	*prev;
}					t_dot;

/*
**	structure for storing new piece
**	m_ fields are for margins (empty lines)
**	map stores actual piece
*/

typedef struct		s_piece
{
	int				width;
	int				height;
	int				m_top;
	int				m_left;
	int				m_bottom;
	int				m_right;
	char			**map;
}					t_piece;

typedef struct		s_map
{
	char			c;
	char			enemy;
	char			enemynew;
	int				width;
	int				height;
	int 			new_enemies;
	int				placeable_candidates;
	char			**map;
	int 			**heatmap;
	t_dot			*enemies;
	t_dot			*placeable;
	t_dot			***candidates;
}					t_map;



int					set_errno(int val);
t_dot				*init_dot(int i, int j, int c);
t_dot				*add_last_dot(t_dot **head, t_dot *new);
void				delete_dot(t_dot *dot);
void				clear_dots(t_dot **head);
t_dot				*compare_dots(t_dot *cur, t_dot *dot);
void				get_free_space(t_map *map, int i, int j, t_piece *p);
t_map 				*init_map(void);
int					get_player(t_map *map);
int					get_map(t_map *map);
void				free_map(t_map **map);
void				clear_map(t_map *map);
t_piece				*init_piece();
void				delete_piece(t_piece **p);
int					get_piece(t_piece *p);
void				get_pieces_params(t_piece *p);
int					next_move(t_map *map);
void				process_map(t_map *map, t_piece *p);
void				get_candidates(t_map *map, t_piece *p, t_dot *best);
t_dot				*choose_candidate(t_dot *dots, t_map *map, int comp(t_dot, t_dot, t_map));
int					is_placeable(t_dot *coord, t_map *map, t_piece *p);
t_dot				*find_dot(t_dot *head, t_dot *dot);
void				get_array_of_candidates(t_map *map);
void				calculate_heatmap(t_map *map);
void				get_heatmap(t_map *map);
void				map_a_map(t_map *map, void f(t_map*, t_dot*));
void				reset_heatmap(t_map *map, t_dot *cur);
void			 	replace_lowercase_c(t_map *map, t_dot *cur);


void				map_dots(t_dot *dot, void f(t_dot d));
void				print_dot_heat(t_dot d);
#endif