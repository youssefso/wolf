/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymoukhli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 18:16:33 by ymoukhli          #+#    #+#             */
/*   Updated: 2019/08/10 16:03:52 by ymoukhli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#define mapWidth 24
#define mapHeight 24

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

	dir = player.dir_colum;
	printf("dir x: %f, y %f\n", dir.x, dir.y);
	if (dir.x >= 0)
	{
		(*grid_point).x =  (int)(player.pos.x / 64) * 64 + 64;
		(*step).x = 64;
	}
	else
	{
		(*grid_point).x = (int)(player.pos.x / 64) * 64 - 1;
		if ((*grid_point).x < 0)
			(*grid_point).x = 0;
		(*step).x = -64;
	}
	if (dir.y >= 0)
	{
		(*grid_point).y = player.pos.y + (fabsf(player.pos.x - (*grid_point).x) * tan(alpha));
		(*step).y = 64 * tan(alpha);
	}
	else
	{
		(*grid_point).y = player.pos.y - (fabsf(player.pos.x - (*grid_point).x) * tan(alpha));
		(*step).y = - 64 * tan(alpha);
	} if (grid_point->x < 0)
		grid_point->x = 0;
	if (grid_point->y < 0)
		grid_point->y = 0;
}
void	ft_sethorizontal_variable(t_player player,t_vf *grid_point, t_vf *step, float alpha)
{
	t_vf	dir;

	dir = player.dir_colum;
	if (dir.y >= 0)
	{
		grid_point->y = (int)(player.pos.y /64) * 64 + 64;
		step->y = 64;
	}
	else
	{
		grid_point->y = (int)(player.pos.y / 64) * 64 - 1;
		step->y = -64;
	}
	if (dir.x >= 0)
	{
		grid_point->x = player.pos.x + (fabsf(player.pos.y - grid_point->y) / tan(alpha));
		step->x = 64 / tan(alpha);
	}
	else
	{
		grid_point->x = player.pos.x - (fabsf(player.pos.y - grid_point->y) / tan(alpha));
		step->x = -64 / tan(alpha);
	}
	if (grid_point->x < 0)
		grid_point->x = 0;
	if (grid_point->y < 0)
		grid_point->y = 0;
}

double	ft_vertical_check(t_player player, float alpha, int map[24][24])
{
	t_vf	grid_point;
	t_vf	step;
	int hit;
	double distance = 0;
	int x;
	int y;
	int count = 0 ;

	hit = 0;
	ft_setvertical_variable(player, &grid_point, &step,alpha);
	printf("A: x %f y %f\n", grid_point.x, grid_point.y);
	y = (int)(grid_point.y / 64);
	x = (int)(grid_point.x / 64);
	while (hit == 0 && y > 0 && y < 24 && x > 0 && x < 24)
	{
	//	printf("grid_point :%f %f||||||||grid %d, %d\n player: %d, %d\n",\
	//		grid_point.x, grid_point.y, x, y, player.pos.x, player.pos.y);
		if (map[(int)(grid_point.y / 64)][(int)(grid_point.x / 64)] != 0)
		{
			hit = 1;
			distance = fabsf(player.pos.x - grid_point.x) / cos(alpha);
		}
		grid_point = vec_add(grid_point, step);
	}
	return distance;
}
double	ft_horizontal_check(t_player player, float alpha, int map[24][24])
{
	t_vf	grid_point;
	t_vf	step;
	int		hit;
	double	distance = 1e30;
	int x;
	int y;

	hit = 0;
	ft_sethorizontal_variable(player, &grid_point, &step,alpha);
	y = (int)(grid_point.y / 64);
	x = (int)(grid_point.x / 64);
	while (hit == 0 && y > 0 && y < 24 && x > 0 && x < 24)
	{
		if (map[(int)(grid_point.y / 64)][(int)(grid_point.x / 64)] != 0)
		{
			hit = 1;
			distance = fabsf(player.pos.x - grid_point.x) / cos(alpha);
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
			mlx_pixel_put(p->init, p->win, x, y++, 0xFFFFFF);
}

void	ft_loop(t_player player, int map[24][24], t_p *param)
{
	int x;
	double t1, t2;
	t_vf dir;
	double ang_colum;
	double i;
	double	alpha;
	double	p_dist;

	ang_colum = 60 / (double)WIDTH;
	ang_colum = ft_rad(ang_colum);
	p_dist = (int)((WIDTH / 2) / tan(ft_rad(30)));
	x = 0;
	i = 0;
	while (x < WIDTH)
	{
		t1 = 1e20;
		t2 = 1e20;
		player.dir_colum = vec_rot(player.dir, -0.523599 + i);
		alpha = ft_alpha(player.dir_colum);
		t1 = ft_vertical_check(player, alpha, map);
		t2 = ft_horizontal_check(player, alpha, map);
		t1 = ft_min_value(t1, t2);
		ft_draw_colum(t1, p_dist, param, x);
		i += ang_colum;
		x++;
	}
}
void	ft_init(t_p *p)
{
	int WorldMap[mapWidth][mapHeight]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	t_player ply;

	ply.pos = (t_vi){3,3};
	ply.pos.x *= 64;
	ply.pos.y *= 64;
	ply.dir = (t_vf){1, 0};
	ft_loop(ply, WorldMap, p);
}

int main(int ac, char **av)
{
	t_p *p;

	//if (!(p = (t_p *)malloc(sizeof(t_p))))
	//	return 0;
	//ft_mlx_init(p);
	//ft_init(p);
	ft_read_file(av[1]);
	//mlx_loop(p->init);
}
