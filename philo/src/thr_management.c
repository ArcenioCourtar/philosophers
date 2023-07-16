/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_management.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:33:59 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/16 17:48:39 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	create_threads(t_data *dat)
{
	t_tmp	*args;
	int		i;

	dat->tid = malloc(sizeof(pthread_t) * (dat->num + 1));
	if (!dat->tid)
		return (false);
	i = 0;
	while (i < dat->num)
	{
		args = malloc(sizeof(t_tmp));
		if (!args)
			return (false);
		args->dat = dat;
		args->num = i;
		pthread_create(&(dat->tid[i]), NULL, routine_philo, args);
		i++;
	}
	args = malloc(sizeof(t_tmp));
	if (!args)
		return (false);
	args->dat = dat;
	pthread_create(&(dat->tid[dat->num]), NULL, routine_reaper, args);
	return (true);
}

// Maybe destroy mutexes as well?
void	join_threads(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num + 1)
	{
		pthread_join(dat->tid[i], NULL);
		i++;
	}
	printf("-----------------------------------\n");
}
