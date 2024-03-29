/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsyvasal <bsyvasal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:51:37 by bsyvasal          #+#    #+#             */
/*   Updated: 2023/10/27 10:58:43 by bsyvasal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int i, int p)
{
	if (p < 0)
		return (0);
	if (p == 0)
		return (1);
	if (p > 1)
		return (i * ft_power(i, p - 1));
	return (i);
}
