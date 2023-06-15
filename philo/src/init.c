/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:17:25 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/15 15:48:08 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_mutex_list(t_mutex *list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&list[i], NULL) != 0)
			printf("yo what happen\n");
		i++;
	}
}

// add proper error handling
void	init_struct(t_data *dat)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(dat->time_cur_mut), NULL);
	dat->tid = malloc(sizeof(pthread_t) * (dat->num + 1));
	if (!dat->tid)
		return ;
	dat->time_meal = malloc(sizeof(u_int64_t) * dat->num);
	if (!dat->time_meal)
		return ;
	dat->time_meal_mut = malloc(sizeof(t_mutex) * dat->num);
	if (!dat->time_meal_mut)
		return ;
	init_mutex_list(dat->time_meal_mut, dat->num);
	dat->stick = malloc(sizeof(bool) * dat->num);
	if (!dat->stick)
		return ;
	while (i < dat->num)
	{
		dat->stick[i] = true;
		i++;
	}
	dat->stick_mut = malloc(sizeof(t_mutex) * dat->num);
	if (!dat->stick_mut)
		return ;
	init_mutex_list(dat->stick_mut, dat->num);
	pthread_mutex_init(&(dat->ready), NULL);
}
