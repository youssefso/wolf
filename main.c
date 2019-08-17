/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoukhli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:16:33 by ymoukhli          #+#    #+#             */
/*   Updated: 2019/08/17 15:19:18 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_light_pixel(t_p *p, int x, int y, int col)
{
	int i;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGTH)
		return ;
	i = y * HEIGTH + x;
	p->data[i] = col;
}
void	ft_mlx_init(t_p *p)
{
	int b_p;
	int s_l;
	int endian;

	p->init = mlx_init();
	p->win = mlx_new_window(p->init, WIDTH, HEIGTH, "WOLF");
	p->img = mlx_new_image(p->init, WIDTH, HEIGTH);
	p->data = (unsigned int *)mlx_get_data_addr(p->img, &b_p, &s_l, &endian);
}
/////////////////////vect rot/////////////////////
t_vf	vec_rot(t_vf v, float a)
{
	t_vf	v1;
	v1.x = v.x * cos(a) - v.y * sin(a);
	v1.y = v.x * sin(a) + v.y * cos(a);
	return (v1);
}

t_vf	vec_sub(t_vf v1, t_vf v2)
{
	t_vf v0;

	v0.x = v1.x - v2.x;
	v0.y = v1.y - v2.y;
	return v0;
}

t_vf	vec_mult(t_vf v1, float a)
{
	t_vf v0;

	v0.x = v1.x * a;
	v0.y = v1.y * a;
	return v0;
}

t_vf	vec_add(t_vf v1, t_vf v2)
{
	t_vf v0;

	v0.x = v1.x + v2.x;
	v0.y = v1.y + v2.y;
	return v0;
}
/////////////////////********/////////////////////

float	ft_rad(float a)
{
	return ((a * M_PI) / 180);
}
//////////////////////////////////////////////////

t_vf	vec_normalise(t_vf v)
{
	t_vf v1;
	float a;

	a = sqrtf(v.x * v.x + (v.y * v.y));
	v1.x = v1.x / a;
	v1.y = v1.y / a;
	return v1;
}

float	vec_dot(t_vf v, t_vf v1)
{
	float a;

	a = v.x * v1.x + (v.y * v1.y);
	return a;
}
/////////////////hit check//////////////////////

/////////////////////////////////////////////////
double	ft_alpha(t_vf dir)
{
	t_vf v;
	float alpha;

	if (dir.x < 0)
		v = (t_vf){-1, 0};
	else if (dir.x >= 0)
		v = (t_vf){1, 0};
	alpha = acosf(vec_dot(dir, v));
	return alpha;
}

double	ft_min_value(double t1, double t2)
{
	if (t1 > t2)
		t1 = t2;
	if (t1 < 0)
		t1 = 0;
	return t1;
}

void	ft_setvertical_variable(t_player player,t_vf *grid_point, t_vf *step, float alpha)
{
	t_vf dir;
	float x;

	dir = player.dir_colum;
	if (dir.x >= 0)
	{
		(*grid_point).x =  (int)(player.pos.x / 64) * 64 + 64;
		x = grid_point->x;
		(*step).x = 64;
	}
	else
	{
		(*grid_point).x = (int)(player.pos.x / 64) * 64 - 1;
		x = grid_point->x + 1;
		if ((*grid_point).x < 0)
			(*grid_point).x = 0;
		(*step).x = -64;
	}
	if (dir.y >= 0)
	{
		(*grid_point).y = player.pos.y + (fabsf(player.pos.x - x) * tan(alpha));
		(*step).y = 64 * tan(alpha);
	}
	else
	{
		(*grid_point).y = player.pos.y - (fabsf(player.pos.x - x) * tan(alpha));
		(*step).y = - 64 * tan(alpha);
	}
	if (grid_point->x < 0)
		grid_point->x = 0;
	if (grid_point->y < 0)
		grid_point->y = 0;
}

void	ft_sethorizontal_variable(t_player player,t_vf *grid_point, t_vf *step, float alpha)
{
	t_vf	dir;
	float	y;

	dir = player.dir_colum;
	if (dir.y >= 0)
	{
		grid_point->y = (int)(player.pos.y /64) * 64 + 64;
		y = grid_point->y;
		step->y = 64;
	}
	else
	{
		grid_point->y = (int)(player.pos.y / 64) * 64 - 1;
		y = grid_point->y + 1;
		step->y = -64;
	}
	if (dir.x >= 0)
	{
		grid_point->x = player.pos.x + (fabsf(player.pos.y - y) / tan(alpha));
		step->x = 64 / tan(alpha);
	}
	else
	{
		grid_point->x = player.pos.x - (fabsf(player.pos.y - y) / tan(alpha));
		step->x = - 64 / tan(alpha);
	}
	if (grid_point->x < 0)
		grid_point->x = 0;
	if (grid_point->y < 0)
		grid_point->y = 0;
}

