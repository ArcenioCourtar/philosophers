/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:59:14 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/12 12:50:28 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>	// pt_create, detach, join. mut_init, destr, lock, unl.
#include <string.h>		// memset(),
#include <stdio.h>		// printf()
#include <stdlib.h>		// malloc(), free()
#include <unistd.h>		// write(), usleep(),
#include <sys/time.h>	// gettimeofday()
#include "../include/philo.h"

void *pt_start(void *arg)
{
	while (1) {
		printf("yo");
	}
	return (NULL);
}

/*
	args: phil_num, death_time, eat_time, sleep_time, (eat_max_amount).
	State changes should be displayed with a message as follows:
	[timestamp] [philo num] [action]
*/
int	main(void)
{
	struct timeval	cur_time;
	int	phil_num = 3;
	pthread_t test;
	int *chopsticks = malloc(sizeof(int));
	int i = 0;
	
	*chopsticks = phil_num + 1;
	printf("thread id: %lu\n", test);
	while (i < phil_num) {
		if (pthread_create(&test, NULL, pt_start, NULL) != 0)
			return (0);
		printf("thread id: %lu\n", test);
		i++;
	}
	gettimeofday(&cur_time, NULL);
	printf("sec: %ld, ms: %i\n", cur_time.tv_sec, cur_time.tv_usec);
	return (0);
}
