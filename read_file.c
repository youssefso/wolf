#include "wolf.h"
int		ft_num_inlin(char	*str, int *i)
{
	int u;
	int lvl;
	int num;

	u = *i;
	lvl = 0;
	num = 0;
	while (str[u] != '\0' && str[u] != '\n')
	{
		if (lvl == 0 && ft_isdigit(str[u]))
			lvl = 1;
		else if (lvl == 1 && ft_isdigit(str[u]) == 0)
		{
			lvl = 0;
			num++;
		}
		u++;
	}
	if (lvl == 1)
		num++;
	if (str[u] == '\n')
		u++;
	*i = u;
	return (num);
}
t_vi	ft_check_lines(char *str)
{
	int		i;
	t_vi	dim;
	int		num;
	int		check_num;
	
	check_num = 0;
	dim = (t_vi){0,0};
	i = 0;
	while (str[i] != '\0')
	{
		dim.y++;
		num = ft_num_inlin(str, &i);
		if (check_num == 0)
			check_num = num;
		else if (num != check_num)
			exit(0);
	}
	dim.x = check_num;
	return (dim);
}

int	**ft_alloc_map(int y, int x)
{
	int **map;
	int i;

	i = 0;
	map = (int **)malloc(sizeof(int *) * y);
	while (i < y)
		map[i++] = (int *)malloc(sizeof(int) * x);
	return (map);
}

void	ft_fill_map(int **map, t_vi dim, char *str)
{
	int x;
	int i;
	int y;

	y = 0;
	i = 0;
	while (y < dim.y)
	{
		x = 0;
		while (x < dim.x)
		{
			map[y][x] = ft_atoi(str + i);
			i = ft_nextnum(str, i);
			if (i == -1)
				break ;
			x++;
		}
		y++;
	}
}
t_map ft_read_file(char *file_name)
{
	int **map;
	char *str;
	t_vi dim;
	t_map m;

	str = ft_file(file_name);
	dim = ft_check_lines(str);
	map = ft_alloc_map(dim.y, dim.x);
	ft_fill_map(map, dim, str);
	ft_puttab(map, dim.y, dim.x);
	m.map = map;
	m.dim = dim;
	return m;
}
