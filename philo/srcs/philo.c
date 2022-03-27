/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:15:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/03/27 18:39:16 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static long	calcul_ms(void)
{
	static long	start = 0;

	if (!start)
		start = get_time();
	return (get_time() - start);
}

static void	sleep(t_philo *philo)
{
	msg_sleep(calcul_ms(), philo->index);
	usleep(philo->infos->ms_sleep * 1000);
	philo->state = "think";
}

static void	think(t_philo *philo)
{
	msg_think(calcul_ms(), philo->index);
	// take fork
	philo->state = "eat";
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	//msg take fork or eat
	philo->nb_eat++;
	philo->eat_start = calcul_ms();
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->infos->ms_eat * 1000);
	// free fork
	philo->state = "sleep";
}

static void	*routine(void *p_data)
{
	t_philo			*philo;

	philo = (t_philo *)p_data;
	while (1) // STATE GLOBAL RUN ?
	{
		if (ft_strcmp(philo->state, "sleep") == 0)
			sleep(philo);
		else if (ft_strcmp(philo->state, "think") == 0)
			think(philo);
		else if (ft_strcmp(philo->state, "eat") == 0)
			eat(philo);
	}
	return (0);
}

// eat -> sleep -> think -> ...
void	philo(t_infos infos)
{
	int		i;
	int		j;
	t_philo	*philos;

	philos = malloc(infos.nb_philos * sizeof(t_philo));
	if (!philos)
		error_occured();
	pthread_mutex_init(&infos.mutex, NULL);
	pthread_mutex_lock(&infos.mutex);
	i = -1;
	while (++i < infos.nb_philos)
	{
		philos[i].index = i + 1;
		philos[i].nb_eat = 0;
		philos[i].eat_start = 0;
		pthread_mutex_init(&philos[i].mutex, NULL);
		philos[i].state = "sleep";
		philos[i].fork.id_o = -1;
		philos[i].fork.used = 0;
		pthread_mutex_init(&philos[i].fork.mutex, NULL);	
		philos[i].infos = &infos;
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			error_occured();
	}
	pthread_mutex_unlock(&infos.mutex);
	//**********************************
	// Test if dead and ate too much
	//**********************************
	j = -1;
	while (++j < infos.nb_philos)
		if (pthread_join(philos[j].thread, NULL))
			error_occured();
	pthread_mutex_destroy(&infos.mutex);
}
