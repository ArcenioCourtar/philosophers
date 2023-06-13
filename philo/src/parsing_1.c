/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:51:26 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/13 16:14:36 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_isspace(int c);
long	ft_atol(const char *str);

static bool	all_nums(const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

// too beeg
static bool	assign_num(int argc, char **argv, t_data *dat)
{
	int			i;
	u_int64_t	tmp;

	i = 1;
	tmp = ft_atol(argv[i]);
	if (tmp > INT_MAX)
		return (false);
	dat->num = tmp;
	i++;
	tmp = ft_atol(argv[i]);
	if (tmp > INT_MAX)
		return (false);
	dat->ttd = tmp * 1000;
	i++;
	tmp = ft_atol(argv[i]);
	if (tmp > INT_MAX)
		return (false);
	dat->tte = tmp * 1000;
	i++;
	tmp = ft_atol(argv[i]);
	if (tmp > INT_MAX)
		return (false);
	dat->tts = tmp * 1000;
	i++;
	if (argc == 6)
	{
		tmp = ft_atol(argv[i]);
		if (tmp > INT_MAX)
			return (false);
		dat->eat_num = tmp;
	}
	else
		dat->eat_num = -1;
	return (true);
}

static bool	valid_input(int argc, char **argv, t_data *dat)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!all_nums(argv[i]))
			return (ret_msg("non-number in args", false));
		i++;
	}
	if (!assign_num(argc, argv, dat))
		return (ret_msg("number out of bounds", false));
	return (true);
}

bool	parse_input(int argc, char **argv, t_data *dat)
{
	if (argc != 5 && argc != 6)
		return (ret_msg("Usage: ./philo num ttd tte tts ttenum", false));
	if (!valid_input(argc, argv, dat))
		return (false);
	return (true);
}
