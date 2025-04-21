#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <ctype.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
# define ESC_KEY 65307
# define CLOSE 17

# define ZOOM_FACTOR 1.1
# define PAN_FACTOR 0.1
# define MOVE_SPEED 0.1
# define MAX_ITER 200

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define PALETTE_SIZE 16

typedef struct s_fractal
{
    double      cx;
    double      cy;
    double      zx;
    double      zy;
	double		j_cx;
	double		j_cy;
}				t_fractal;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_palette_info
{
	int			color1;
	int			color2;
	double		frac;
}				t_palette_info;

typedef enum
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP
}				t_type;

typedef struct s_image
{
	void		*img;
	char		*buffer;
	int			bpp;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_mlx
{
	t_type		type;
	void		*mlx;
	void		*win;
	t_image		img;
	double		zoom;
	double		offset_x;
	double		offset_y;
	double		win_x;
	double		win_y;
	int			palette[PALETTE_SIZE];
	t_fractal	fractal;
}				t_mlx;

// setup::
void			init_mlxset(t_mlx *mlxset);
void			zoom_init(t_mlx *fractol);
int				mem_alloc(t_mlx **fractol);
char			*get_type_name(t_type type);

// events::
int				keypress_hook(int keycode, t_mlx *fractol);
int				close_win(t_mlx *fractol);
int				mouse_hook(int button, int x, int y, t_mlx *fractol);
int				arrow_keys(int keycode, t_mlx *fractol);

// rendering
int				fractal_rendering(t_mlx *fractol);
int				rgb(int r, int g, int b);
int				get_color(int iteration, double zx, double zy, t_mlx *fractol);
void			mandelbrot_math(int x, int y, t_mlx *fractol);
void			init_colors(t_mlx *fractol);
void			julia_math(int x, int y, t_mlx *fractol);
void			burning_ship_math(int x, int y, t_mlx *fractol);

void			clean_exit(t_mlx *mlxset);

// utils checking
int				ft_strcmp(const char *s1, const char *s2);
int				is_valid(t_mlx *fractol, int argc, char **argv);
void			julia_valid(t_mlx *fractol, char **argv);
int				is_julia_valid(char *str);
void			error_mess(t_mlx *mlxset);
double			ft_atof(const char *nptr);
double			ft_atof1(const char *nptr, unsigned int i);

#endif