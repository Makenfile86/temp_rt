#ifndef MODEL_H
# define MODEL_H

# include "vectors.h"
# include "rtv1.h"
# include "../libft/libft.h"



typedef struct	s_vertices
{
	t_vector		ve[3];
	t_vector		te[3];
	t_vector		no[3];
    t_vector		normal;
	t_vec2		uv[3];
//	t_bounds	bounds;
}				t_vertices;

typedef struct	s_obj
{
	size_t		num_geometry;
    t_vector    *geometry;
    size_t      num_coordinates;
    t_vec2      *coordinates;
    size_t      num_normals;
    t_vector    *normals;
    size_t      num_polygonals;
    t_vertices  *polygonals;
  

}				t_obj;

typedef struct	s_model
{
	char        *name[5];
    t_rgb2      rgb2[5];
    t_vector    xyz[5];
    t_vector    rot[5];
    double      mater[5];
    double       size[5];
    int         nbr;
  

}				t_model;


t_obj			*create_obj_data(void);
void	malloc_obj(t_obj *obj, size_t num_geometry, size_t num_coordinates);
void	malloc_obj2(t_obj *obj, size_t num_normals, size_t num_polygonals);
t_vector	parse_geo(char *line);
t_vec2	parse_coord(char *line);
t_vector	parse_normals(char *line);

#endif