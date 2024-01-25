/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 17:06:26 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 15:33:34 by acourtar      ########   odam.nl         */
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
# define TIME_S 200//		sleep time in microseconds (1ms == 1000)
# define CONVERT 1000//		millisecond to microsecond factor

typedef pthread_mutex_t		t_mutex;
typedef struct s_tmp		t_tmp;
typedef unsigned long long	t_ullong;

// struct to keep track of fork state.
typedef struct s_fork
{
	int		last;
	bool	held;
}	t_fork;

// main public data structure.
typedef struct s_data
{
	int			num;
	t_ullong	ttd;
	t_ullong	tte;
	t_ullong	tts;
	int			noe;
	bool		running;
	t_mutex		mut_running;
	t_mutex		mut_print;
	int			*eat_num;
	t_ullong	*time_eaten;
	t_fork		*forks;
	pthread_t	*tid;
	t_tmp		*args;
	t_mutex		*mut_eat_num;
	t_mutex		*mut_eaten;
	t_mutex		*mut_fork;
	int			count_mut;
	int			count_thr;
}	t_data;

// temporary struct used to pass along info to the threads.
typedef struct s_tmp
{
	t_data	*dat;
	int		num;
}	t_tmp;

// private struct for each philo
// tracks time they last ate, and if they're holding forks
typedef struct s_me
{
	int			num;
	t_ullong	time_eat;
	bool		held[2];
	bool		alive;
}	t_me;

// parsing

bool		parse_input(int argc, char **argv, t_data *dat);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
int			ft_isspace(int c);
long		ft_atol(const char *str);
bool		ret_msg(const char *str, bool ret);

// managing mutex arrays

bool		mut_list_init(t_data *dat, t_mutex *list);
void		mut_list_lock(t_mutex *list, int len);
void		mut_list_unlock(t_mutex *list, int len);
void		mut_list_destroy(t_data *dat, t_mutex *list, int len);

// time management

t_ullong	my_gettime(void);
t_ullong	time_and_print(t_me *me, t_data *dat, const char *txt);
void		init_struct(t_data *dat);
bool		init_struct_malloc(t_data *dat);
bool		init_struct_mut(t_data *dat);

// thread related functions

bool		create_threads(t_data *dat);
void		*routine_philo(void *args);
void		*routine_reap(void *args);
bool		check_simulation_status(t_data *dat);
void		check_eat_times(t_data *dat);
void		simulation_end(t_data *dat);

// 5 function per file limit. :(

bool		think(t_me *me, t_data *dat);
void		*ft_calloc(size_t nelem, size_t elsize);

#endif