/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_reaper_2.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 14:04:26 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 15:44:22 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// If the amount of times they need to eat is specified, check the amount of
// times each philo has eaten.
void	check_eat_num(t_data *dat, int num, int *lowest_eat)
{
	if (dat->noe == -1)
		return ;
	pthread_mutex_lock(&(dat->mut_eat_num[num]));
	if (*lowest_eat == -1)
		*lowest_eat = dat->eat_num[num];
	else if (*lowest_eat > dat->eat_num[num])
		*lowest_eat = dat->eat_num[num];
	pthread_mutex_unlock(&(dat->mut_eat_num[num]));
}

static bool	death_check(t_data *dat, int i)
{
	t_ullong	time_curr;

	pthread_mutex_lock(&(dat->mut_eaten[i]));
	time_curr = my_gettime();
	if (time_curr >= (dat->time_eaten[i] + dat->ttd))
	{
		pthread_mutex_lock(&(dat->mut_print));
		simulation_end(dat);
		printf("%llu %i died\n", time_curr / CONVERT, i);
		pthread_mutex_unlock(&(dat->mut_print));
		pthread_mutex_unlock(&(dat->mut_eaten[i]));
		return (true);
	}
	pthread_mutex_unlock(&(dat->mut_eaten[i]));
	return (false);
}

static bool	eat_num_check(t_data *dat, int lowest_eat)
{
	if (dat->noe != -1 && (lowest_eat >= dat->noe))
	{
		pthread_mutex_lock(&(dat->mut_print));
		simulation_end(dat);
		printf("%llu all philos have eaten %i times\n", \
		my_gettime() / CONVERT, dat->noe);
		pthread_mutex_unlock(&(dat->mut_print));
		return (true);
	}
	return (false);
}

// Check if a philo has died, or if all philos have eaten enough.
void	check_eat_times(t_data *dat)
{
	int			i;
	int			lowest_eat;

	while (1)
	{
		lowest_eat = -1;
		i = 0;
		while (i < dat->num)
		{
			if (death_check(dat, i))
				return ;
			check_eat_num(dat, i, &lowest_eat);
			i++;
		}
		if (eat_num_check(dat, lowest_eat))
			return ;
		usleep(100);
	}
}
