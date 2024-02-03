/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 19:36:47 by acourtar      #+#    #+#                 */
/*   Updated: 2024/01/30 19:36:47 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Sets up the correct values for the forks.
// philos track if they've held the fork last and will not pick it up
// if that's the case.
// Initial last value is set to -1 so only even-numbered philos pick it up
// when the simulation starts.
static void	set_forks(t_fork *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		(forks + i)->last = -1;
		(forks + i)->held = false;
		i++;
	}
}

// Set time_eaten to 1 until all threads have intialized, which will all
// set their personal time_eaten to 0 to signify being ready
static void	set_time_eaten(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		dat->time_eaten[i] = 1;
		i++;
	}
}

// Separate function to split up the actual mallocs and doing something with
// that memory.
void	init_after_malloc(t_data *dat)
{
	set_forks(dat->forks, dat->num);
	set_time_eaten(dat);
}
