/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:59:14 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/13 19:47:35 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ret_msg(const char *str, bool ret)
{
	printf("%s\n", str);
	return (ret);
}

void	init_mutex_list(t_mutex *list, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pthread_mutex_init(&list[i], NULL) != 0)
			printf("yo what happen\n");
		i++;
	}
}

// add proper error handling
void	init_struct(t_data *dat)
{
	dat->time_st = my_gettime();
	dat->tid = malloc(sizeof(pthread_t) * (dat->num + 1));
	if (!dat->tid)
		return ;
	dat->time_meal = malloc(sizeof(u_int64_t) * dat->num);
	if (!dat->time_meal)
		return ;
	dat->time_meal_mut = malloc(sizeof(t_mutex) * dat->num);
	if (!dat->time_meal_mut)
		return ;
	init_mutex_list(dat->time_meal_mut, dat->num);
	dat->stick = malloc(sizeof(int) * dat->num);
	if (!dat->stick)
		return ;
	dat->stick_mut = malloc(sizeof(t_mutex) * dat->num);
	if (!dat->stick_mut)
		return ;
	init_mutex_list(dat->stick_mut, dat->num);
}

void	*pt_philo(void *args)
{
	t_args	*input;
	t_data	*dat;
	int		philonum;

	input = args;
	dat = input->dat;
	philonum = input->i;
	free(args);
	printf("hello I'm philo %i, dat address %p\n", philonum, dat);
	return (NULL);
}

void	start_philo(t_data *dat)
{
	int		i;
	t_args	*args;

	i = 0;
	while (i < dat->num)
	{
		args = malloc(sizeof(t_args));
		if (!args)
			return ;
		args->dat = dat;
		args->i = i;
		pthread_create(&(dat->tid[i]), NULL, pt_philo, args);
		i++;
	}
}

void	*pt_countdown(void *args)
{
	t_data	*dat;

	dat = args;
	pthread_join(dat->tid[dat->num - 1], NULL);
	printf("final thread has executed\n");
	return (NULL);
}

void	start_babysitter(t_data *dat)
{
	pthread_create(&(dat->tid[dat->num]), NULL, pt_countdown, dat);
}

/*
	args: phil_num, death_time, eat_time, sleep_time, (eat_max_amount).
	State changes should be displayed with a message as follows:
	[timestamp] [philo num] [action]
*/
int	main(int argc, char **argv)
{
	t_data	dat;

	if (!parse_input(argc, argv, &dat))
		return (0);
	init_struct(&dat);
	start_philo(&dat);
	start_babysitter(&dat);
	pthread_join(dat.tid[dat.num], NULL);
	printf("reaper has executed");
	return (0);
}
