/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thr_routine_philo_3.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 14:45:06 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:55:30 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	First, check if the philo is already holding a fork
	If they're not, check if this is the start of the simulation.
	In case it's the start of the simulation, only the even-numbered philos
	will grab forks.
	If it's not the start of the simulation, the philos will also check if
	they're the last one to have held the forks, if that's that case,
	the philo will not pick it up.
*/
static void	fork_status(t_me *me, t_data *dat, int fork_num, bool fork_side)
{
	pthread_mutex_lock(&(dat->mut_fork[fork_num]));
	if (!dat->forks[fork_num].held && \
	((dat->forks[fork_num].last == -1 && !(me->num % 2)) \
	|| (dat->forks[fork_num].last != me->num \
	&& dat->forks[fork_num].last != -1)))
	{
		dat->forks[fork_num].last = me->num;
		dat->forks[fork_num].held = true;
		me->held[fork_side] = true;
		time_and_print(me, dat, "has taken a fork\n", NULL);
	}
	pthread_mutex_unlock(&(dat->mut_fork[fork_num]));
}

// Check for available forks. The 'u' value is the index of the adjacent 
// forks.
static void	check_forks(t_me *me, t_data *dat)
{
	int		u[2];

	u[0] = me->num;
	u[1] = me->num + 1;
	if (me->num == dat->num - 1)
		u[1] = 0;
	fork_status(me, dat, u[0], 0);
	fork_status(me, dat, u[1], 1);
}

// Philo thinks, while they think they check for forks.
bool	think(t_me *me, t_data *dat)
{
	time_and_print(me, dat, "is thinking\n", NULL);
	while (1)
	{
		if (!check_simulation_status(dat))
			return (false);
		check_forks(me, dat);
		if (me->held[0] == true && me->held[1] == true)
			return (true);
		usleep(TIME_S);
	}
}
