/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_reaper.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 16:02:39 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 16:03:32 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine_reaper(void *args)
{
	t_tmp		*tmp;
	t_data		*dat;
	u_int64_t	time_cur;

	tmp = args;
	dat = tmp->dat;
	free(args);
	pthread_mutex_lock(&(dat->mut_ready));
	dat->time_start = my_gettime();
	dat->debug_time[0] = dat->time_start; dat->debug_time[1] = dat->time_start; dat->debug_num = -1;
	dat->ready = true;
	pthread_mutex_unlock(&(dat->mut_ready));
	return (NULL);
}
