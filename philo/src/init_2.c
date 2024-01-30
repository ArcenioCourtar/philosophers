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
void	set_forks(t_fork *forks, int num)
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

void	set_time_eaten(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		dat->time_eaten[i] = 1;
		i++;
	}
}

void	init_after_malloc(t_data *dat)
{
	set_forks(dat->forks, dat->num);
	set_time_eaten(dat);
}
