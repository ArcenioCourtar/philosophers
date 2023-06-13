/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:53:18 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/13 14:56:59 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

u_int64_t	my_gettime(void)
{
	struct timeval	newtime;

	gettimeofday(&newtime, NULL);
	return (newtime.tv_sec * 1000000 + newtime.tv_usec);
}
