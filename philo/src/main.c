/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:59:14 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/12 19:43:03 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>	// pt_create, detach, join. mut_init, destr, lock, unl.
#include <string.h>		// memset(),
#include <stdio.h>		// printf()
#include <stdlib.h>		// malloc(), free()
#include <unistd.h>		// write(), usleep(),
#include <sys/time.h>	// gettimeofday()
#include "../include/philo.h"

void	*pt_start(void *arg)
{
	return (NULL);
}

void	*timer_start(void *arg)
{
	t_data	*dat;

	dat = arg;
}

t_data	*alloc_struct(void)
{
	int		i;
	t_data	*new;

	i = 0;
	new = malloc(sizeof(t_data));
	new->num = 3;
	new->ttd = 5;
	new->tte = 0;
	new->tts = 0;
	gettimeofday(&(new->time), NULL);
	new->tid = malloc(sizeof(pthread_t) * new->num + 1);
	new->stick = malloc(sizeof(int) * new->num + 1);
	while (i < new->num + 1)
	{
		new->stick[i] = 1;
		i++;
	}
	new->life = 1;
	return (new);
}

void	start_threads(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		pthread_create(&(dat->tid[i]), NULL, pt_start, dat);
		i++;
	}
	pthread_create(&(dat->tid[i]), NULL, pt_start, dat);
}

/*
	args: phil_num, death_time, eat_time, sleep_time, (eat_max_amount).
	State changes should be displayed with a message as follows:
	[timestamp] [philo num] [action]
*/
int	main(int argc, char **argv)
{
	t_data	*dat;

	dat = alloc_struct();
	start_threads(dat);
	return (0);
}
