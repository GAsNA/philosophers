/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:27:18 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/06 11:29:39 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	msg_sleep(calcul_ms(philo->infos), philo->index);
	usleep(philo->infos->ms_sleep * 1000);
	philo->state = "think";
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	return (1);
}

int	get_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	msg_think(calcul_ms(philo->infos), philo->index);
	philo->state = "eat";
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	return (1);
}

int	get_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	if (!take_fork(philo))
		return (0);
	msg_eat(calcul_ms(philo->infos), philo->index);
	pthread_mutex_lock(&philo->infos->mutex_ate);
	philo->nb_eat++;
	pthread_mutex_lock(&philo->infos->mutex_dead);
	philo->eat_time = calcul_ms(philo->infos);
	pthread_mutex_unlock(&philo->infos->mutex_dead);
	pthread_mutex_unlock(&philo->infos->mutex_ate);
	usleep(philo->infos->ms_eat * 1000);
	free_fork(philo);
	philo->state = "sleep";
	return (1);
}
