/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/15 17:32:44 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_myself(t_data **dat, t_me *me, void *args)
{
	t_tmp	*tmp;

	tmp = args;
	*dat = tmp->dat;
	me->num = tmp->i;
	//stickindexer(me->num, &(*dat)->num, me->i);
	free(args);
	pthread_mutex_lock(&(*dat)->ready);
	me->time_cur = (*dat)->time_st;
	me->time_meal = (*dat)->time_st;
	pthread_mutex_unlock(&(*dat)->ready);
}

void	stickindexer(int me_num, int max_num, int i[2])
{
	if (me_num == 0)
	{
		i[0] = max_num - 1;
		i[1] = me_num;
	}
	else
	{
		i[0] = me_num - 1;
		i[1] = me_num;
	}
}

void	meal_prep(t_data *dat, t_me *me)
{
	int	i[2];

	me->time_cur = my_gettime();
	printf("%llu %i is thinking\n", (me->time_cur - dat->time_st) / 1000, me->num);
	stickindexer(me->num, dat->num, i);
	while (1)
	{
		pthread_mutex_lock(&(dat->stick_mut[i[0]]));
		pthread_mutex_lock(&(dat->stick_mut[i[1]]));
		if (dat->stick[i[0]] == true && dat->stick[i[1]] == true)
		{
			me->time_cur = my_gettime();
			dat->stick[i[0]] = false;
			printf("%llu %i has taken a fork\n", (me->time_cur - dat->time_st) / 1000, me->num);
			dat->stick[i[1]] = false;
			printf("%llu %i has taken a fork\n", (me->time_cur - dat->time_st) / 1000, me->num);
			pthread_mutex_unlock(&(dat->stick_mut[i[0]]));
			pthread_mutex_unlock(&(dat->stick_mut[i[1]]));
			break ;
		}
		pthread_mutex_unlock(&(dat->stick_mut[i[0]]));
		pthread_mutex_unlock(&(dat->stick_mut[i[1]]));
	}
}

void	eat(t_data *dat, t_me *me)
{
	int	i[2];

	me->time_meal = my_gettime();
	me->time_cur = me->time_meal;
	printf("%llu %i is eating\n", (me->time_cur - dat->time_st) / 1000, me->num);
	stickindexer(me->num, dat->num, i);
	while (me->time_cur - me->time_meal <= dat->tte)
		me->time_cur = my_gettime();
	pthread_mutex_lock(&(dat->stick_mut[i[0]]));
	pthread_mutex_lock(&(dat->stick_mut[i[1]]));
	dat->stick[i[0]] = true;
	dat->stick[i[1]] = true;
	pthread_mutex_unlock(&(dat->stick_mut[i[0]]));
	pthread_mutex_unlock(&(dat->stick_mut[i[1]]));
}

void	go_sleep(t_data *dat, t_me *me)
{
	int	sleeptime;

	me->time_sleep = my_gettime();
	printf("%llu %i is sleeping\n", (me->time_sleep - dat->time_st) / 1000, me->num);
	sleeptime = (dat->tts - 1) * TIME_S;
	usleep(sleeptime);
	me->time_cur = my_gettime();
	printf("%i is WOKE\n", me->num);
	while (me->time_cur <= me->time_sleep + dat->tts)
		me->time_cur = my_gettime();
}

void	*pt_philo(void *args)
{
	t_data		*dat;
	t_me		me;

	init_myself(&dat, &me, args);
	while (1)
	{
		meal_prep(dat, &me);
		eat(dat, &me);
		go_sleep(dat, &me);
	}
	// printf("philo number %i, dat addr %p\n", me.num, dat);
	return (NULL);
}

// MUTEXES
bool	kill_time(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num)
	{
		pthread_mutex_lock(&(dat->time_meal_mut[i]));
		// printf("time diff now and meal: %llu\n", (dat->time_cur - dat->time_meal[i]) / 1000);
		if (dat->time_cur - dat->time_meal[i] >= dat->ttd)
		{
			pthread_mutex_unlock(&(dat->time_meal_mut[i]));
			return (true);
		}
		pthread_mutex_unlock(&(dat->time_meal_mut[i]));
		i++;
	}
	return (false);
}

void	*pt_countdown(void *args)
{
	t_data	*dat;

	dat = args;
	while (1)
	{
		pthread_mutex_lock(&(dat->time_cur_mut));
		dat->time_cur = my_gettime();
		if (kill_time(dat))
		{
			printf("time elapsed in ms: %llu\n", (dat->time_cur - dat->time_st) / 1000);
			pthread_mutex_unlock(&(dat->time_cur_mut));
			break ;
		}
		pthread_mutex_unlock(&(dat->time_cur_mut));
	}
	return (NULL);
}

void	start_philo(t_data *dat)
{
	int		i;
	t_tmp	*args;

	i = 0;
	pthread_mutex_lock(&(dat->ready));
	while (i < dat->num)
	{
		args = malloc(sizeof(t_tmp));
		if (!args)
			return ;
		args->dat = dat;
		args->i = i;
		pthread_create(&(dat->tid[i]), NULL, pt_philo, args);
		i++;
	}
	dat->time_st = my_gettime();
	dat->time_cur = dat->time_st;
	i = 0;
	while (i < dat->eat_num)
	{
		dat->time_meal[i] = dat->time_st;
		i++;
	}
	pthread_mutex_unlock(&(dat->ready));
}

void	start_babysitter(t_data *dat)
{
	pthread_create(&(dat->tid[dat->num]), NULL, pt_countdown, dat);
}
