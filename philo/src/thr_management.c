/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_management.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:33:59 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 15:27:42 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Create all threads.
bool	create_threads(t_data *dat)
{
	t_tmp	*args;
	int		i;

	args = dat->args;
	i = 0;
	while (i < dat->num)
	{
		args[i].num = i;
		args[i].dat = dat;
		if \
		(pthread_create(&(dat->tid[i]), NULL, routine_philo, &(args[i])) != 0)
			return (false);
		i++;
		dat->count_thr++;
	}
	if \
	(pthread_create(&(dat->tid[dat->num]), NULL, routine_reap, &(args[0])) != 0)
		return (false);
	dat->count_thr++;
	return (true);
}

// philo threads need to check if the simulation is still running,
// if it's not, they terminate.
bool	check_simulation_status(t_data *dat)
{
	bool	status;

	pthread_mutex_lock(&(dat->mut_running));
	status = dat->running;
	pthread_mutex_unlock(&(dat->mut_running));
	return (status);
}

// Get current time and print it.
t_ullong	time_and_print(t_me *me, t_data *dat, const char *txt)
{
	t_ullong	time;

	pthread_mutex_lock(&(dat->mut_print));
	time = my_gettime();
	if (time >= me->time_eat + dat->ttd)
	{
		pthread_mutex_unlock(&(dat->mut_print));
		me->alive = false;
		return (0);
	}
	if (!check_simulation_status(dat))
	{
		pthread_mutex_unlock(&(dat->mut_print));
		me->alive = false;
		return (0);
	}
	printf("%llu %i %s", time / CONVERT, me->num + 1, txt);
	pthread_mutex_unlock(&(dat->mut_print));
	return (time);
}
