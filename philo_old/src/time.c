/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:53:18 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 15:18:18 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Instead of using the terrible timeval struct,
// convert the seconds to microseconds, add them up, and store it in an
// unsigned 64 bit int.
// During the first call, before the philosophers run, set the start time.
// After that subtract the start time, from the current time, to get the 
// time elapsed since the start of the simulation.
t_ullong	my_gettime(void)
{
	struct timeval	newtime;
	static t_ullong	start_time = 0;

	gettimeofday(&newtime, NULL);
	if (start_time == 0)
	{
		start_time = newtime.tv_sec * 1000000 + newtime.tv_usec;
		return (start_time);
	}
	return ((newtime.tv_sec * 1000000 + newtime.tv_usec) - start_time);
}
