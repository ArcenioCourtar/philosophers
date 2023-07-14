/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 20:06:15 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_main(t_me *me, t_data *dat);

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

bool	check_simulation_status(int num, t_data *dat)
{
	bool	status;

	pthread_mutex_lock(&(dat->mut_running[num]));
	status = dat->running;
	pthread_mutex_unlock(&(dat->mut_running[num]));
	return (status);
}

void	*routine_philo(void *args)
{
	t_me	me;
	t_data	*dat;

	init_philo(args, &me, &dat);
	wait_start(&me, dat);
	philo_main(&me, dat);
	return (NULL);
}
