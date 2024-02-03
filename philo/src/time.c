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

/*
Instead of using the terrible timeval struct,
convert the seconds to microseconds, add them up, and store it in an
unsigned long long.
The reaper thread will call this function first, before any other threads
can. The other threads are locked behind a boolean which only changes
after the reaper thread is done with this.
During the first call the starting time is set by storing the return of
gettimeofday()
Each subsequent call will compare the difference between that first call and
the current one to return the current simulation time
*/
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
