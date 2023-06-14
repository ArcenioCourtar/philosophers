/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/14 18:55:35 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*pt_philo(void *args)
{
	t_args	*input;
	t_data	*dat;
	int		philonum;

	input = args;
	dat = input->dat;
	philonum = input->i;
	free(args);
	while (1)
	{
		if (philonum == 0)
		{
			pthread_mutex_lock(&(dat->stick_mut[dat->num - 1]));
			pthread_mutex_lock(&(dat->stick_mut[philonum]));
		}
		else if (philonum == dat->num - 1)
		{
			pthread_mutex_lock(&(dat->stick_mut[philonum - 1]));
			pthread_mutex_lock(&(dat->stick_mut[0]));
		}
		else
		{
			pthread_mutex_lock(&(dat->stick_mut[philonum - 1]));
			pthread_mutex_lock(&(dat->stick_mut[philonum]));
		}
		printf("I");
		usleep(TIME_S);
		if (philonum == 0)
		{
			pthread_mutex_unlock(&(dat->stick_mut[dat->num - 1]));
			pthread_mutex_unlock(&(dat->stick_mut[philonum]));
		}
		else if (philonum == dat->num - 1)
		{
			pthread_mutex_unlock(&(dat->stick_mut[philonum - 1]));
			pthread_mutex_unlock(&(dat->stick_mut[0]));
		}
		else
		{
			pthread_mutex_unlock(&(dat->stick_mut[philonum - 1]));
			pthread_mutex_unlock(&(dat->stick_mut[philonum]));
		}
	}
	return (NULL);
}

// MUTEXES
bool	kill_time(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		pthread_mutex_lock(&(dat->time_meal_mut[i]));
		if (dat->time_cur - dat->time_meal[i] >= dat->ttd)
		{
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
		pthread_mutex_lock(&(dat->time_cur_mut));
		dat->time_cur = my_gettime();
		if (kill_time(dat))
		{
			printf("time elapsed in ms: %lu\n", (dat->time_cur - dat->time_st) / 1000);
			pthread_mutex_unlock(&(dat->time_cur_mut));
			break ;
		}
		pthread_mutex_unlock(&(dat->time_cur_mut));
	}
	return (NULL);
}

void	start_philo(t_data *dat)
{
	int		i;
	t_args	*args;

	i = 0;
	while (i < dat->num)
	{
		args = malloc(sizeof(t_args));
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
