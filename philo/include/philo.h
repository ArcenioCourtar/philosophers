/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:06:26 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/13 15:58:59 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>	// pt_create, detach, join. mut_init, destr, lock, unl.
# include <string.h>	// memset(),
# include <stdio.h>		// printf()
# include <stdlib.h>	// malloc(), free()
# include <unistd.h>	// write(), usleep(),
# include <sys/time.h>	// gettimeofday()
# include <stdbool.h>	// bool!
# include <limits.h>	// useful defines

typedef struct s_data
{
	u_int64_t		num;
	u_int64_t		ttd;
	u_int64_t		tte;
	u_int64_t		tts;
	u_int64_t		eat_num;
	struct timeval	start;
	struct timeval	time;
	struct timeval	*t_meal;
	pthread_t		*tid;
	int				*stick;
	int				life;
}	t_data;

typedef struct s_stat
{
	struct timeval	t_meal;
}	t_stat;

u_int64_t	my_gettime(void);
bool		ret_msg(const char *str, bool ret);
bool		parse_input(int argc, char **argv, t_data *dat);

#endif