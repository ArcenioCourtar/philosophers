/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debugfunc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 16:47:16 by acourtar      #+#    #+#                 */
/*   Updated: 2023/07/10 16:54:56 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	debug_dat_cont(t_data *dat)
{
	printf("num: %i, ttd: %llu, tte: %llu, tts: %llu, tte_num: %i\n", \
	dat->num, dat->ttd, dat->tte, dat->tts, dat->eat_num);
}
