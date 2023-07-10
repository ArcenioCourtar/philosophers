/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 17:06:26 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/10 19:01:26 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>//		pt_create, detach, join. mut_init, destr, lock, unl
# include <string.h>//		memset(),
# include <stdio.h>//		printf()
# include <stdlib.h>//		malloc(), free()
# include <unistd.h>//		write(), usleep(),
# include <sys/time.h>//	gettimeofday()
# include <stdbool.h>//		bool!
# include <limits.h>//		useful defines
# define TIME_S 100//		0.1ms sleep time

typedef pthread_mutex_t	t_mutex;

typedef struct s_data
{
	int				num;
	u_int64_t		ttd;
	u_int64_t		tte;
	u_int64_t		tts;
	int				eat_num;
	pthread_t		*tid;
}	t_data;

typedef struct s_tmp
{
	t_data	*dat;
	int		i;
}	t_tmp;

typedef struct s_me
{
	t_data	*dat;
	int		num;
}	t_me;

u_int64_t	my_gettime(void);
bool		ret_msg(const char *str, bool ret);
bool		parse_input(int argc, char **argv, t_data *dat);
void		init_struct(t_data *dat);

//	debug
void		debug_dat_cont(t_data *dat);

#endif