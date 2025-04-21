/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 02:30:12 by modat             #+#    #+#             */
/*   Updated: 2025/04/21 20:20:53 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

double	ft_atof(const char *nptr)
{
	unsigned int	i;
	int				sign;
	double			res;

	i = 0;
	sign = 1;
	res = 0.0;
	while (nptr[i] == ' ' || nptr[i] == '\t')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		res = (res * 10) + (nptr[i++] - '0');
	if (nptr[i] == '.')
	{
		i++;
		res += ft_atof1(nptr, i);
	}
	return (sign * res);
}

double	ft_atof1(const char *nptr, unsigned int i)
{
	double	fractional;
	double	divisor;

	fractional = 0.0;
	divisor = 10.0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		fractional += (nptr[i] - '0') / divisor;
		divisor *= 10;
		i++;
	}
	return (fractional);
}

int	mem_alloc(t_mlx **fractol)
{
	*fractol = malloc(sizeof(t_mlx));
	if (!*fractol)
	{
		perror("Memory allocation failed");
		return (1);
	}
	return (0);
}
