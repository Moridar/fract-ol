/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:51:59 by bsyvasal          #+#    #+#             */
/*   Updated: 2023/12/04 17:57:20 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	finit(t_fractol *f)
{
	f->fractaltype = 0;
	f->run = 0;
	f->width = 800;
	f->height = 600;
	f->zoom = 1;
	f->xcenter = 0;
	f->ycenter = 0;
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, f->width, f->height, "Hello world!");
	f->img = mlx_new_image(f->mlx, f->width, f->height);
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel, &f->line_length,
			&f->endian);
	mlx_hook(f->win, ON_DESTROY, 0, destroy, f);
	mlx_hook(f->win, ON_KEYDOWN, 0, keydown, f);
	mlx_mouse_hook(f->win, mouse_hook, f);
	mlx_loop_hook(f->mlx, render_next_frame, f);
}

int	printerrormsg(t_fractol *f, int errno)
{
	if (errno == 0)
		ft_printf("Missing or invalid parameter\n"
			" - Mandelbrot\n - Julia x y\n");
	if (errno == 1)
		ft_printf("Missing or invalid parameter for julia set\n - Julia"
			" 1.0 1.0");
	return (destroy(f));
}

int	main(int argc, char *argv[])
{
	t_fractol	f;

	finit(&f);
	if (argc <= 1)
		return (printerrormsg(&f, 0));
	else if (!ft_strncmp(argv[1], "Mandelbrot", 10))
		f.fractaltype = 1;
	else if (!ft_strncmp(argv[1], "Julia", 5))
	{
		if (argc != 4)
			return (printerrormsg(&f, 1));
		f.fractaltype = 2;
		f.xconstant = ft_atod(argv[2]);
		f.yconstant = ft_atod(argv[3]);
	}
	else
		return (printerrormsg(&f, 0));
	draw(&f);
	mlx_loop(f.mlx);
}
