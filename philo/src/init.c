/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:17:25 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 15:37:56 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// add proper error handling
void	init_struct(t_data *dat)
{
	dat->ready = false;
	pthread_mutex_init(&(dat->mut_ready), NULL);
	dat->mut_ready_arr = malloc(sizeof(t_mutex) * dat->num);
	mut_list_init(dat->mut_ready_arr, dat->num);
}
