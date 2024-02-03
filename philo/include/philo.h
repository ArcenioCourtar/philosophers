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
	t_ullong	start_time;
	int			running;
	t_mutex		mut_running;
	t_mutex		mut_print;
	int			*eat_num;
	t_ullong	*time_eaten;
	t_fork		*forks;
	pthread_t	*tid;
	t_tmp		*args;
	t_mutex		*mut_eat_num;
	t_mutex		*mut_time_eaten;
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
// tracks time they last ate, the held forks, and if they should be alive
typedef struct s_me
{
	int			num;
	t_ullong	time_eaten;
	bool		held[2];
	bool		alive;
}	t_me;

// wow it's calloc

void		*ft_calloc(size_t nelem, size_t elsize);

// parsing

bool		parse_input(int argc, char **argv, t_data *dat);
int			ft_isdigit(int c);
int			ft_isspace(int c);
long		ft_atol(const char *str);
size_t		ft_strlen(const char *s);

// managing mutex arrays

void		mut_list_destroy(t_data *dat, t_mutex *list, int len);
bool		mut_list_init(t_data *dat, t_mutex *list);

// time management

t_ullong	my_gettime(t_data *dat);
t_ullong	time_and_print(t_me *me, t_data *dat, const char *txt);

// setting up the struct before the simulation

void		init_struct(t_data *dat);
void		init_after_malloc(t_data *dat);
bool		init_struct_malloc(t_data *dat);
bool		init_struct_mut(t_data *dat);

// thread routines

void		*routine_philo(void *args);
void		*routine_reap(void *args);

// thread related functions

void		check_eat_times(t_data *dat);
bool		create_threads(t_data *dat);
int			check_simulation_status(t_data *dat);

// cleanup

void		destroy_mutexes(t_data *dat);
void		join_threads(t_data *dat);
int			cleanup(t_data *dat, int exit_code);
bool		ret_msg(const char *str, bool ret);

// 5 function per file limit. :(

bool		think(t_me *me, t_data *dat);
void		philo_main(t_me *me, t_data *dat);

#endif