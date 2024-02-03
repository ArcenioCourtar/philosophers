/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo_1.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:30:03 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// pass the info inside of the temp struct to the philo,
static void	init_philo(t_tmp *args, t_me *me, t_data **dat)
{
	*dat = args->dat;
	me->num = args->num;
	me->held[0] = false;
	me->held[1] = false;
	me->time_eaten = 0;
	me->alive = true;
}

// Busy wait until the reaper thread has started and changes this flag.
static void	wait_start(t_data *dat, int num)
{
	pthread_mutex_lock(&(dat->mut_time_eaten[num]));
	dat->time_eaten[num] = 0;
	pthread_mutex_unlock(&(dat->mut_time_eaten[num]));
	while (1)
	{
		pthread_mutex_lock(&(dat->mut_running));
		if (dat->running != 0)
			break ;
		pthread_mutex_unlock(&(dat->mut_running));
		usleep(100);
	}
	pthread_mutex_unlock(&(dat->mut_running));
}

// philo routine.
// Initialize struct, wait for reaper thread to say go, perform simulation.
void	*routine_philo(void *args)
{
	t_me	me;
	t_data	*dat;

	init_philo(args, &me, &dat);
	wait_start(dat, me.num);
	philo_main(&me, dat);
	return (NULL);
}
