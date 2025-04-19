/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:25:11 by modat             #+#    #+#             */
/*   Updated: 2025/04/19 11:11:50 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// double  mapping(double value, double min, double max, double screen_max)
// {
//     return (min + value * (max - min) / (screen_max - 1));
// }

/* set pixel to buffer image
 1. calculate pixel position. 
 int offset = (y * line_size) + (x * (bpp / 8));
 
 2. set color value for each pixel.
 buffer[offset] = blue;      // Blue (0-255)
buffer[offset + 1] = green; // Green (0-255)
buffer[offset + 2] = red;   // Red (0-255)
buffer[offset + 3] = 0x00; // Alpha (0x00 = fully opaque)
*/

// Function to map screen pixels to complex plane
void    pixel_to_complex(t_mlx *fractol, int x, int y, double real, double imginaery)
{
    t_complex c;

}