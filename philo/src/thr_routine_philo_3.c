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
	First, check if the philo is already holding a the utensil.
	If they're not, check if this is the start of the simulation.
	In case it's the start of the simulation, only the even-numbered philos
	will grab utensils.
	If it's not the start of the simulation, the philos will also check if
	they're the last one to have held the utensil, if that's that case,
	the philo will not pick it up.
	TODO: make the if-statement more readable maybe? :)
*/
static void	uten_status(t_me *me, t_data *dat, int uten_num, bool uten_side)
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

// Check for available utensils. The 'u' value is the index of the adjacent 
// utensils.
static void	check_utens(t_me *me, t_data *dat)
{
	int		u[2];

	u[0] = me->num;
	u[1] = me->num + 1;
	if (me->num == dat->num - 1)
		u[1] = 0;
	uten_status(me, dat, u[0], 0);
	uten_status(me, dat, u[1], 1);
}

// Philo thinks, while they think they check for forks.
bool	think(t_me *me, t_data *dat)
{
	while (1)
	{
		if (!check_simulation_status(dat))
			return (false);
		check_utens(me, dat);
		if (me->held[0] == true && me->held[1] == true)
			return (true);
		usleep(TIME_S);
	}
}
