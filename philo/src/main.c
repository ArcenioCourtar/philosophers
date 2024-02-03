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

/*
	First I parse the input, if the input is invalid, return from main().
	If the input is valid, allocate memory, intialize mutexes and
	threads. If anything goes wrong, free/destroy/join where needed.
	If all goes well, parent thread waits for all child threads to finish.
	Cleanup and return from main().
*/
int	main(int argc, char **argv)
{
	t_data	dat;

	if (!parse_input(argc, argv, &dat))
		return (0);
	init_struct(&dat);
	if (!init_struct_malloc(&dat))
		return (cleanup(&dat, 1));
	init_after_malloc(&dat);
	if (!init_struct_mut(&dat))
		return (cleanup(&dat, 1));
	if (!create_threads(&dat))
	{
		dat.thr_error = true;
		return (cleanup(&dat, 1));
	}
	return (cleanup(&dat, 0));
}
