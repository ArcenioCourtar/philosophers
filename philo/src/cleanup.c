/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/03 14:02:56 by acourtar      #+#    #+#                 */
/*   Updated: 2024/02/03 14:02:56 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ret_msg(const char *str, bool ret)
{
	printf("%s\n", str);
	return (ret);
}

void	destroy_mutexes(t_data *dat)
{
	if (dat->count_mut > 0)
	{
		pthread_mutex_destroy(&(dat->mut_running));
		dat->count_mut--;
	}
	if (dat->count_mut > 0)
	{
		pthread_mutex_destroy(&(dat->mut_print));
		dat->count_mut--;
	}
	mut_list_destroy(dat, dat->mut_ready, dat->num);
	mut_list_destroy(dat, dat->mut_time_eaten, dat->num);
	mut_list_destroy(dat, dat->mut_fork, dat->num);
	mut_list_destroy(dat, dat->mut_eat_num, dat->num);
}

void	join_threads(t_data *dat)
{
	int	i;

	i = dat->count_thr - 1;
	while (i >= 0)
	{
		pthread_join(dat->tid[i], NULL);
		i--;
	}
}

// free stuff xd
int	cleanup(t_data *dat, int exit_code)
{
	join_threads(dat);
	destroy_mutexes(dat);
	free(dat->tid);
	free(dat->time_eaten);
	free(dat->forks);
	free(dat->args);
	free(dat->mut_time_eaten);
	free(dat->mut_fork);
	free(dat->eat_num);
	free(dat->mut_eat_num);
	free(dat->mut_ready);
	return (exit_code);
}