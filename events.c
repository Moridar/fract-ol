/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:13:18 by bsyvasal          #+#    #+#             */
/*   Updated: 2023/12/04 17:55:17 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <stdlib.h>

int	destroy(t_fractol *f)
{
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
	return (0);
}

int	keydown(int keycode, t_fractol *f)
{
	if (keycode == 53)
		return (destroy(f));
	if (keycode == 36)
		if (--(f->run))
			f->run = 1;
	if (keycode == 13 || keycode == 126)
		f->ycenter -= 0.1 / f->zoom;
	if (keycode == 1 || keycode == 125)
		f->ycenter += 0.1 / f->zoom;
	if (keycode == 0 || keycode == 123)
		f->xcenter -= 0.1 / f->zoom;
	if (keycode == 2 || keycode == 124)
		f->xcenter += 0.1 / f->zoom;
	if (keycode == 5)
		f->zoom *= 1.1;
	if (keycode == 4)
		f->zoom /= 1.1;
	draw(f);
	return (0);
}

// int	keyup(int keycode, t_fractol *f)
// {
// 	(void)f;
// 	printf("%d released\n", keycode);
// 	return (0);
// }

int	mouse_hook(int button, int x, int y, t_fractol *f)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		f->xcenter += ((double) x / f->width * 4.0 - 2) / f->zoom;
		f->ycenter += ((double) y / f->height * 4.0 - 2) / f->zoom;
	}
	if (button == 5)
		f->zoom *= 1.1;
	if (button == 4)
		f->zoom /= 1.1;
	draw(f);
	return (0);
}

int	render_next_frame(t_fractol *f)
{
	if (f->run)
	{
		f->zoom *= 1.05;
		draw(f);
	}
	return (0);
}
