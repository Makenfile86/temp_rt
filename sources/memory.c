/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:22:29 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/01 10:24:18 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "rtv1.h"

t_data	*allocate_memory(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!(data->sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		memory_allocation_fail();
	if (!(data->cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))))
		memory_allocation_fail();
	if (!(data->spot = (t_spot *)malloc(sizeof(t_spot))))
		memory_allocation_fail();
	if (!(data->cone = (t_cone *)malloc(sizeof(t_cone))))
		memory_allocation_fail();
	if (!(data->plane = (t_plane *)malloc(sizeof(t_plane))))
		memory_allocation_fail();
	if (!(data->camera = (t_camera *)malloc(sizeof(t_camera))))
		memory_allocation_fail();
		if (!(data->texture = (t_texturemap *)malloc(sizeof(t_texturemap))))
		memory_allocation_fail();
			if (!(data->scene = (t_scene *)malloc(sizeof(t_scene))))
		memory_allocation_fail();
		if (!(data->model = (t_model *)malloc(sizeof(t_model))))
		memory_allocation_fail();
			if (!(data->obj = (t_obj *)malloc(sizeof(t_obj))))
			memory_allocation_fail();
		data->obj->num_geometry = 0;
	data->obj->geometry = NULL;
	data->obj->num_coordinates = 0;
	data->obj->coordinates = NULL;
	data->obj->num_normals = 0;
	data->obj->normals = NULL;
	data->obj->num_polygonals = 0;
	data->obj->polygonals = NULL;
	//data->obj->bounds.min = ft_make_vec3(MAX_BOUNDS, MAX_BOUNDS, MAX_BOUNDS);
	//data->obj->bounds.max = ft_make_vec3(MIN_BOUNDS, MIN_BOUNDS, MIN_BOUNDS);

	return (data);
}

void	free_memory(t_data *data)
{
	
	free(data->cylinder);
	free(data->cone);
	free(data->plane);
	free(data->camera);
	free(data->spot);
	free(data->sphere);
	free(data->texture);
	free(data->model);
	free(data);
}
