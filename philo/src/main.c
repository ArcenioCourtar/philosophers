/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 16:59:14 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/11 16:30:20 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ret_msg(const char *str, bool ret)
{
	printf("%s\n", str);
	return (ret);
}

/*
	args: phil_num, death_time, eat_time, sleep_time, (eat_max_amount).
	State changes should be displayed with a message as follows:
	[timestamp] [philo num] [action]
	NEED TO STOP EACH THREAD BEFORE TERMINATION TO STOP SANITIZER FROM CRYING
*/
int	main(int argc, char **argv)
{
	t_data	dat;

	if (!parse_input(argc, argv, &dat))
		return (0);
	init_struct(&dat);
	debug_dat_cont(&dat);
	create_threads(&dat);
	join_threads(&dat);
	printf("time between start and last philo %i: %llu", dat.debug_num, dat.debug_time[1] - dat.debug_time[0]);
	return (0);
}
