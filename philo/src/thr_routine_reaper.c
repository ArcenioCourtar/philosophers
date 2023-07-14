/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_reaper.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:39 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 19:26:58 by acourtar      ########   odam.nl         */
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
		usleep(TIME_S);
		i = 0;
		time_curr = my_gettime();
		while (i < dat->num)
		{
			pthread_mutex_lock(&(dat->mut_eaten[i]));
			if (time_curr > (dat->time_eaten[i] + dat->ttd))
			{
				pthread_mutex_unlock(&(dat->mut_eaten[i]));
				return ;
			}
			pthread_mutex_unlock(&(dat->mut_eaten[i]));
			i++;
		}
	}
}

void	simulation_end(t_data *dat)
{
	mut_list_lock(dat->mut_running, dat->num);
	dat->running = false;
	mut_list_unlock(dat->mut_running, dat->num);
}

void	*routine_reaper(void *args)
{
	t_data		*dat;

	dat = init_reaper(args);
	start_simulation(dat);
	check_eat_times(dat);
	simulation_end(dat);
	printf("reaper thread ended\n");
	return (NULL);
}
