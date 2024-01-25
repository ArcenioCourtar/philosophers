/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo_2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 18:38:39 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 15:02:32 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	return_forks(t_me *me, t_data *dat)
{
	int		u[2];

	u[0] = me->num;
	u[1] = me->num + 1;
	if (me->num == dat->num - 1)
		u[1] = 0;
	pthread_mutex_lock(&(dat->mut_fork[u[0]]));
	dat->forks[u[0]].held = false;
	me->held[0] = false;
	pthread_mutex_unlock(&(dat->mut_fork[u[0]]));
	pthread_mutex_lock(&(dat->mut_fork[u[1]]));
	dat->forks[u[1]].held = false;
	me->held[1] = false;
	pthread_mutex_unlock(&(dat->mut_fork[u[1]]));
}

static bool	eat_done(t_me *me, t_data *dat)
{
	return_forks(me, dat);
	if (dat->noe != -1)
	{
		pthread_mutex_lock(&(dat->mut_eat_num[me->num]));
		dat->eat_num[me->num] += 1;
		pthread_mutex_unlock(&(dat->mut_eat_num[me->num]));
	}
	return (true);
}

/*
	Philo starts eating.
	The time_and_print() function has an additional check that makes sure
	an already-dead philo does not start eating. If that's the case the
	"public" time_eaten will be equal to the philo's private value and the 
	message will not print and the thread terminates.
	If the philo is not yet dead it will eat, and at the end of it, 
	return the forks to the table, and increment the amount it has eaten
	if needed.
*/
static bool	eat(t_me *me, t_data *dat)
{
	pthread_mutex_lock(&(dat->mut_eaten[me->num]));
	dat->time_eaten[me->num] = \
	time_and_print(me, dat, "is eating\n");
	if (me->time_eat == dat->time_eaten[me->num] || me->alive == false)
	{
		pthread_mutex_unlock(&(dat->mut_eaten[me->num]));
		return (false);
	}
	me->time_eat = dat->time_eaten[me->num];
	pthread_mutex_unlock(&(dat->mut_eaten[me->num]));
	while (1)
	{
		usleep(TIME_S);
		if (!check_simulation_status(dat))
			return (false);
		if (dat->tte <= my_gettime() - me->time_eat)
			return (eat_done(me, dat));
	}
}

/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⠿⠿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣶⣤⣤⣄⠀⠀⠀⢀⣴⣿⠋⠀⠀⣠⣄⣀⣀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⣽⣿⠟⠀⠀⢰⣿⣟⣁⠀⠀⠀⠙⠛⣿⣿⠇⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣥⣄⠀⠀⠈⠛⠛⠿⠟⠀⠀⣠⣾⣟⣁⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠛⠛⠁⠀⠀
⠀⠀⠀⠀⠀⠀⣀⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣠⣾⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀⠀⠀⠀⠈⠻⣿⣷⣄⠀⠀⠀⠀
⠀⠀⢀⣼⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⢼⣿⣿⣿⣿⡷⠀⢠⣿⡟⠀⢀⣴⣶⠀⠀⠰⣿⡄⠘⠿⠿⠿⠿⠿⠃⠀⠀⠀⠀⠈⠻⣿⣦⡀⠀⠀
⠀⢀⣾⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣄⣠⣾⣿⣿⣦⣠⣼⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣷⡀⠀
⠀⣼⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠛⠉⠀⠈⠙⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣧⠀
⢀⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⡇
⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇
⠘⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇
⠀⢿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡿⠀
⠀⠈⢿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⡿⠃⠀
⠀⠀⠈⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠁⠀⠀
⠀⠀⠀⠀⠈⠻⣿⣷⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣶⣿⡿⠋⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠋⠁⠀⠀⠀⠀⠀⠀
I SLEEP
*/
static bool	philo_sleep(t_me *me, t_data *dat)
{
	t_ullong	time_sleep;

	time_sleep = my_gettime();
	time_and_print(me, dat, "is sleeping\n");
	if (me->alive == false)
		return (false);
	while (1)
	{
		usleep(TIME_S);
		if (!check_simulation_status(dat))
			return (false);
		if (dat->tts <= my_gettime() - time_sleep)
			return (true);
	}
}

// The three functions here all return a boolean value.
// If they return false the simulation has ended either because the reaper 
// thread found a dead philo, or because a dead philo attempted to eat.
void	philo_main(t_me *me, t_data *dat)
{
	while (1)
	{
		if (!think(me, dat))
			break ;
		if (!eat(me, dat))
			break ;
		if (!philo_sleep(me, dat))
			break ;
	}
}
