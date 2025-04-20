/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:54:22 by modat             #+#    #+#             */
/*   Updated: 2025/04/20 18:54:23 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// scaling a rage of numbers with a known max & min values.
/*
            800
  (0, 0) _ _ _ _ _ _ _ _ _ _ _ _   
        |                       |
    600 |                       |
        |                       |
        |                       |
        |                       |
        |_ _ _ _ _ _ _ _ _ _ _ _|

         _ _ _ _ _ _ _ _ _ _ _ _
        |                       |
        |                       |
        |        (0,0)          |
        |                       |
        |                       |
        |_ _ _ _ _ _ _ _ _ _ _ _|
*/
// linear interpolation
// double      mapping(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
// {
//     return (new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min)  + new_min;
// }
// void    pixel_handler(int x, int y, t_mlx *fractol)
// {
//     t_complex z;
//     t_complex c;

//     z.x_real = 0.0;
//     z.y_imaginery = 0.0;

//     // c.x = 



// }
