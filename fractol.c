/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:51:59 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/01/11 11:32:58 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	str_isdouble(char *str)
{
	int	decimal_used;

	if (*str == '-')
		str++;
	decimal_used = 0;
	while (*str)
	{
		if (*str == ',' || *str == '.')
		{
			++decimal_used;
			str++;
		}
		if (!ft_isdigit(*str) || decimal_used > 1)
			return (0);
		str++;
	}
	return (1);
}

static int	print_msg(int msgno)
{
	if (msgno == 0)
		ft_printf("Missing or invalid parameter\n"
			" - Mandelbrot\n - Julia x y\n");
	if (msgno == 1)
		ft_printf("Missing or invalid parameter for julia set\n - Julia"
			" -0.5 0.5\n");
	if (msgno == 2)
		ft_printf("Controls:\nWASD/Arrows: Move\n"
			"GH: Zoom\nEnter: Auto zoom\nR: Reset\n"
			"Mouse Scrolls: Zoom\n"
			"Mouse Left Click: Move\n"
			"Mouse Right Click: Increase Julia values\n"
			"1: Mandelbrot\n2: Julia\n");
	return (0);
}

static void	f_init(t_fractol *f, int type)
{
	f->fractaltype = type;
	f->run = 0;
	f->width = 800;
	f->height = 600;
	f->zoom = 1;
	f->xcenter = 0;
	f->ycenter = 0;
	if (type != 2)
	{
		f->xconstant = -0.4;
		f->yconstant = 0.6;
	}
	f->mlx = mlx_init();
	f->win = mlx_new_window(f->mlx, f->width, f->height, "Fract-ol");
	f->img = mlx_new_image(f->mlx, f->width, f->height);
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel, &f->line_length,
			&f->endian);
	mlx_hook(f->win, ON_DESTROY, 0, destroy, f);
	mlx_hook(f->win, ON_KEYDOWN, 0, keydown, f);
	mlx_mouse_hook(f->win, mouse_hook, f);
	mlx_loop_hook(f->mlx, render_next_frame, f);
	print_msg(2);
	mlx_loop(f->mlx);
}

int	main(int argc, char *argv[])
{
	t_fractol	f;

	if (!ft_strncmp(argv[1], "Mandelbrot", 11))
		f_init(&f, 1);
	else if (!ft_strncmp(argv[1], "Julia", 6))
	{
		if (argc != 4 || !str_isdouble(argv[2]) || !str_isdouble(argv[3]))
			return (print_msg(1));
		f.xconstant = ft_atod(argv[2]);
		f.yconstant = ft_atod(argv[3]);
		f_init(&f, 2);
	}
	return (print_msg(0));
}
