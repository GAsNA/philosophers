/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:15:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/06 11:33:45 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *p_data)
{
	t_philo			*philo;

	philo = (t_philo *)p_data;
	if (philo->nb_eat == philo->infos->nb_eat)
		return (0);
	while (1)
	{
		if (ft_strcmp(philo->state, "sleep") == 0)
		{
			if (!get_sleep(philo))
				break ;
		}
		else if (ft_strcmp(philo->state, "think") == 0)
		{
			if (!get_think(philo))
				break ;
		}
		else if (ft_strcmp(philo->state, "eat") == 0)
			if (!get_eat(philo))
				break ;
	}
	return (0);
}

static void	init(t_infos *infos, t_philo *philos)
{
	int	i;

	pthread_mutex_init(&infos->mutex, NULL);
	pthread_mutex_init(&infos->mutex_ate, NULL);
	pthread_mutex_init(&infos->mutex_dead, NULL);
	infos->ms_start = get_time();
	infos->philos = philos;
	i = -1;
	while (++i < infos->nb_philos)
	{
		philos[i].index = i + 1;
		philos[i].nb_eat = 0;
		philos[i].eat_time = 0;
		philos[i].run = 1;
		philos[i].dead = 0;
		pthread_mutex_init(&philos[i].mutex, NULL);
		philos[i].state = "eat";
		philos[i].fork.id = -1;
		philos[i].fork.used = 0;
		pthread_mutex_init(&philos[i].fork.mutex, NULL);
		philos[i].infos = infos;
	}
}

void	philo(t_infos infos)
{
	int		i;
	t_philo	*philos;

	philos = malloc(infos.nb_philos * sizeof(t_philo));
	if (!philos)
		error_occured();
	init(&infos, philos);
	i = -1;
	while (++i < infos.nb_philos)
	{
		usleep(100);
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			error_occured();
	}
	while ((!ate_enough(philos) && !is_dead(philos)) || one_is_good(philos))
		usleep(100);
	i = -1;
	while (++i < infos.nb_philos)
		if (pthread_join(philos[i].thread, NULL))
			error_occured();
	pthread_mutex_destroy(&infos.mutex);
	i = -1;
	while (++i < infos.nb_philos)
		pthread_mutex_destroy(&philos[i].fork.mutex);
	free(philos);
}
