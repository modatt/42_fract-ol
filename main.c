/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:24:43 by modat             #+#    #+#             */
/*   Updated: 2025/04/20 19:30:26 by modat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     main(int argc, char **argv)
{
    t_mlx   *fractol = NULL;
    if (mem_alloc(&fractol))
        return (1);

   if (is_valid(fractol, argc, argv))
   {
      init_mlxset(fractol);
      // render(fractol);
      mlx_hook(fractol->win, CLOSE, 0, close_win, fractol);
      mlx_hook(fractol->win, 2, 1, keypress_hook, fractol); 
      mlx_mouse_hook(fractol->win, mouse_hook, fractol);
      mlx_key_hook(fractol->win, arrow_keys, fractol);
      mlx_loop_hook(fractol->mlx, fractal_rendering, fractol);
      // fractal_rendering(fractol);
      printf("%d", fractol->type);
      mlx_loop(fractol->mlx);
   }
   // print_type(fractol);
   
   free(fractol);
   return (0);
    
}

int   fractal_rendering(t_mlx *fractol)
{
   if (fractol->type == MANDELBROT)
      mandelbrot(fractol);
   else if (fractol->type == JULIA)
      julia(fractol);
   else if (fractol->type == BURNING_SHIP)
      burning_ship(fractol);
   mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, fractol->win_x, fractol->win_y);
   return (0);
}
/*
int   render_fractal(t_mlx *fractol)
{
   iteration(fractol);
   mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, fractol->win_x, fractol->win_y);
   return (0);
}

int   iteration(t_mlx   *fractol)
{
   fractol->win_y = 0;
   while (fractol->win_y < HEIGHT)
   {
      fractol->win_x = 0;
      while (fractol->win_x < WIDTH)
      {
         if (fractol->type == MANDELBROT)
            mandlebrot(fractol);
         else if (fractol->type == JULIA)
            julia(fractol);
         else if (fractol->type == BURNING_SHIP)
            burning_ship(fractol);
         else 
            return (0);
         fractol->win_x++;
      }
      fractol->win_y++;
   }
   return (0);
}
   */

   void print_type(t_mlx *fractol)
   {
       switch (fractol->type)
       {
           case MANDELBROT:
               printf("Fractal Type: Mandelbrot\n");
               break;
           case JULIA:
               printf("Fractal Type: Julia\n");
               break;
           case BURNING_SHIP:
               printf("Fractal Type: Burning Ship\n");
               break;
           default:
               printf("Unknown Fractal Type\n");
               break;
       }
   }

   