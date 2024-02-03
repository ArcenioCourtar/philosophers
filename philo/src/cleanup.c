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

static void	destroy_mutexes(t_data *dat)
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
	mut_list_destroy(dat, dat->mut_ready);
	mut_list_destroy(dat, dat->mut_time_eaten);
	mut_list_destroy(dat, dat->mut_fork);
	mut_list_destroy(dat, dat->mut_eat_num);
}

// in case an error occured during the creation of threads, the reaper
// will not be there to say "go".
// ensure the threads that are created actually finish their routine so
// they can be joined.
static void	join_threads(t_data *dat)
{
	int	i;

	if (dat->thr_error == true)
	{
		i = 0;
		while (i < dat->count_thr)
		{
			pthread_mutex_lock(&(dat->mut_ready[i]));
			i++;
		}
		dat->running = false;
		dat->ready = true;
		i = 0;
		while (i < dat->count_thr)
		{
			pthread_mutex_unlock(&(dat->mut_ready[i]));
			i++;
		}
	}
	i = 0;
	while (i < dat->count_thr)
	{
		pthread_join(dat->tid[i], NULL);
		i++;
	}
}

// join threads, destroy mutexes, and free memory wherever necessary
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
