/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   madnlebrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:25:05 by modat             #+#    #+#             */
/*   Updated: 2025/04/19 00:07:57 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// f(Z) = z^2 + c
// c = (x_real, y_i) these are the inputs (fixed) for mandlebrot

// void    mandlebrot(t_mlx *fractol)
// {
//     int y;
//     int x;
    
//     y = 0;
//     while (y++ < HEIGHT)
//     {
//         x = 0;
//         while (x++ < WIDTH)
//         {
//             // 1. Map pixel (x, y) to complex plane (real, imag)
//             // assign complex numbers for mand
//             // fractol->complex.x_real = ((x - WIDTH/2.0) * (4.0 / (fractol->zoom * WIDTH)) + fractol->offset_x);
//             // fractol->complex.y_imaginery = ((y - HEIGHT/2.0) * (4.0 / (fractol->zoom * HEIGHT)) + fractol->offset_x);
//             // iteration for mandlebrot
            
            
//         // 2. Run Mandelbrot logic on that point
        
//         // put_pixel_to_image()
        
//         // 3. Choose color and draw pixel
//         }       
//     }
// }