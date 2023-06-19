/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:26:35 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/19 17:37:37 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

void	init_myself(t_data **dat, t_me *me, void *args)
{
	t_tmp	*tmp;

	tmp = args;
	*dat = tmp->dat;
	me->num = tmp->i;
	stickindexer(me->num, (*dat)->num, me->i);
	free(args);
	me->time_cur = (*dat)->time_st;
	me->time_meal = (*dat)->time_st;
}

void	take_stick(t_data *dat, t_me *me, bool have_stick[2], bool uneven)
{
	me->time_cur = my_gettime();
	if (uneven)
	{
		if (have_stick[0] == false)
		{
			pthread_mutex_lock(&dat->stick_mut[me->i[0]]);
			if (dat->stick[me->i[0]] == true)
			{
				printf("%llu %i picks up left stick\n", (me->time_cur - dat->time_st) / 1000, me->num);
				have_stick[0] = true;
				dat->stick[me->i[0]] = false;
			}
			pthread_mutex_unlock(&dat->stick_mut[me->i[0]]);
		}
		else
		{
			pthread_mutex_lock(&dat->stick_mut[me->i[1]]);
			if (dat->stick[me->i[1]] == true)
			{
				printf("%llu %i picks up right stick\n", (me->time_cur - dat->time_st) / 1000, me->num);
				have_stick[1] = true;
				dat->stick[me->i[1]] = false;
			}
			pthread_mutex_unlock(&dat->stick_mut[me->i[1]]);
		}
	}
	else
	{
		if (have_stick[1] == false)
		{
			pthread_mutex_lock(&dat->stick_mut[me->i[1]]);
			if (dat->stick[me->i[1]] == true)
			{
				printf("%llu %i picks up right stick\n", (me->time_cur - dat->time_st) / 1000, me->num);
				have_stick[1] = true;
				dat->stick[me->i[1]] = false;
			}
			pthread_mutex_unlock(&dat->stick_mut[me->i[1]]);
		}
		else
		{
			pthread_mutex_lock(&dat->stick_mut[me->i[0]]);
			if (dat->stick[me->i[0]] == true)
			{
				printf("%llu %i picks up left stick\n", (me->time_cur - dat->time_st) / 1000, me->num);
				have_stick[0] = true;
				dat->stick[me->i[0]] = false;
			}
			pthread_mutex_unlock(&dat->stick_mut[me->i[0]]);
		}
	}
}


void	meal_prep(t_data *dat, t_me *me)
{
	bool	have_stick[2];

	have_stick[0] = false;
	have_stick[1] = false;
	me->time_cur = my_gettime();
	printf("%llu %i is thinking about sticks %i, %i\n", \
	(me->time_cur - dat->time_st) / 1000, me->num, me->i[0], me->i[1]);
	while (have_stick[0] == false || have_stick[1] == false)
	{
		if (me->num % 2 == 0)
			take_stick(dat, me, have_stick, false);
		else
			take_stick(dat, me, have_stick, true);
	}
}

void	eat(t_data *dat, t_me *me)
{
	unsigned int	sleeptime;

	me->time_cur = my_gettime();
	me->time_meal = me->time_cur;
	pthread_mutex_lock(&(dat->time_meal_mut[me->num]));
	dat->time_meal[me->num] = me->time_meal;
	pthread_mutex_unlock(&(dat->time_meal_mut[me->num]));
	printf("%llu %i is eating\n", (me->time_cur - dat->time_st) / 1000, me->num);
	sleeptime = dat->tte - TIME_S;
	usleep(sleeptime);
	while (me->time_cur - me->time_meal <= dat->tte)
		me->time_cur = my_gettime();
	pthread_mutex_lock(&(dat->stick_mut[me->i[0]]));
	dat->stick[me->i[0]] = true;
	pthread_mutex_unlock(&(dat->stick_mut[me->i[0]]));
	pthread_mutex_lock(&(dat->stick_mut[me->i[1]]));
	dat->stick[me->i[1]] = true;
	pthread_mutex_unlock(&(dat->stick_mut[me->i[1]]));
}

void	go_sleep(t_data *dat, t_me *me)
{
	unsigned int	sleeptime;

	me->time_sleep = my_gettime();
	printf("%llu %i is sleeping\n", (me->time_sleep - dat->time_st) / 1000, me->num);
	sleeptime = (dat->tts - TIME_S);
	usleep(sleeptime);
	me->time_cur = my_gettime();
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
		dat->time_cur = my_gettime();
		//printf("time diff now and meal: %llu\n", (dat->time_cur - dat->time_meal[i]) / 1000);
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
		usleep(TIME_S);
		pthread_mutex_lock(&(dat->time_cur_mut));
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

	dat->time_st = my_gettime();
	dat->time_cur = dat->time_st;
	i = 0;
	while (i < dat->num)
	{
		dat->time_meal[i] = dat->time_st;
		i++;
	}
	i = 0;
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
}

void	start_babysitter(t_data *dat)
{
	pthread_create(&(dat->tid[dat->num]), NULL, pt_countdown, dat);
}
