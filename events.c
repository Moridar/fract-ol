/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:13:18 by bsyvasal          #+#    #+#             */
/*   Updated: 2024/01/11 10:56:26 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	destroy(t_fractol *f)
{
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
	return (0);
}

static int	keydown_extend(int keycode, t_fractol *f)
{
	if (keycode == 15)
	{
		f->zoom = 1;
		f->xcenter = 0;
		f->ycenter = 0;
	}
	else if (keycode == 18 && f->fractaltype != 1)
	{
		f->fractaltype = 1;
		f->zoom = 1;
	}
	else if (keycode == 19 && f->fractaltype != 2)
	{
		f->fractaltype = 2;
		f->zoom = 1;
	}
	return (0);
}

int	keydown(int keycode, t_fractol *f)
{
	if (keycode == 53)
		return (destroy(f));
	if (keycode == 36)
	{
		if (--(f->run))
			f->run = 1;
	}
	else if (keycode == 13 || keycode == 126)
		f->ycenter -= 0.1 / f->zoom;
	else if (keycode == 1 || keycode == 125)
		f->ycenter += 0.1 / f->zoom;
	else if (keycode == 0 || keycode == 123)
		f->xcenter -= 0.1 / f->zoom;
	else if (keycode == 2 || keycode == 124)
		f->xcenter += 0.1 / f->zoom;
	else if (keycode == 5)
		f->zoom *= 1.1;
	else if (keycode == 4)
		f->zoom /= 1.1;
	else
		keydown_extend(keycode, f);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractol *f)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		f->xcenter += ((double) x / f->width * 4.0 - 2) / f->zoom;
		f->ycenter += ((double) y / f->height * 4.0 - 2) / f->zoom;
	}
	else if (button == 2 && f->fractaltype == 2)
	{
		f->xconstant = (f->xconstant + (double) x / f->width / 300);
		f->yconstant = (f->yconstant + (double) y / f->height / 100);
		if (f->xconstant > 1)
			f->xconstant *= -1;
		if (f->yconstant > 1)
			f->yconstant *= -1;
	}
	else if (button == 5)
		f->zoom *= 1.5;
	else if (button == 4)
		f->zoom /= 1.5;
	return (0);
}

int	render_next_frame(t_fractol *f)
{
	if (f->run)
		f->zoom *= 1.1;
	draw(f);
	return (0);
}
