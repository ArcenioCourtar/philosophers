/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo_2.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 18:38:39 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/16 18:35:14 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_simulation_status(int num, t_data *dat);

// maybe return a bool?
void	time_and_print(t_me *me, t_data *dat, const char *txt, \
u_int64_t *ptr_time)
{
	u_int64_t	time;

	pthread_mutex_lock(&(dat->mut_print));
	time = my_gettime();
	if (!check_simulation_status(me->num, dat))
	{
		pthread_mutex_unlock(&(dat->mut_print));
		return ;
	}
	printf("%llu %i %s", time, me->num, txt);
	pthread_mutex_unlock(&(dat->mut_print));
	if (ptr_time)
		*ptr_time = time;
}

void	uten_status(t_me *me, t_data *dat, int uten_num, bool uten_side)
{
	pthread_mutex_lock(&(dat->mut_uten[uten_num]));
	if (!dat->uten[uten_num].held && \
	((dat->uten[uten_num].last == -1 && !(me->num % 2)) \
	|| (dat->uten[uten_num].last != me->num && dat->uten[uten_num].last != -1)))
	{
		dat->uten[uten_num].last = me->num;
		dat->uten[uten_num].held = true;
		me->held[uten_side] = true;
		time_and_print(me, dat, "grabs utensil.\n", NULL);
	}
	pthread_mutex_unlock(&(dat->mut_uten[uten_num]));
}

void	check_utens(t_me *me, t_data *dat)
{
	int		u[2];

	u[0] = me->num;
	u[1] = me->num + 1;
	if (me->num == dat->num - 1)
		u[1] = 0;
	uten_status(me, dat, u[0], 0);
	uten_status(me, dat, u[1], 1);
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

// additional check to avoid should-be dead philos from eating needed
bool	eat(t_me *me, t_data *dat)
{
	pthread_mutex_lock(&(dat->mut_eaten[me->num]));
	time_and_print(me, dat, "is eating.\n", &(dat->time_eaten[me->num]));
	pthread_mutex_unlock(&(dat->mut_eaten[me->num]));
	me->time_eat = dat->time_eaten[me->num];
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
	time_and_print(me, dat, "is sleeping\n", NULL);
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
