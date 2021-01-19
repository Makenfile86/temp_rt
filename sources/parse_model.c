#include "rtv1.h"
#include "stdio.h"


 t_obj    *read_obj(t_obj *obj)
{
    int     fd;

    int     i;
 char    *filename;
    int     width;
    int     height;
    char *line;
 

    height = 1000;
    width = 1000;

i = 0;
    filename = "cat.obj";
fd = open(filename, O_RDONLY);

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "v ", 2) == 0)
			obj->num_geometry++;
        else if (ft_strncmp(line, "vt", 2) == 0)
			obj->num_coordinates++;
		else if (ft_strncmp(line, "vn", 2) == 0)
			obj->num_normals++;
		else if (ft_strncmp(line, "f ", 2) == 0)
			obj->num_polygonals++;
		free(line);

	}
        printf("%zu\n", obj->num_geometry);

        printf("%zu\n", obj->num_coordinates);

        printf("%zu\n", obj->num_normals);

        printf("%zu\n", obj->num_polygonals);
	close(fd);
malloc_obj(obj, obj->num_geometry, obj->num_coordinates);
malloc_obj2(obj, obj->num_normals, obj->num_polygonals);
return (obj);
}

static void	parse_poly(t_obj *obj, size_t i, char *line)
{
	char	**parts;
	char	**tf;
	size_t	n;
	size_t j;

	j = 0;
ft_putendl("poo");
	parts = ft_strsplit(line + 1, ' ');
	while (parts[j] && (tf = ft_strsplit(parts[j], '/')))
	{
		if (!tf[0] || (n = ft_atoi(tf[0])))	
		obj->polygonals[i].ve[j] = obj->geometry[n - 1];
		if (!tf[1] || (n = ft_atoi(tf[1])))
		obj->polygonals[i].uv[j] = obj->coordinates[n - 1];
		if (!tf[2] || (n = ft_atoi(tf[2])))
		obj->polygonals[i].no[j] = obj->normals[n - 1];
		//free_null(5, tf[0], tf[1], tf[2], tf, parts[j]);
		j++;
	printf("%zu	\nj", j);
	}
	ft_putendl("poo2");
	//free(parts);
		printf("%f x\n", obj->polygonals[2].ve[1].x);

		printf("%f y\n", obj->polygonals[2].ve[1].y);

		printf("%f z\n", obj->polygonals[2].ve[1].z);
}

void	malloc_obj(t_obj *obj, size_t num_geometry, size_t num_coordinates)
{
	obj->geometry = (t_vector*)malloc(sizeof(t_vector) * num_geometry);
	obj->coordinates = (t_vec2*)malloc(sizeof(t_vec2) * num_coordinates);
}
void	malloc_obj2(t_obj *obj, size_t num_normals, size_t num_polygonals)
{
	obj->normals = (t_vector*)malloc(sizeof(t_vector) * num_normals);
	obj->polygonals = (t_vertices*)malloc(sizeof(t_vertices) * num_polygonals);
}

void		read_obj_data(int fd, t_obj *obj)
{
	char	*line;
	size_t	i[4];
	

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strncmp(line, "v ", 2) == 0)
			obj->geometry[i[0]++] = parse_geo(line + 1);
		if (ft_strncmp(line, "vt ", 2) == 0)
			obj->coordinates[i[1]++] = parse_coord(line + 1);
	if (ft_strncmp(line, "vn ", 2) == 0)
			obj->normals[i[2]++] = parse_normals(line + 2);
	if (ft_strncmp(line, "f ", 2) == 0)
			parse_poly(obj, i[3]++, line);
		
		
	}
	//printf("%f\n", obj->geometry[1].z);
//printf("%f\n", obj->coordinates[1].y);

ft_putendl("jee2");
}



t_vector	parse_normals(char *line)
{
	t_vector	vector;
	char tmp[10];
	char tmp2[10];
	char tmp3[15];
	int	i;
	int k;

k = 0;
	i = 1;


		while (line[i] != ' ')
		{
		tmp[k] = line[i];
			i++;
			k++;
		}
		i++;
		k = 0;
		while (line[i] != ' ')
		{
			tmp2[k] = line[i];
			i++;
			k++;
		}
		i++;
		k = 0;
		while (line[i] != '\0')
		{
			tmp3[k] = line[i];
			i++;
			k++;
		}
	
	vector.x = atof(tmp);
	vector.y = atof(tmp2);
	vector.z = atof(tmp3);
//printf("%f\n", vector.z);
	//printf("%s\n", line);
	return (vector);

}

t_vec2	parse_coord(char *line)
{
	t_vec2	vector;
	char tmp[10];
	char tmp2[10];
	int	i;
	int k;

	k = 0;
	i = 1;
	while (line[i] != ' ')
		{
			tmp[k] = line[i];
			i++;
			k++;
		}
		i++;
		k = 0;
		while (line[i] != '\0')
		{
			tmp2[k] = line[i];
			i++;
			k++;
		}
		
	
	
	vector.u = atof(tmp2);
	vector.v = atof(tmp);
	//printf("%f\n", vector.y);
	return (vector);



}

t_vector	parse_geo(char *line)
{
	t_vector	vector;
	char tmp[10];
	char tmp2[10];
	char tmp3[15];
	int	i;
	int k;

k = 0;
	i = 1;


		while (line[i] != ' ')
		{
		tmp[k] = line[i];
			i++;
			k++;
		}
		i++;
		k = 0;
		while (line[i] != ' ')
		{
			tmp2[k] = line[i];
			i++;
			k++;
		}
		i++;
		k = 0;
		while (line[i] != '\0')
		{
			tmp3[k] = line[i];
			i++;
			k++;
		}
	
	
	vector.x = atof(tmp);
	vector.y = atof(tmp2);
	vector.z = atof(tmp3);
	return (vector);

}

t_obj    *create_obj_data(void)
{
    	t_obj *obj;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
	{
        		return (0);
	}
	obj->num_geometry = 0;
//	m->vertices = NULL;

	return (obj);
}


int     init_obj(void)
{

   t_obj *obj;
   int fd;
char *filename;
       filename = "cat.obj";

   
obj = create_obj_data();
	
ft_putendl("jee3");

    obj = read_obj(obj);
	ft_putendl("jee4");

fd = open(filename, O_RDONLY);
ft_putendl("jee5");

		read_obj_data(fd, obj);
		ft_putendl("jee6");

	close(fd);
	ft_putendl("jee7");

    
    return (0);

}
