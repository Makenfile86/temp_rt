/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:41:16 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:53:16 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "stdio.h"

static double	return_max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}


static double calc_fresnel(t_vector normal, t_vector target, double ior)
{
	t_fresnel params;
	double tmp;

	params.etai = 1;
	params.etat = ior;
	params.cosi = vectordot(target, normal);
	if (params.cosi > 0)
	{
		tmp = params.etai;
		params.etai = params.etat;
		params.etat = tmp;
	} 
	params.sint = params.etai / params.etat *
		sqrtf(return_max(0.f, 1 - params.cosi * params.cosi));
	if (params.sint >= 1)
		params.kr = 1;
	else
	{
		params.cost = sqrtf(return_max(0.f, 1 - params.sint * params.sint));
		params.cosi = fabs(params.cosi);
		params.rs = ((params.etat * params.cosi) - (params.etai * params.cost))
			/ ((params.etat * params.cosi) + (params.etai * params.cost));
		params.rp = ((params.etai * params.cosi) - (params.etat * params.cost))
			/ ((params.etai * params.cosi) + (params.etat * params.cost));
		params.kr = (params.rs * params.rs + params.rp * params.rp) / 2;
	}
	return (params.kr);
}


static t_ray		reflection_direction(t_ray ray, t_vector n, t_data *data)
{
	t_vector	tmp;
	double		reflect;
	double		r_factor;

	if (data->hit.refract == 1)
	{
	//data->hit.org_start = vector_copy(ray.start);
		//data->hit.org_target = vector_copy(ray.target);

	//ft_putendl("moikka");
	ray.start = vector_copy(ray.newstart);
	double etai;
	double ior;
	double etat;
	double eta;
	double tmp;
	double cosi;
	double k;

	etai = 1;
	ior = 30;
	etat = ior;

	cosi = vectordot(ray.target, n);
	if (cosi < -1)
	cosi = -1;
	if (cosi > 1)
	cosi = 1;
	if (cosi < 0)
	cosi = cosi * -1;
	else
	{
		tmp = etai;
		etai = etat;
		etat = tmp;
		n.x = n.x * -1;
		n.y = n.y * -1;
		n.z = n.z * -1;
	}
	eta = etai / etat;
	k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
	ray.target = vectornew(0, 0, 0);
	else
	ray.target = vectoradd(vectorscale(eta, ray.target),
		vectorscale((eta * cosi - sqrtf(k)), n));
	
	//data->iter += 1;
	data->hit.refract = 0;
	data->hit.was_refract = 1;
	ray.target = normalized_vector(ray.target);
	data->hit.org_normal = normalized_vector(data->hit.org_normal);
	data->hit.fresnel = calc_fresnel(n, ray.target, ior);
	//printf("%f\n", data->hit.fresnel);
	}
	else
	{
	r_factor = fabs(data->scene->reflection - 9.5);

	ray.start = vector_copy(ray.newstart);
	reflect = r_factor * vectordot(ray.target, n);
	tmp = vectorscale(reflect, n);
	ray.target = vector_minus(ray.target, tmp);
	//if (data->hit.was_refract == 1)
	//data->hit.fresnel = calc_fresnel(ray.start, ray.target, 1.5);
	if (data->hit.was_refract == 1)
	data->hit.was_refract = 0;


	}
	return (ray);
}

static void			search_intersection(t_data *data, t_ray ray)
{
	int			i;
	
	data->objnbr = data->obj->num_polygonals;
	i = data->objnbr - 1;
	//i = data->obj->num_polygonals + data->objnbr - 1;
	data->hit.obj_idx = -1;
	data->hit.t = 1000.0;
	data->hit.find_shadow = 0;
	//int tmp;
	//tmp = data->obj->num_polygonals;
//data->objnbr = data->obj->num_polygonals;
	//ft_putnbr(data->obj->num_polygonals);
	//printf("%f x\n", data->obj->polygonals[0].normal.x);

		//printf("%f y\n", data->obj->polygonals[0].normal.y);

		//printf("%f z\n", data->obj->polygonals[0].normal.z);
	
	while (i >= 0)
	{
		
		if (data->cylinder->nbr > i && intersectcylinder(ray, data, i) == 1)
			set_hit(data, "cylinder", i);
		if (data->sphere->nbr > i && intersectsphere(ray, data, i) == 1)
			set_hit(data, "sphere", i);
		if (data->plane->nbr > i && intersectplane(data, i, ray) == 1)
			set_hit(data, "plane", i);
		if (data->cone->nbr > i && intersectcone(ray, data, i) == 1)
			set_hit(data, "cone", i);
		if ((int)data->obj->num_polygonals > i && intersecttriangle(ray, data, i) == 1)
			set_hit(data, "triangle", i);
		i--;
	}
	
}

