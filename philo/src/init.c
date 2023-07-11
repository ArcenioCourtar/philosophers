/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:17:25 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/11 17:51:26 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	init_mutex_list(t_mutex *list, int len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		if (pthread_mutex_init(&list[i], NULL) != 0)
// 			printf("yo what happen\n");
// 		i++;
// 	}
// }

// add proper error handling
void	init_struct(t_data *dat)
{
	dat->ready = false;
	pthread_mutex_init(&(dat->mut_ready), NULL);
}
