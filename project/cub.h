/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <ykisibek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:09:04 by ykisibek          #+#    #+#             */
/*   Updated: 2025/05/24 14:09:04 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "math.h"
# include "stdio.h"
# include "stdlib.h"
# include "fcntl.h"
# include "unistd.h"
# include "sys/types.h"
# include "sys/stat.h"
# include "minilibx-linux/mlx.h"

# define SCREEN_WIDTH 640
# define SCREEN_HIGHT 480
# define WHITE_SPACE	" \t\v\f\r"
# define FOV 0.66

//for textures
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define TEX_NUM 4

//for gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef enum e_keyword
{
	W = 119,
	S = 115,
	D = 100,
	A = 97,
	ESC = 65307,
	LEFT_ARR = 65361,
	RIGHT_SRR = 65363,
	UP_ARR = 65362,
	DOWN_ARR = 65364,
}	t_keyword;

typedef enum e_path
{
	NO,
	SO,
	WE,
	EA,
	C,
	F,
}	t_path;

typedef struct s_player
{
	double			player_x; //player column
	double			player_y; //player row
	double			dir_x; //direction vector x
	double			dir_y; //direction vector y
	double			plane_x; //camera plane x
	double			plane_y; //camera plane y
	double			mov_speed; //moving speed
	double			rot_speed; //rotation speed
}	t_player;

typedef struct s_map
{
	int				map_h; //map height
	int				fd; //.cub file descriptor
	char			**map; //the game map
	char			*info; //temp for the path and color info
	char			*no; //NO path
	char			*so; //SO path
	char			*we; //WE path
	char			*ea; //EA path
	char			*c_col; //ceiling color
	char			*f_col; //floor color
	int				col_c;
	int				col_f;
}	t_map;

typedef struct s_ray_info
{
	double			time;
	double			old_time;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
}	t_ray_info;

typedef struct s_wall
{
	int				tex_num;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	int				line_height;
}	t_wall;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	int				color;
	int				height;
	int				width;
	int				line_height;
	int				draw_start;
	int				draw_end;
}	t_texture;

typedef struct cub
{
	t_map			*map;
	t_player		*player;
	t_ray_info		*rays;
	t_wall			*wall;
	t_texture		**texture;
	t_texture		*img;
	void			*mlx;
	void			*mlx_win;
	char			*file_name; //.cub file (argv[1])
}	t_cub;

//add_funcs
int					ft_strlen(char *str);
char				*ft_strdup(char *str);
int					ft_strncmp(char *str1, char *str2, int n);
char				*nolength(char const *str);
int					ft_strlcpy(char *dest, char *src, int size);

//add_funcs1
char				*ft_strtrim(char *s1, char *set);
int					ft_count(char *str, char letter);
char				*ft_fill_words(char *s, char c);
char				**ft_split(char *s, char c);
int					ft_atoi(const char *str);

//cub
int					main(int argc, char **argv);

//free_memory
void				exit_error(char *str);
void				free_player(t_player *player);
void				free_arr(char **map);
void				free_and_exit(t_cub *cub, char *str);

//free_memory1
void				free_map1(t_map *map);
void				free_map(t_map *map);
void				free_rays(t_ray_info *rays);
void				free_wall(t_wall *wall);
void				free_cub(t_cub *cub);

//free_memory2
void				free_texture(t_texture **texture);

//get_next_line_utils
int					gnl_strlen(char *str);
char				*ft_strchr(char *str, int c);
void				free_line(char *str);
char				*ft_strjoin(char *s1, char *s2);

//get_next_line
char				*fill_line(char *line, int fd);
int					count_nl(char *line);
char				*free_from_nl(char *line);
char				*copy_with_nl(char *line);
char				*get_next_line(int fd);

//init
void				init_texture(t_cub *cub);
void				init_cub_map(t_cub *cub, int fd);
void				init_cub_rays(t_cub *cub);
void				get_info(t_cub *cub, int argc, char **argv);
void				init_plane(t_cub *cub);

//init1
void				define_dir(t_cub *cub, int row, int col);
void				add_line(t_cub *cub, int hight, int i);
void				add_line_to_map(t_cub *cub);

//raycasting_tex
int					check_tex(char *name);
void				generate_textures(t_cub *cub);
void				getting_delta_vals(t_cub *cub);
void				perform_dda(t_cub *cub);
void				calculate_height(t_cub *cub);

//raycasting1
void				rotate_right(t_cub *cub);
int					cub_keys(t_keyword key, t_cub *cub);
void				rays(t_cub *cub);
void				raycasting(t_cub *cub);

//raycasting2
void				fill(t_cub *cub, int y, int map_col);
void				get_color(t_cub *cub);
void				move_up_down(t_map *map, t_player *pl, int c);
void				move_left_right(t_map *map, t_player *pl, int c);
void				rotate_left(t_cub *cub);

//raycasting3
void				get_img_info(t_cub *cub, int x);
void				init_ray_values(t_cub *cub, int x);
void				calc_ray_distances(t_cub *cub);
void				start_rays(t_cub *cub);
void				checking_gen_tex(t_cub *cub);

//raycasting4
void				set_texture_number(t_cub *cub);
void				calculate_wall_x(t_cub *cub);
void				calculate_tex_x(t_cub *cub);
void				get_tex_x(t_cub *cub);
int					exit_cub(t_cub *cub);

//validate
void				check_the_map(t_cub *cub);
void				trim_trailing_empty_lines(t_cub *cub);
void				get_map_data(t_cub *cub);
void				validate_paths(t_cub *cub);
void				validate(t_cub *cub);

//validate1
void				check_up_down_borders(t_cub *cub);
void				check_the_end(t_cub *cub, int row, int col);
void				check_side_borders(t_cub *cub);
void				check_neighbors(t_cub *cub, int row, int col);
void				check_space_borders(t_cub *cub);

//validate2
int					get_colors(t_cub *cub, char *info, t_path path);
int					get_path1(t_cub *cub, char *info, t_path path);
int					get_path(t_cub *cub, char *info, t_path path);
int					get_path_info(t_cub *cub, char *info);

//validate3
int					is_white(char element);
int					is_empty_str(char *str);
int					is_valid_symbol(char c);
int					is_dir(char c);
void				trim_the_nl(t_cub *cub);

//validate4
void				set_texture_path(t_cub *cub, char *temp, t_path p);
void				validate_paths_1(t_cub *cub, char *path, t_path p);
int					count_parts(char **temp);
void				validate_color(t_cub *cub, char *col, char c);

//validate5
void				check_map_row(t_cub *cub, int row, int *p_dir_count);
void				check_for_symbols(t_cub *cub);
void				check_name(t_cub *cub);

#endif