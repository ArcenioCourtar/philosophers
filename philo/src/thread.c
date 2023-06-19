/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/19 17:52:30 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_philo(t_data *dat)
{
	int		i;
	t_tmp	*args;

	dat->time_st = my_gettime();
	dat->time_cur = dat->time_st;
	i = 0;
	while (i < dat->num)
	{
		dat->time_meal[i] = dat->time_st;
		i++;
	}
	i = 0;
	while (i < dat->num)
	{
		args = malloc(sizeof(t_tmp));
		if (!args)
			return ;
		args->dat = dat;
		args->i = i;
		pthread_create(&(dat->tid[i]), NULL, pt_philo, args);
		i++;
	}
}

void	start_babysitter(t_data *dat)
{
	pthread_create(&(dat->tid[dat->num]), NULL, pt_countdown, dat);
}
