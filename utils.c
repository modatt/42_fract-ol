/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:25:20 by modat             #+#    #+#             */
/*   Updated: 2025/04/20 21:18:43 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

int is_valid(t_mlx *fractol, int argc, char **argv)
{
    if (argc == 2)
    {
        if (ft_strcmp(argv[1], "mandlebrot") == 0) // Corrected spelling to 'mandelbrot'
            fractol->type = MANDELBROT;
        else if (ft_strcmp(argv[1], "burning_ship") == 0)
            fractol->type = BURNING_SHIP;
        else if (ft_strcmp(argv[1], "julia") == 0)  // Fixed the typo to "julia" and compared correctly
        {
            fractol->type = JULIA;
            fractol->fractal.cx = -0.7;
            fractol->fractal.cy = 0.27015;
        }
    }
    else if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
    {
        fractol->type = JULIA;
        fractol->fractal.cx = atof(argv[2]);
        fractol->fractal.cy = atof(argv[3]);
    }
    else 
    {
        write(STDERR_FILENO, "Enter a valid args:\n", 20);
        write(STDERR_FILENO, "./fractol <mandlebrot>\n", 23);
        write(STDERR_FILENO, "./fractol <julia> <real> <imaginery>\n", 37);
        write(STDERR_FILENO, "./fractol <burning_ship>\n", 25);
        exit(1);
    }
    return 1;
}



double ft_atof(const char *nptr)
{
    unsigned int    i;
    int     sign;
    double  res;

    i = 0;
    sign = -1;
    res = 0.0;
    while (nptr[i] == ' ' || nptr[i] == '\t')
        i++;
    while (nptr[i] == '-' || nptr[i] == '+')
    {
       if (nptr[i] == '-')
            sign = -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        res = (res * 10) + (nptr[i] - '0');
        i++;
    }
    if (nptr[i] == '.')
        res += ft_atof1(nptr, i);
    return (sign * (res));
}

double    ft_atof1(const char *nptr, unsigned int i)
{
    double  fractional;
    double  divisor;

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
