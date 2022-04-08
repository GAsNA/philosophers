/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:33:53 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/08 09:28:47 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	calcul_ms(void)
{
	static long	start;

	if (!start)
		start = get_time();
	return (get_time() - start);
}

static long	get_time_micro(struct timeval *start_time)
{
	struct timeval	current;
	long			time;

	gettimeofday(&current, NULL);
	time = (((current.tv_sec - start_time->tv_sec) * 1000000)
			+ (current.tv_usec - start_time->tv_usec));
	return (time);
}

void	ft_usleep(long wait)
{
	struct timeval	time;

	if (wait <= 0)
		return ;
	gettimeofday(&time, NULL);
	while (get_time_micro(&time) < wait)
		usleep(500); // 100 !!!
}
