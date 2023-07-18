/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:30:03 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_main(t_me *me, t_data *dat);

// pass the info inside of the temp struct to the philo,
// free memory reserved for the temp struct.
void	init_philo(t_tmp *args, t_me *me, t_data **dat)
{
	bool	ready;

	ready = false;
	*dat = args->dat;
	me->num = args->num;
	me->held[0] = false;
	me->held[1] = false;
	me->time_eat = 0;
	me->time_cur = 0;
	free(args);
}

// Busy wait until the reaper thread has started and changes this flag.
void	wait_start(t_me *me, t_data *dat)
{
	while (1)
	{
		pthread_mutex_lock(&(dat->mut_ready));
		if (dat->ready == true)
		{
			pthread_mutex_unlock(&(dat->mut_ready));
			break ;
		}
		pthread_mutex_unlock(&(dat->mut_ready));
	}
	me->time_cur = my_gettime();
}

// philo routine.
// initialize struct, wait for reaper thread to say go, perform simulation.
void	*routine_philo(void *args)
{
	t_me	me;
	t_data	*dat;

	init_philo(args, &me, &dat);
	wait_start(&me, dat);
	philo_main(&me, dat);
	return (NULL);
}
