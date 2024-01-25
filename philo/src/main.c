/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 16:59:14 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:25:28 by acourtar      ########   odam.nl         */
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
	mut_list_destroy(dat, dat->mut_eaten, dat->num);
	mut_list_destroy(dat, dat->mut_fork, dat->num);
	mut_list_destroy(dat, dat->mut_eat_num, dat->num);
}

void	join_threads(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->count_thr)
	{
		pthread_join(dat->tid[i], NULL);
		i++;
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
	free(dat->mut_eaten);
	free(dat->mut_fork);
	free(dat->eat_num);
	free(dat->mut_eat_num);
	return (exit_code);
}

/*
	First I parse the input, if the input is invalid, return from main().
	If the input is valid, intialize the struct, if any errors occur while
	initializing, free any memory and return from main().
	Create the reaper thread and all philo threads, after which the simulation
	starts.
	Parent thread waits for all child threads to terminate.
	Free and return from main().
*/
int	main(int argc, char **argv)
{
	t_data	dat;

	if (!parse_input(argc, argv, &dat))
		return (0);
	init_struct(&dat);
	if (!init_struct_malloc(&dat))
		return (cleanup(&dat, 1));
	if (!init_struct_mut(&dat))
		return (cleanup(&dat, 1));
	if (!create_threads(&dat))
		return (cleanup(&dat, 1));
	return (cleanup(&dat, 0));
}
