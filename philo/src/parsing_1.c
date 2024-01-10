/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 15:51:26 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:13:36 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Check if all characters given as arguments are numbers.
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

// If the input are all non-negative numbers, checks if they're within bounds.
// TODO: make smol
static bool	assign_num(int argc, char **argv, t_data *dat)
{
	int			i;
	unsigned long long	tmp;

	i = 1;
	tmp = ft_atol(argv[i]);
	if (tmp > INT_MAX || tmp == 0)
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
		dat->noe = tmp;
	}
	else
		dat->noe = -1;
	return (true);
}

// Check whether te input is valid
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

// Parse the input given by the user
bool	parse_input(int argc, char **argv, t_data *dat)
{
	if (argc != 5 && argc != 6)
		return (ret_msg("Usage: ./philo num ttd tte tts tte_num", false));
	if (!valid_input(argc, argv, dat))
		return (false);
	return (true);
}
