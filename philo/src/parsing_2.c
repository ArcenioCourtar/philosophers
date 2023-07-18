/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/13 15:51:41 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/18 14:13:24 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\f')
		return (1);
	if (c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	number;
	int		is_negative;

	number = 0;
	is_negative = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			is_negative = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number *= 10;
		number += *str - '0';
		str++;
	}
	if (is_negative == 1)
		number *= -1;
	return (number);
}
