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
t_ullong	my_gettime(t_data *dat)
{
	struct timeval	newtime;

	gettimeofday(&newtime, NULL);
	if (dat->start_time == 0)
	{
		dat->start_time = newtime.tv_sec * 1000000 + newtime.tv_usec;
		return (dat->start_time);
	}
	return ((newtime.tv_sec * 1000000 + newtime.tv_usec) - dat->start_time);
}
