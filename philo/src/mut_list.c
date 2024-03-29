/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mut_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 15:36:29 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 15:38:53 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	mut_list_init(t_data *dat, t_mutex *list)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		if (pthread_mutex_init(&list[i], NULL) != 0)
			return (false);
		i++;
		dat->count_mut++;
	}
	return (true);
}

void	mut_list_destroy(t_data *dat, t_mutex *list)
{
	int	i;

	i = 0;
	while (i < dat->num && dat->count_mut > 0)
	{
		pthread_mutex_destroy(&list[i]);
		i++;
		dat->count_mut--;
	}
}
