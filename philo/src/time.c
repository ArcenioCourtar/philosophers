/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:53:18 by acourtar          #+#    #+#             */
/*   Updated: 2023/06/13 16:37:18 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

u_int64_t	my_gettime(void)
{
	struct timeval	newtime;

	if (gettimeofday(&newtime, NULL) != 0)
		return (0);
	return (newtime.tv_sec * 1000000 + newtime.tv_usec);
}