static void copy_hit_data(t_data *data)
{
	int i;
	
	i = data->hit.obj_idx;
	
	if (ft_strcmp(data->hit.obj_name, "sphere") == 0)
	{
		data->hit.texture.type = data->sphere->texture[i].type;
	data->hit.texture.size = data->sphere->texture[i].size;
	data->hit.texture.color.red = data->sphere->texture[i].color.red;
	data->hit.texture.color.green = data->sphere->texture[i].color.green;
	data->hit.texture.color.blue = data->sphere->texture[i].color.blue;
	data->hit.mater = data->sphere->mater[i];
	}
		if (ft_strcmp(data->hit.obj_name, "plane") == 0)
	{
		data->hit.texture.type = data->plane->texture[i].type;
	data->hit.texture.size = data->plane->texture[i].size;
	data->hit.texture.color.red = data->plane->texture[i].color.red;
	data->hit.texture.color.green = data->plane->texture[i].color.green;
	data->hit.texture.color.blue = data->plane->texture[i].color.blue;
	data->hit.mater = data->plane->mater[i];

	}
	if (ft_strcmp(data->hit.obj_name, "cylinder") == 0)
	{
		data->hit.texture.type = data->cylinder->texture[i].type;
	data->hit.texture.size = data->cylinder->texture[i].size;
	data->hit.texture.color.red = data->cylinder->texture[i].color.red;
	data->hit.texture.color.green = data->cylinder->texture[i].color.green;
	data->hit.texture.color.blue = data->cylinder->texture[i].color.blue;
	data->hit.mater = data->cylinder->mater[i];
	}
	if (ft_strcmp(data->hit.obj_name, "cone") == 0)
	{
data->hit.mater = data->cone->mater[i];
	}
	if (ft_strcmp(data->hit.obj_name, "triangle") == 0)
	{
data->hit.mater = 1;
data->hit.texture.type = 0;
	}
		if (data->hit.mater == 3)
			data->hit.refract = 1;
			//if (data->hit.was_refract == 1)
			//data->hit.was_refract = 0;
		
}

static t_ray		new_hit_direction(t_data *data, t_ray org_ray, t_vector *n)
{
	double		temp;
	t_ray		ray;

	ray.newstart = vectornew(0, 0, 0);
	ray.start = vector_copy(org_ray.start);
	ray.target = vector_copy(org_ray.target);
	if (data->iter == data->org_iter && data->hit.was_refract != 1)
	{
		data->hit.org_start = vector_copy(ray.start);
		data->hit.org_target = vector_copy(ray.target);
		data->hit.org_normal = vector_copy(*n);
	}
	if (ft_strcmp(data->hit.obj_name, "cone") == 0)
		*n = new_start_dir_cone(data, &ray);
	if (ft_strcmp(data->hit.obj_name, "sphere") == 0)
	{
		
		*n = new_start_dir_sphere(data, &ray);
		temp = vectordot(*n, *n);
		if (temp == 0)
		{
			n->x = 101010;
			return (ray);
		}
		temp = 1.0f / sqrt(temp);
		*n = vectorscale(temp, *n);
		
	
		}
	if (ft_strcmp(data->hit.obj_name, "plane") == 0)
		*n = new_start_dir_plane(data, &ray);
	if (ft_strcmp(data->hit.obj_name, "cylinder") == 0)
		*n = new_start_dir_cylinder(data, &ray);
		if (ft_strcmp(data->hit.obj_name, "triangle") == 0)
		{
			*n = data->hit.normal;
			ray.newstart = data->hit.point;
		}
	copy_hit_data(data);
	return (ray);
}

static t_rgb		search_light_and_shadow(t_data *data, t_ray ray,
		t_vector n, t_rgb rgb)
{
	int			i;
	int 		idx;
	char		*name;

	name = data->hit.obj_name;
	idx = data->hit.obj_idx;
	ray.target = vector_copy(n);
	i = (data->spot->nbr - 1);
		if (data->hit.texture.type > 0)
		//{
		//if (data->hit.was_refract == 1)
		//texture_mapping(data, n, data->hit.preobj_name);
		//else
		texture_mapping(data, n, name);
		
	while (i >= 0)
	{
	if (data->iter == data->org_iter && data->scene->shadows > 0)
		{

			if (shadow(data, ray.newstart, i) != 1)
				rgb = get_light(data, rgb, ray, i);
		}
		else	
		rgb = get_light(data, rgb, ray, i);
		i--;
	}

	return (rgb);
}

void				get_color(t_data *data, int x, int y)
{
	t_vector	n;
	t_rgb		rgb;
	t_ray		ray;
	
	
	ray = init_pixel(data, x, y, &rgb);
	while (data->iter > 0 && data->light_scale > 0.0f)
	{
		//if (data->hit.was_refract == 1)
		//{
			//ray.start = vector_copy(data->hit.org_start);
			//ray.target = vector_copy(data->hit.org_target);
		//	ray.newstart = vector_copy(data->hit.pre_refract_ray->newstart);
			//data->hit.was_refract = 0;
		//}ft_strcmp(data->hit.preobj_name, "empty") == 0))
		search_intersection(data, ray);
		if (data->hit.obj_idx == -1)
			break ;
		ray = new_hit_direction(data, ray, &n);
		if (n.x == 101010)
			break ;
	if (data->hit.mater != 3 && data->hit.mater != 4)
		rgb = search_light_and_shadow(data, ray, n, rgb);
		if (data->hit.mater != 3 && data->hit.mater != 4)
		data->iter--;
		if ((ft_strcmp(data->hit.preobj_name, "empty") != 0) && data->hit.mater == 3 && data->hit.preobj_mater != 4)
		data->iter = 0;
		set_old_hit(data);
		ray = reflection_direction(ray, n, data);
		
		if (data->hit.was_refract != 1)
		put_color(data, rgb, x, y);
		//test++;
	}
	
}
