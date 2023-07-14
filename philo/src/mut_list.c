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

void	mut_list_init(t_mutex *list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&list[i], NULL) != 0)
			printf("yo what happen\n");
		i++;
	}
}

void	mut_list_lock(t_mutex *list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_lock(&list[i]);
		i++;
	}
}

void	mut_list_unlock(t_mutex *list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_unlock(&list[i]);
		i++;
	}
}

void	mut_list_destroy(t_mutex *list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&list[i]);
		i++;
	}
}
