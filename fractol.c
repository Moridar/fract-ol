/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:51:59 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/01/09 15:02:50 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	destroy(t_fractol *f)
{
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
	return (0);
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
	f->xconstant = -0.4;
	f->yconstant = 0.6;
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, f->width, f->height, "Fract-ol");
	f->img = mlx_new_image(f->mlx, f->width, f->height);
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel, &f->line_length,
			&f->endian);
	mlx_hook(f->win, ON_DESTROY, 0, destroy, f);
	mlx_hook(f->win, ON_KEYDOWN, 0, keydown, f);
	mlx_mouse_hook(f->win, mouse_hook, f);
	mlx_loop_hook(f->mlx, render_next_frame, f);
}

static int	printerrormsg(t_fractol *f, int errno)
{
	if (errno == 0)
		ft_printf("Missing or invalid parameter\n"
			" - Mandelbrot\n - Julia x y\n");
	if (errno == 1)
		ft_printf("Missing or invalid parameter for julia set\n - Julia"
			" -0.5 0.5");
	if (errno == 2)
		return (ft_printf("Controls:\nWASD/Arrows: Move\n"
				"GH: Zoom\nEnter: Auto zoom\nR: Reset\n"
				"Mouse Scrolls: Zoom\n"
				"Mouse Left Click: Move\n"
				"Mouse Right Click: Increase Julia values\n"
				"1: Mandelbrot\n2: Julia\n"));
	return (destroy(f));
}

int	main(int argc, char *argv[])
{
	t_fractol	f;

	finit(&f);
	if (argc <= 1)
		return (printerrormsg(&f, 0));
	else if (!ft_strncmp(argv[1], "Mandelbrot", 11))
		f.fractaltype = 1;
	else if (!ft_strncmp(argv[1], "Julia", 6))
	{
		if (argc != 4)
			return (printerrormsg(&f, 1));
		f.fractaltype = 2;
		f.xconstant = ft_atod(argv[2]);
		f.yconstant = ft_atod(argv[3]);
		if ((f.xconstant == 0 && !ft_strchr(argv[2], '0'))
			|| (f.yconstant == 0 && !ft_strchr(argv[3], '0')))
			return (printerrormsg(&f, 1));
	}
	else
		return (printerrormsg(&f, 0));
	printerrormsg(&f, 2);
	mlx_loop(f.mlx);
	return (0);
}