double	ft_vertical_check(t_player player, float alpha, t_map map, int xx)
{
	t_vf	grid_point;
	t_vf	step;
	int hit;
	double distance = 1e30;
	int x;
	int y;
	int count = 0;

	hit = 0;
	ft_setvertical_variable(player, &grid_point, &step,alpha);
	while (hit == 0 && grid_point.y > 0 && grid_point.y < map.dim.y * 64)
	{
		if (xx == WIDTH /2)
		printf("point A = x %f, y %f\n", grid_point.x, grid_point.y);
		x = (grid_point.x / 64);
		y = (grid_point.y / 64);
		if (map.map[y][x] != 0)
		{
			hit = 1;
			distance = fabsf(player.pos.y - grid_point.y) / sin(alpha);
			break ;
		}
		grid_point = vec_add(grid_point, step);
	}
	return distance;
}
double	ft_horizontal_check(t_player player, float alpha, t_map map, int xx)
{
	t_vf	grid_point;
	t_vf	step;
	int		hit;
	double	distance = 1e30;
	int x;
	int y;

	hit = 0;
	ft_sethorizontal_variable(player, &grid_point, &step,alpha);
	while (hit == 0 && grid_point.x > 0 && grid_point.x < map.dim.x * 64)
	{
		if (xx == WIDTH /2)
		printf("point A = x %f, y %f\n", grid_point.x, grid_point.y);
		x = (grid_point.x / 64);
		y = (grid_point.y / 64);
		if (map.map[y][x] != 0)
		{
			hit = 1;
			distance = fabsf(player.pos.x - grid_point.x) / cos(alpha);
			break ;
		}
		grid_point = vec_add(grid_point, step);
	}
	return distance;
}

void	ft_draw_colum(double distance, double plane_distance, t_p *p, int x)
{
		int y;
		int y_max;
		double wall_height;

		wall_height = 64 / distance * plane_distance;
		y = HEIGTH / 2 - (wall_height / 2);
		y_max = HEIGTH / 2 + (wall_height / 2);
		while (y < y_max)
			ft_light_pixel(p, x, y++, 0xffffff);
}

double 	ft_true_distance(double distance, double ang_column, int x)
{
	distance = distance * cos(0.523599 - (x * ang_column));
	return distance;
}
void	ft_loop(t_player player, t_map map, t_p *param)
{
	int x;
	double t1, t2;
	t_vf dir;
	double ang_colum;
	double i;
	double	alpha;
	double	p_dist;
	static t_vf player_check;
	int xx;
	int yy;

	yy = (int)(player.pos.y / 64);
	xx = (int)(player.pos.x / 64);
	if (map.map[yy][xx] == 0)
		player_check = player.pos;
	else
		player.pos = player_check;
	param->player = player;
	ang_colum = 60 / (double)WIDTH;
	ang_colum = ft_rad(ang_colum);
	p_dist = (int)((WIDTH / 2) / tan(ft_rad(30)));
	x = 0;
	i = 0;
	while (x < WIDTH)
	{
		if (x == WIDTH / 2)
		system("clear");
		player.dir_colum = vec_rot(player.dir, -0.523599 + i);
		alpha = ft_alpha(player.dir_colum);
		t1 = ft_vertical_check(player, alpha, map, x);
		t1 = ft_true_distance(t1, ang_colum, x);
		if (x == WIDTH / 2)
			printf("distance *t1*: %f\n", t1);
		t2 = ft_horizontal_check(player, alpha, map,x);
		t2 = ft_true_distance(t2, ang_colum, x);
		if (x == WIDTH / 2)
			printf("distance *t2*: %f\n", t2);
		t1 = ft_min_value(t1, t2);
		ft_draw_colum(t1, p_dist, param, x);
		i += ang_colum;
		x++;
	}
	mlx_put_image_to_window(param->init, param->win, param->img, 0, 0);
	x = 0;
	while (x < WIDTH)
		mlx_pixel_put(param->init, param->win, x++, HEIGTH / 2, 0xff0000);
	x = 0;
	while (x < WIDTH)
		mlx_pixel_put(param->init, param->win, WIDTH / 2, x++, 0xff0000);
}
void	ft_init(t_p *p, t_map map)
{
	t_player ply;

	ply.pos = (t_vf){1,1};
	ply.pos.x *= 64 + 32;
	ply.pos.y *= 64 + 32;
	ply.dir = (t_vf){0, -1};
	ft_loop(ply, map, p);
}

int		t_kees(int key, t_p *p)
{
	int step;

	step = 3;
	if (key == 126 || key == 13)
		p->player.pos = vec_add(p->player.pos, vec_mult(p->player.dir, step));
	if (key == 125 || key == 1)
		p->player.pos = vec_sub(p->player.pos, vec_mult(p->player.dir, step));
	if (key == 123 || key == 0)
		p->player.pos = vec_add(p->player.pos, vec_mult(vec_rot(p->player.dir, 1.5708), -step));
	if (key == 14)
	{
		p->player.pos = vec_add(p->player.pos, vec_mult(vec_rot(p->player.dir, 0.523599), step));
	}
	if (key == 12)
	{
		p->player.pos = vec_add(p->player.pos, vec_mult(vec_rot(p->player.dir, -0.523599), step));
	}
	if (key == 124 || key == 2)
		p->player.pos = vec_add(p->player.pos, vec_mult(vec_rot(p->player.dir, 1.5708), step));
	if (key == 40)
		p->player.dir = vec_rot(p->player.dir, 0.1);
	if (key == 38)
		p->player.dir = vec_rot(p->player.dir, -0.1);
	if (key == 53)
		exit(0);
	ft_bzero(p->data, WIDTH * HEIGTH * 4);
	ft_loop(p->player, p->map, p);
	return (1);
}

int main(int ac, char **av)
{
	t_p *p;
	t_map map;

	if (!(p = (t_p *)malloc(sizeof(t_p))))
		return 0;
	ft_mlx_init(p);
	p->map = ft_read_file(av[1]);
	ft_init(p, p->map);
	mlx_hook(p->win, 2, 1, t_kees, p);
	mlx_loop(p->init);
}
