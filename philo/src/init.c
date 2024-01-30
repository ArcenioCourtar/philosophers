/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:17:25 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:19:39 by acourtar      ########   odam.nl         */
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

bool	init_struct_mut(t_data *dat)
{
	if (pthread_mutex_init(&(dat->mut_running), NULL) != 0)
		return (false);
	dat->count_mut++;
	if (pthread_mutex_init(&(dat->mut_print), NULL) != 0)
		return (false);
	dat->count_mut++;
	if (!mut_list_init(dat, (dat->mut_time_eaten)))
		return (false);
	if (!mut_list_init(dat, (dat->mut_fork)))
		return (false);
	if (dat->noe != -1)
	{
		if (!mut_list_init(dat, (dat->mut_eat_num)))
			return (false);
	}
	return (true);
}

bool	noe_condition(t_data *dat)
{
	if (dat->noe != -1)
	{
		dat->eat_num = ft_calloc(dat->num, sizeof(int));
		if (!(dat->eat_num))
			return (false);
		dat->mut_eat_num = malloc(sizeof(t_mutex) * dat->num);
		if (!(dat->mut_eat_num))
			return (false);
	}
	return (true);
}

bool	init_struct_malloc(t_data *dat)
{
	dat->tid = malloc(sizeof(pthread_t) * (dat->num + 1));
	if (!(dat->tid))
		return (false);
	dat->time_eaten = malloc(sizeof(t_ullong) * dat->num);
	if (!(dat->time_eaten))
		return (false);
	dat->forks = malloc(sizeof(t_fork) * dat->num);
	if (!(dat->forks))
		return (false);
	dat->args = malloc(sizeof(t_tmp) * (dat->num));
	if (!(dat->args))
		return (false);
	dat->mut_time_eaten = malloc(sizeof(t_mutex) * dat->num);
	if (!(dat->mut_time_eaten))
		return (false);
	dat->mut_fork = malloc(sizeof(t_mutex) * dat->num);
	if (!(dat->mut_fork))
		return (false);
	if (!noe_condition(dat))
		return (false);
	set_forks(dat->forks, dat->num);
	return (true);
}

// initialize values that aren't passed by the user, and not malloc related
void	init_struct(t_data *dat)
{
	dat->running = false;
	dat->tid = NULL;
	dat->time_eaten = NULL;
	dat->forks = NULL;
	dat->args = NULL;
	dat->mut_time_eaten = NULL;
	dat->mut_fork = NULL;
	dat->eat_num = NULL;
	dat->mut_eat_num = NULL;
	dat->count_mut = 0;
	dat->count_thr = 0;
}
