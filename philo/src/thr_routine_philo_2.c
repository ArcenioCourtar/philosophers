/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo_2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 18:38:39 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/14 20:24:19 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_simulation_status(int num, t_data *dat);

void	check_utens(t_me *me, t_data *dat)
{
	int		u[2];

	u[0] = me->num;
	u[1] = me->num + 1;
	if (me->num == dat->num - 1)
		u[1] = 0;
	me->time_cur = my_gettime();
	pthread_mutex_lock(&(dat->mut_uten[u[0]]));
	if (!dat->uten[u[0]].held && \
	((dat->uten[u[0]].last == -1 && me->num % 2) \
	|| (dat->uten[u[0]].last != me->num && dat->uten[u[0]].last != -1)))
	{
		dat->uten[u[0]].last = me->num;
		dat->uten[u[0]].held = true;
		me->held[0] = true;
		printf("%llu %i grabs utensil %i\n", me->time_cur, me->num, u[0]);
	}
	pthread_mutex_unlock(&(dat->mut_uten[u[0]]));
	me->time_cur = my_gettime();
	pthread_mutex_lock(&(dat->mut_uten[u[1]]));
	if (!dat->uten[u[1]].held && \
	((dat->uten[u[1]].last == -1 && me->num % 2) \
	|| (dat->uten[u[1]].last != me->num && dat->uten[u[1]].last != -1)))
	{
		dat->uten[u[1]].last = me->num;
		dat->uten[u[1]].held = true;
		me->held[1] = true;
		printf("%llu %i grabs utensil %i\n", me->time_cur, me->num, u[1]);
	}
	pthread_mutex_unlock(&(dat->mut_uten[u[1]]));
}

void	return_utens(t_me *me, t_data *dat)
{
	int		u[2];

	u[0] = me->num;
	u[1] = me->num + 1;
	if (me->num == dat->num - 1)
		u[1] = 0;
	pthread_mutex_lock(&(dat->mut_uten[u[0]]));
	dat->uten[u[0]].held = false;
	me->held[0] = false;
	pthread_mutex_unlock(&(dat->mut_uten[u[0]]));
	pthread_mutex_lock(&(dat->mut_uten[u[1]]));
	dat->uten[u[1]].held = false;
	me->held[1] = false;
	pthread_mutex_unlock(&(dat->mut_uten[u[1]]));
}

bool	think(t_me *me, t_data *dat)
{
	while (1)
	{
		if (!check_simulation_status(me->num, dat))
			return (false);
		check_utens(me, dat);
		if (me->held[0] == true && me->held[1] == true)
			return (true);
		usleep(TIME_S);
	}
}

bool	eat(t_me *me, t_data *dat)
{
	me->time_eat = my_gettime();
	pthread_mutex_lock(&(dat->mut_eaten[me->num]));
	dat->time_eaten[me->num] = me->time_eat;
	pthread_mutex_unlock(&(dat->mut_eaten[me->num]));
	printf("%llu %i is eating\n", me->time_eat, me->num);
	while (1)
	{
		usleep(TIME_S);
		if (!check_simulation_status(me->num, dat))
			return (false);
		if (dat->tte <= my_gettime() - me->time_eat)
		{
			return_utens(me, dat);
			return (true);
		}
	}
}

bool	philo_sleep(t_me *me, t_data *dat)
{
	u_int64_t	time_sleep;

	time_sleep = my_gettime();
	printf("%llu %i is sleeping\n", time_sleep, me->num);
	while (1)
	{
		usleep(TIME_S);
		if (!check_simulation_status(me->num, dat))
			return (false);
		if (dat->tts <= my_gettime() - me->time_cur)
			return (true);
	}
}

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
