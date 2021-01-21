#include "rtv1.h"

    void		copy_model_data(t_data *data, char *str, int x, int e)
{
	
    if (x == 0)
    {
        data->model->name[e] = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
    ft_strcpy(&data->model->name[e][x], str);
    }
    else if (x == 1)
		data->model->xyz[e].x = ft_atoi(str);
	else if (x == 2)
	data->model->xyz[e].y = ft_atoi(str);
	else if (x == 3)
		data->model->xyz[e].z = ft_atoi(str);
	else if (x == 4)
		data->model->rgb2[e].red = ft_atoi(str);
	else if (x == 5)
		data->model->rgb2[e].green = ft_atoi(str);
	else if (x == 6)
		data->model->rgb2[e].blue = ft_atoi(str);
	else if (x == 7)
		data->model->rot[e].x = ft_atoi(str);
	else if (x == 8)
		data->model->rot[e].y = ft_atoi(str);
	else if (x == 9)
		data->model->rot[e].z = ft_atoi(str);
	else if (x == 10)
		data->model->mater[e] = ft_atoi(str);
        else
        data->model->size[e] = ft_atoi(str);
        
}
