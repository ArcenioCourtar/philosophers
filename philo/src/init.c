/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:17:25 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/16 18:08:58 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// I should write a calloc func later....
void	set_uten(t_uten *uten, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		(uten + i)->last = -1;
		(uten + i)->held = false;
		i++;
	}
}

// add proper error handling
void	init_struct(t_data *dat)
{
	dat->ready = false;
	dat->running = true; 
	pthread_mutex_init(&(dat->mut_ready), NULL);
	dat->time_eaten = malloc(sizeof(u_int64_t) * dat->num);
	if (!(dat->time_eaten))
		return ;
	dat->mut_eaten = malloc(sizeof(t_mutex) * dat->num);
	if (!(dat->mut_eaten))
		return ;
	mut_list_init(dat->mut_eaten, dat->num);
	dat->mut_running = malloc(sizeof(t_mutex) * dat->num);
	if (!(dat->mut_running))
		return ;
	mut_list_init(dat->mut_running, dat->num);
	dat->uten = malloc(sizeof(t_uten) * dat->num);
	if (!(dat->uten))
		return ;
	set_uten(dat->uten, dat->num);
	dat->mut_uten = malloc(sizeof(t_mutex) * dat->num);
	if (!(dat->mut_uten))
		return ;
	mut_list_init(dat->mut_uten, dat->num);
	pthread_mutex_init(&(dat->mut_print), NULL);
}
