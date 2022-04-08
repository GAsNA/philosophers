/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:31:34 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/07 17:39:15 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ate_enough(t_philo *philos)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philos[0].infos->mutex_ate);
	while (++i < philos[0].infos->nb_philos)
	{
		pthread_mutex_lock(&philos[0].infos->mutex);
		if (philos[i].run && philos[i].nb_eat == philos[0].infos->nb_eat)
		{
			philos[i].run = 0;
			pthread_mutex_unlock(&philos[0].infos->mutex);
			pthread_mutex_unlock(&philos[0].infos->mutex_ate);
			return (1);
		}
		pthread_mutex_unlock(&philos[0].infos->mutex);
	}
	pthread_mutex_unlock(&philos[0].infos->mutex_ate);
	return (0);
}

int	is_dead(t_philo *philos)
{
	int	i;
	int	j;

	i = -1;
	pthread_mutex_lock(&philos[0].infos->mutex_dead);
	while (++i < philos[0].infos->nb_philos)
	{
		if (philos[i].run && calcul_ms() - philos[i].eat_time
			>= philos[0].infos->ms_die)
		{
			msg_dead(calcul_ms(), philos[i].index, &philos[i]);
			philos[i].dead = 1;
			pthread_mutex_lock(&philos[0].infos->mutex);
			j = -1;
			while (++j < philos[0].infos->nb_philos)
				philos[j].run = 0;
			pthread_mutex_unlock(&philos[0].infos->mutex);
			pthread_mutex_unlock(&philos[0].infos->mutex_dead);
			return (1);
		}
	}
	pthread_mutex_unlock(&philos[0].infos->mutex_dead);
	return (0);
}

int	one_is_good(t_philo *philos)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (++i < philos[0].infos->nb_philos)
	{
		if (philos[i].run)
			ret = 1;
		if (philos[i].dead)
			return (0);
	}
	return (ret);
}
