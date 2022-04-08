/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:51:05 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/07 17:51:49 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	msg_dead(int ms, int index, t_philo *philo)
{
	(void) philo;
	pthread_mutex_lock(&philo->infos->mutex_w);
	pthread_mutex_lock(&philo->infos->mutex);
	if (philo->run)
		printf("%s%i\t%i\t%s%s\n", _RED, ms, index, "died", _END);
	pthread_mutex_unlock(&philo->infos->mutex);
	pthread_mutex_unlock(&philo->infos->mutex_w);
}

void	msg_think(int ms, int index, t_philo *philo)
{
	(void) philo;
	pthread_mutex_lock(&philo->infos->mutex_w);
	pthread_mutex_lock(&philo->infos->mutex);
	if (philo->run)
		printf("%s%i\t%i\t%s%s\n", _PURPLE, ms, index, "is thinking", _END);
	pthread_mutex_unlock(&philo->infos->mutex);
	pthread_mutex_unlock(&philo->infos->mutex_w);
}

void	msg_sleep(int ms, int index, t_philo *philo)
{
	(void) philo;
	pthread_mutex_lock(&philo->infos->mutex_w);
	pthread_mutex_lock(&philo->infos->mutex);
	if (philo->run)
		printf("%s%i\t%i\t%s%s\n", _BLUE, ms, index, "is sleeping", _END);
	pthread_mutex_unlock(&philo->infos->mutex);
	pthread_mutex_unlock(&philo->infos->mutex_w);
}

void	msg_eat(int ms, int index, t_philo *philo)
{
	(void) philo;
	pthread_mutex_lock(&philo->infos->mutex_w);
	pthread_mutex_lock(&philo->infos->mutex);
	if (philo->run)
		printf("%s%i\t%i\t%s%s\n", _GREEN, ms, index, "is eating", _END);
	pthread_mutex_unlock(&philo->infos->mutex);
	pthread_mutex_unlock(&philo->infos->mutex_w);
}

void	msg_take(int ms, int index, t_philo *philo)
{
	(void) philo;
	pthread_mutex_lock(&philo->infos->mutex_w);
	pthread_mutex_lock(&philo->infos->mutex);
	if (philo->run)
		printf("%s%i\t%i\t%s%s\n", _YELLOW, ms, index, "has taken a fork", _END);
	pthread_mutex_unlock(&philo->infos->mutex);
	pthread_mutex_unlock(&philo->infos->mutex_w);
}
