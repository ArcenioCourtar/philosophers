/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 14:53:18 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 17:31:02 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

u_int64_t	my_gettime(void)
{
	struct timeval		newtime;
	static u_int64_t	start_time = 0;

	gettimeofday(&newtime, NULL);
	if (start_time == 0)
	{
		start_time = newtime.tv_sec * 1000000 + newtime.tv_usec;
		return (start_time);
	}
	return ((newtime.tv_sec * 1000000 + newtime.tv_usec) - start_time);
}
