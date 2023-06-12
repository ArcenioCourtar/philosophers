/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:59:14 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/12 15:37:41 by acourtar         ###   ########.fr       */
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
	int	*test;

	test = arg;
	*test += 1;
	return (NULL);
}

void	alloc_struct(t_data *dat)
{
	int	i;

	i = 0;
	dat = malloc(sizeof(t_data));
	dat->num = 3;
	dat->ttd = 5;
	dat->tte = 0;
	dat->tts = 0;
	gettimeofday(&(dat->time), NULL);
	dat->tid = malloc(sizeof(pthread_t) * dat->num);
	dat->stick = malloc(sizeof(int) * dat->num + 1);
	while (i < dat->num + 1)
	{
		dat->stick[i] = 1;
		i++;
	}
	dat->life = 1;
}

/*
	args: phil_num, death_time, eat_time, sleep_time, (eat_max_amount).
	State changes should be displayed with a message as follows:
	[timestamp] [philo num] [action]
*/
int	main(int argc, char **argv)
{
	t_data	*dat;

	alloc_struct(dat);
	
	return (0);
}
