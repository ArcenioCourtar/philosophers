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

// free stuff xd
int	free_ret(t_data *dat)
{
	// destroy mutexes
	// join threads
	free(dat->tid);
	free(dat->time_eaten);
	free(dat->forks);
	free(dat->args);
	free(dat->mut_eaten);
	free(dat->mut_fork);
	free(dat->eat_num);
	free(dat->mut_eat_num);
	return (0);
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
		return (free_ret(&dat));
	if (!init_struct_mut(&dat))
		return (free_ret(&dat));
	if (!create_threads(&dat))
		return (free_ret(&dat));
	join_threads(&dat);
	return (free_ret(&dat));
}
