/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/11 12:33:59 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/11 16:29:46 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philo(t_tmp *args, t_me *me)
{
	me->dat = args->dat;
	me->num = args->i;
	free(args);
	me->time_cur = my_gettime();
}

u_int64_t	time_diff(u_int64_t start, u_int64_t cur)
{
	return (cur - start);
}

void	debug_time_diff(t_data *dat, u_int64_t time, int num)
{
	if (time > dat->debug_time[1])
	{
		dat->debug_time[1] = time;
		dat->debug_num = num;
	}
}

void	*routine_philo(void *args)
{
	t_me	me;

	init_philo(args, &me);
	printf("philo %i, time: %llu\n", me.num, time_diff(me.dat->time_start, me.time_cur));
	debug_time_diff(me.dat, me.time_cur, me.num);
	return (NULL);
}

void	*routine_reaper(void *args)
{
	t_tmp		*tmp;
	t_data		*dat;
	u_int64_t	time_cur;

	tmp = args;
	dat = tmp->dat;
	free(args);
	time_cur = my_gettime();
	printf("reaperman, time: %llu\n", time_diff(dat->time_start, time_cur));
	debug_time_diff(dat, time_cur, -1);
	return (NULL);
}

bool	create_threads(t_data *dat)
{
	t_tmp	*args;
	int		i;

	dat->tid = malloc(sizeof(pthread_t) * (dat->num + 1));
	if (!dat->tid)
		return (false);
	i = 0;
	dat->time_start = my_gettime();
	dat->debug_time[0] = dat->time_start; dat->debug_time[1] = dat->time_start; dat->debug_num = -1;
	args = malloc(sizeof(t_tmp));
	if (!args)
		return (false);
	args->dat = dat;
	pthread_create(&(dat->tid[dat->num]), NULL, routine_reaper, args);
	while (i < dat->num)
	{
		args = malloc(sizeof(t_tmp));
		if (!args)
			return (false);
		args->dat = dat;
		args->i = i;
		pthread_create(&(dat->tid[i]), NULL, routine_philo, args);
		i++;
	}
	return (true);
}

void	join_threads(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num + 1)
	{
		pthread_join(dat->tid[i], NULL);
		i++;
	}
	printf("all threads closed\n");
}
