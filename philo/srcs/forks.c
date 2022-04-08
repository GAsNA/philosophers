/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:25:16 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/07 17:46:54 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	first_fork(t_philo *p1, t_philo *philo, t_philo *next)
{
	pthread_mutex_lock(&p1->fork.mutex);
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		pthread_mutex_unlock(&p1->fork.mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	msg_take(calcul_ms(), philo->index, philo);
	if (next->index == philo->index)
	{
		pthread_mutex_unlock(&p1->fork.mutex);
		return (0);
	}
	return (1);
}

int	second_fork(t_philo *p1, t_philo *p2, t_philo *philo)
{
	pthread_mutex_lock(&p2->fork.mutex);
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		pthread_mutex_unlock(&p1->fork.mutex);
		pthread_mutex_unlock(&p2->fork.mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	msg_take(calcul_ms(), philo->index, philo);
	return (1);
}

int	take_fork(t_philo *philo)
{
	int		id;
	t_philo	*next;
	t_philo	*p1;
	t_philo	*p2;

	id = 0;
	if (philo->index != philo->infos->nb_philos)
		id = philo->index;
	next = &philo->infos->philos[id];
	p1 = philo;
	p2 = next;
	if (id == 0)
	{
		p1 = next;
		p2 = philo;
	}
	if (!first_fork(p1, philo, next))
		return (0);
	if (!second_fork(p1, p2, philo))
		return (0);
	return (1);
}

void	free_fork(t_philo *philo)
{
	int		id;
	t_philo	*next;

	id = 0;
	if (philo->index != philo->infos->nb_philos)
		id = philo->index;
	next = &philo->infos->philos[id];
	pthread_mutex_unlock(&philo->fork.mutex);
	pthread_mutex_unlock(&next->fork.mutex);
}
