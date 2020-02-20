#ifndef FILLER_H
# define FILLER_H
# define OK 0

# include "ft_printf.h"
# include "errno.h"
# include <stdio.h>

typedef struct		s_dot
{
	int				i;
	int				j;
	int				free_t;
	int				free_b;
	int				free_l;
	int				free_r;
	struct s_dot	*next;
	struct s_dot	*prev;
}					t_dot;

typedef struct		s_map
{
	int				c;
	int				width;
	int				height;
	char			**map;
	t_dot			*dots;
}					t_map;



typedef struct		s_piece
{
	int				width;
	int				height;
	int				pos;
	int				pos_bottom;
	int				m_top;
	int				m_left;
	int				m_bottom;
	int				m_right;
	char			**map;
}					t_piece;

int					set_errno(int val);
t_dot				*init_dot(int i, int j);
t_dot				*add_last_dot(t_dot **head, t_dot *new);
void				clear_dots(t_dot **head);
void				get_free_space(t_map *map, int i, int j, t_piece *p);
t_map 				*init_map(void);
int					get_player(t_map *map);
int					get_map(t_map *map);
void				free_map(t_map *map);
t_piece				*init_piece();
int					get_piece(t_piece *p);
void				get_pieces_params(t_piece *p);
void				next_move(t_map *map);
void				process_map(t_map *map, t_piece *p);

#endif