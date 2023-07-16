/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_reaper.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:39 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/16 18:45:34 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_simulation(t_data *dat)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(dat->mut_ready));
	while (i < dat->num)
	{
		dat->time_eaten[i] = 0;
		i++;
	}
	dat->time_start = my_gettime();
	dat->ready = true;
	pthread_mutex_unlock(&(dat->mut_ready));
}

void	simulation_end(t_data *dat)
{
	pthread_mutex_lock(&(dat->mut_running[0]));
	dat->running = false;
	pthread_mutex_unlock(&(dat->mut_running[0]));
}

t_data	*init_reaper(t_tmp *args)
{
	t_data	*dat;

	dat = args->dat;
	free(args);
	return (dat);
}

void	check_eat_times(t_data *dat)
{
	int			i;
	u_int64_t	time_curr;

	while (1)
	{
		usleep(100);
		i = 0;
		while (i < dat->num)
		{
			time_curr = my_gettime();
			pthread_mutex_lock(&(dat->mut_eaten[i]));
			if (time_curr > (dat->time_eaten[i] + dat->ttd))
			{
				pthread_mutex_lock(&(dat->mut_print));
				simulation_end(dat);
				printf("\033[1;31m%llu %i has died.\n", \
				dat->time_eaten[i] + dat->ttd, i);
				pthread_mutex_unlock(&(dat->mut_print));
				pthread_mutex_unlock(&(dat->mut_eaten[i]));
				return ;
			}
			pthread_mutex_unlock(&(dat->mut_eaten[i]));
			i++;
		}
	}
}

void	*routine_reaper(void *args)
{
	t_data		*dat;

	dat = init_reaper(args);
	start_simulation(dat);
	check_eat_times(dat);
	return (NULL);
}
