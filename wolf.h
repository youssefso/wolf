#ifndef WOLF_H
# define WOLF_H
# include "stdio.h"
# include "libft.h"
# include "math.h"
# include "mlx.h"
# define WIDTH 800
# define HEIGTH 800


typedef struct	s_vf
{
	float	x;
	float	y;
}				t_vf;

typedef struct	s_vi
{
	int	x;
	int y;
}				t_vi;
typedef struct	s_player
{
	t_vi	pos;
	t_vf	dir;
	t_vf	dir_colum;
}				t_player;

typedef struct	s_p
{
	void	*win;
	void		*img;
	void	*init;
	unsigned int	*data;
	t_player	player;
}				t_p;

int	**ft_read_file(char *file_name);

#endif
