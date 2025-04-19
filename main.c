/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modat <modat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:24:43 by modat             #+#    #+#             */
/*   Updated: 2025/04/19 10:52:11 by modat            ###   ########.fr       */
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
      //   mlx_key_hook(fractol->win, keypress_hook, &fractol);
      mlx_hook(fractol->win, 2, 1, keypress_hook, fractol); 
      mlx_mouse_hook(fractol->win, mouse_hook, fractol);
      mlx_key_hook(fractol->win, arrow_keys, fractol);
      mlx_loop(fractol->mlx);
   }
   // Draw
   
   free(fractol);
   return (0);
    
}
