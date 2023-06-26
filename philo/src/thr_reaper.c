/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thr_reaper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:48:12 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/20 12:30:46 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// MUTEXES
static bool	kill_time(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		pthread_mutex_lock(&(dat->time_meal_mut[i]));
		dat->time_cur = my_gettime();
		if (dat->time_cur - dat->time_meal[i] >= dat->ttd)
		{
			printf("%llu %i died\n", (dat->time_meal[i] + dat->ttd - dat->time_st) / 1000, i);
			printf("ACTUAL time elapsed: %llu\n", (dat->time_cur - dat->time_st) / 1000);
			pthread_mutex_unlock(&(dat->time_meal_mut[i]));
			return (true);
		}
		pthread_mutex_unlock(&(dat->time_meal_mut[i]));
		i++;
	}
	return (false);
}

void	*pt_countdown(void *args)
{
	t_data	*dat;

	dat = args;
	while (1)
	{
		usleep(TIME_S);
		pthread_mutex_lock(&(dat->time_cur_mut));
		if (kill_time(dat))
		{	
			pthread_mutex_unlock(&(dat->time_cur_mut));
			break ;
		}
		pthread_mutex_unlock(&(dat->time_cur_mut));
	}
	return (NULL);
}
