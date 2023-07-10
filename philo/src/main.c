/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 16:59:14 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/10 19:04:40 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ret_msg(const char *str, bool ret)
{
	printf("%s\n", str);
	return (ret);
}

void	init_philo(t_tmp *args, t_me *me)
{
	me->dat = args->dat;
	me->num = args->i;
	free(args);
}

void	*routine_philo(void *args)
{
	t_me	me;

	init_philo(args, &me);
	printf("ayy, %i\n", me.num);
	return (NULL);
}

void	*routine_reaper(void *args)
{
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
	pthread_create(&(dat->tid[i]), NULL, routine_reaper, args);
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

/*
	args: phil_num, death_time, eat_time, sleep_time, (eat_max_amount).
	State changes should be displayed with a message as follows:
	[timestamp] [philo num] [action]
	NEED TO STOP EACH THREAD BEFORE TERMINATION TO STOP SANITIZER FROM CRYING
*/
int	main(int argc, char **argv)
{
	t_data	dat;

	if (!parse_input(argc, argv, &dat))
		return (0);
	init_struct(&dat);
	debug_dat_cont(&dat);
	create_threads(&dat);
	join_threads(&dat);
	return (0);
}
