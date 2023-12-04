/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:50:21 by bsyvasal          #+#    #+#             */
/*   Updated: 2023/12/04 16:46:18 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	colorize(t_fractol *f, int i, int j, int n)
{
	int			color;
	int			colorset[3];

	colorset[0] = 0x004f182b;
	colorset[1] = 0x0024f18;
	colorset[2] = 0x00aa2e88;
	if (n >= 100)
		color = 0;
	else
		color = colorset[n % 3];
	my_mlx_pixel_put(f, i, j, color);
}

static void	mandelbrot(t_fractol *f, int i, int j)
{
	int			n;
	double		x[3];
	double		y[3];
	double		tmpx;

	x[0] = (i / (double) f->width * 4.0 - 2) / f->zoom + f->xcenter;
	y[0] = (j / (double) f->height * 4.0 - 2) / f->zoom + f->ycenter;
	x[1] = 0;
	y[1] = 0;
	x[2] = 0;
	y[2] = 0;
	n = 0;
	while (x[2] + y[2] <= 2 * 2 && n++ <= 100)
	{
		tmpx = x[2] - y[2] + x[0];
		y[1] = 2 * x[1] * y[1] - y[0];
		x[1] = tmpx;
		x[2] = x[1] * x[1];
		y[2] = y[1] * y[1];
	}
	colorize(f, i, j, n);
}

static void	julia(t_fractol *f, int i, int j)
{
	int			n;
	double		x[3];
	double		y[3];
	double		tmpx;

	x[0] = f->xconstant;
	y[0] = f->yconstant;
	x[1] = (i / (double) f->width * 4.0 - 2) / f->zoom + f->xcenter;
	y[1] = (j / (double) f->height * 4.0 - 2) / f->zoom + f->ycenter;
	x[2] = x[1] * x[1];
	y[2] = y[1] * y[1];
	n = 0;
	while (x[2] + y[2] <= 2 * 2 && n++ <= 100)
	{
		tmpx = x[2] - y[2];
		y[1] = 2 * x[1] * y[1] + y[0];
		x[1] = tmpx + x[0];
		x[2] = x[1] * x[1];
		y[2] = y[1] * y[1];
	}
	colorize(f, i, j, n);
}

void	draw(t_fractol *f)
{
	int		i;
	int		j;
	void	(*func)();

	if (f->fractaltype == 1)
		func = mandelbrot;
	else if (f->fractaltype == 2)
		func = julia;
	mlx_clear_window(f->mlx, f->win);
	i = -1;
	while (++i < f->width)
	{
		j = -1;
		while (++j < f->height)
			func(f, i, j);
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
