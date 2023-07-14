/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 17:06:26 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 20:27:56 by acourtar      ########   odam.nl         */
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
# define TIME_S 50//		0.1ms sleep time

typedef pthread_mutex_t	t_mutex;

typedef struct s_uten
{
	int		last;
	bool	held;
}	t_uten;

typedef struct s_data
{
	int				num;
	u_int64_t		ttd;
	u_int64_t		tte;
	u_int64_t		tts;
	t_mutex			*mut_eaten;
	u_int64_t		*time_eaten;
	int				eat_num;
	pthread_t		*tid;
	u_int64_t		time_start;
	t_mutex			mut_ready;
	bool			ready;
	t_mutex			*mut_running;
	bool			running;
	struct s_uten	*uten;
	t_mutex			*mut_uten;
}	t_data;

typedef struct s_tmp
{
	t_data	*dat;
	int		num;
}	t_tmp;

typedef struct s_me
{
	int			num;
	u_int64_t	time_cur;
	u_int64_t	time_eat;
	bool		held[2];
}	t_me;

u_int64_t	my_gettime(void);
bool		ret_msg(const char *str, bool ret);
bool		parse_input(int argc, char **argv, t_data *dat);
void		init_struct(t_data *dat);
bool		create_threads(t_data *dat);
void		join_threads(t_data *dat);
void		mut_list_init(t_mutex *list, int len);
void		mut_list_lock(t_mutex *list, int len);
void		mut_list_unlock(t_mutex *list, int len);
void		mut_list_destroy(t_mutex *list, int len);
void		*routine_philo(void *args);
void		*routine_reaper(void *args);

//	debug
void		debug_dat_cont(t_data *dat);

#endif