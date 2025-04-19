/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:24:58 by modat             #+#    #+#             */
/*   Updated: 2025/04/19 11:10:46 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void *param passed to use it to pass additional info to it.

int     close_win(t_mlx *fractol)
{
    mlx_destroy_window(fractol->mlx, fractol->win);
    exit(0);
    return (0);
}

int     keypress_hook(int keycode, t_mlx *fractol)
{
    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(fractol->mlx, fractol->win);
        exit(0);
    }
    return (0);
}

int mouse_hook(int button, int x, int y, t_mlx *fractol)
{
    // Get mouse position in the complex plane BEFORE zoom
    double mouse_real = (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH)) + fractol->offset_x;
    double mouse_imag = (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT)) + fractol->offset_y;

    if (button == 4) // Scroll up = zoom in
        fractol->zoom *= ZOOM_FACTOR;
    else if (button == 5) // Scroll down = zoom out
        fractol->zoom /= ZOOM_FACTOR;
    else
        return (0); // Ignore other mouse events

    // Adjust offsets to keep mouse centered after zoom
    fractol->offset_x = mouse_real - (x - WIDTH / 2.0) * (4.0 / (fractol->zoom * WIDTH));
    fractol->offset_y = mouse_imag - (y - HEIGHT / 2.0) * (4.0 / (fractol->zoom * HEIGHT));

    // Redraw the fractal
    // render_fractal(fractol);

    return (0);
}

int arrow_keys(int keycode, t_mlx *fractol)
{
    if (keycode == 126) // Up arrow
        fractol->offset_y -= PAN_FACTOR / fractol->zoom;
    else if (keycode == 125) // Down arrow
        fractol->offset_y += PAN_FACTOR / fractol->zoom;
    else if (keycode == 123) // Left arrow
        fractol->offset_x -= PAN_FACTOR / fractol->zoom;
    else if (keycode == 124) // Right arrow
        fractol->offset_x += PAN_FACTOR / fractol->zoom;

    // render_fractol(fractol); // Redraw the fractal with new offsets
    return (0);
}

/*
⬆️ You move "up" by decreasing the imaginary part of the center.
You divide by zoom so that movement becomes smaller when zoomed in (more precise control at close zoom).
⬇️ You move "down" (imaginary increases).
⬅️ Move left: reduce the real part.
➡️ Move right: increase the real part.

Complex Plane View (zoomed in)
--------------------------------
         ^ ↑
       ← | →    ← arrow keys move view
         ↓ v

offset_x/y changes = move view
zoom stays the same

*/