/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:06:26 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/12 15:37:27 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>	// pt_create, detach, join. mut_init, destr, lock, unl.
# include <string.h>		// memset(),
# include <stdio.h>		// printf()
# include <stdlib.h>		// malloc(), free()
# include <unistd.h>		// write(), usleep(),
# include <sys/time.h>	// gettimeofday()

typedef struct s_data
{
	int				num;
	int				ttd;
	int				tte;
	int				tts;
	struct timeval	time;
	pthread_t		*tid;
	int				*stick;
	int				life;
}	t_data;

#endif