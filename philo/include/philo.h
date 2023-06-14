/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:06:26 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/14 17:28:41 by acourtar         ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	int				num;
	u_int64_t		ttd;
	u_int64_t		tte;
	u_int64_t		tts;
	int				eat_num;
	pthread_t		*tid;
	u_int64_t		time_st;
	u_int64_t		time_cur;
	t_mutex			time_cur_mut;
	u_int64_t		*time_meal;
	t_mutex			*time_meal_mut;
	int				*stick;
	t_mutex			*stick_mut;
}	t_data;

typedef struct s_args
{
	t_data	*dat;
	int		i;
}	t_args;

u_int64_t	my_gettime(void);
bool		ret_msg(const char *str, bool ret);
bool		parse_input(int argc, char **argv, t_data *dat);
void		init_struct(t_data *dat);
void		start_philo(t_data *dat);
void		start_babysitter(t_data *dat);

#endif