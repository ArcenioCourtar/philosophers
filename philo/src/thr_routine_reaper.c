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

// start simulation, all philo threads wait before this section is executed.
// set all time_eaten values to 0 (start of the simulation).
void	start_simulation(t_data *dat)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(dat->mut_running));
	while (i < dat->num)
	{
		dat->time_eaten[i] = 0;
		i++;
	}
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
void	*routine_reaper(void *args)
{
	t_data		*dat;

	dat = init_reaper(args);
	start_simulation(dat);
	check_eat_times(dat);
	return (NULL);
}
