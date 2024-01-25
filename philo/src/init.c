/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 17:17:25 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:19:39 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_memset(void *s, int c, size_t n)
{
	void			*ptr;
	unsigned char	c_uchar;

	ptr = s;
	c_uchar = (unsigned char)c;
	while (n > 0)
	{
		*(unsigned char *)ptr = c_uchar;
		n--;
		ptr++;
	}
	return (s);
}

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*array;

	array = malloc(nelem * elsize);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, nelem * elsize);
	return (array);
}

// Sets up the correct values for the utensils.
void	set_uten(t_uten *uten, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		(uten + i)->last = -1;
		(uten + i)->held = false;
		i++;
	}
}

// mallocs space for the mutexes, initializes them if malloc succeeds. 
t_mutex	*malloc_init_mutex(int num)
{
	t_mutex	*new;

	new = malloc(sizeof(t_mutex) * num);
	if (!new)
		return (NULL);
	if (!mut_list_init(new, num))
		return (NULL);
	return (new);
}

bool	init_struct_mut(t_data *dat)
{
	if (pthread_mutex_init(&(dat->mut_running), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(dat->mut_print), NULL) != 0)
		return (false);
	if (!mut_list_init((dat->mut_eaten), dat->num))
		return (false);
	if (!mut_list_init((dat->mut_uten), dat->num))
		return (false);
	if (dat->noe != -1)
	{
		if (!mut_list_init((dat->mut_eat_num), dat->num))
			return (false);
	}
	return (true);
}

bool	init_struct_malloc(t_data *dat)
{
	dat->tid = malloc(sizeof(pthread_t) * (dat->num + 1));
	if (!(dat->tid))
		return (false);
	dat->time_eaten = malloc(sizeof(t_ullong) * dat->num);
	if (!(dat->time_eaten))
		return (false);
	dat->uten = malloc(sizeof(t_uten) * dat->num);
	if (!(dat->uten))
		return (false);
	dat->args = malloc(sizeof(t_tmp) * (dat->num + 1));
	if (!(dat->args))
		return (false);
	dat->mut_eaten = malloc(sizeof(t_mutex) * dat->num);
	if (!(dat->mut_eaten))
		return (false);
	dat->mut_uten = malloc(sizeof(t_mutex) * dat->num);
	if (!(dat->mut_uten))
		return (false);
	if (dat->noe != -1)
	{
		dat->eat_num = ft_calloc(dat->num, sizeof(int));
		if (!(dat->eat_num))
			return (false);
		dat->mut_eat_num = malloc(sizeof(t_mutex) * dat->num);
		if (!(dat->mut_eat_num))
			return (false);
	}
	set_uten(dat->uten, dat->num);
	return (true);
}

// initialize struct that hosts all info regarding time and mutexes.
// TODO: shrink it.
bool	init_struct(t_data *dat)
{
	dat->running = false;
	if (dat->noe != -1)
	{
		dat->eat_num = ft_calloc(dat->num, sizeof(int));
		if (!(dat->eat_num))
			return (false);
	}
	return (true);
}
