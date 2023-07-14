/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 16:05:04 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philo(t_tmp *args, t_me *me)
{
	bool	ready;

	ready = false;
	me->dat = args->dat;
	me->num = args->i;
	free(args);
}

void	wait_start(t_me *me)
{
	while (1)
	{
		pthread_mutex_lock(&(me->dat->mut_ready));
		if (me->dat->ready == true)
		{
			pthread_mutex_unlock(&(me->dat->mut_ready));
			break ;
		}
		pthread_mutex_unlock(&(me->dat->mut_ready));
	}
	me->time_cur = my_gettime();
}

void	*routine_philo(void *args)
{
	t_me	me;

	init_philo(args, &me);
	wait_start(&me);
	return (NULL);
}
