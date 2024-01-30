/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_reaper.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:39 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 15:21:03 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Checks if all philo threads have initialized
bool	check_philo_thread_init(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		pthread_mutex_lock(&(dat->mut_time_eaten[i]));
		if (dat->time_eaten[i] == 1)
		{
			pthread_mutex_unlock(&(dat->mut_time_eaten[i]));
			return (false);
		}
		pthread_mutex_unlock(&(dat->mut_time_eaten[i]));
		i++;
	}
	return (true);
}

// Start simulation, when all philo threads are ready
void	start_simulation(t_data *dat)
{
	while (1)
	{
		if (check_philo_thread_init(dat))
			break ;
	}
	pthread_mutex_lock(&(dat->mut_running));
	dat->running = true;
	my_gettime();
	pthread_mutex_unlock(&(dat->mut_running));
}

// Function called if the simulation needs to end because a philo died or they
// ate enough.
void	simulation_end(t_data *dat)
{
	pthread_mutex_lock(&(dat->mut_running));
	dat->running = false;
	pthread_mutex_unlock(&(dat->mut_running));
}

t_data	*init_reaper(t_tmp *args)
{
	t_data	*dat;

	dat = args->dat;
	return (dat);
}

// Checks if any philos are supposed to be dead, every 100 microseconds.
void	*routine_reap(void *args)
{
	t_data		*dat;

	dat = init_reaper(args);
	start_simulation(dat);
	check_eat_times(dat);
	return (NULL);
}
