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
int	free_ret(void)
{
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
	if (!init_struct(&dat))
		return (free_ret());
	if (!create_threads(&dat))
		return (free_ret());
	join_threads(&dat);
	return (free_ret());
}
