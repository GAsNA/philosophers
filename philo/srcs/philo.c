/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:15:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/03/28 11:52:21 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static long	calcul_ms(t_infos *infos)
{
	return (get_time() - infos->ms_start);
}

static void	get_sleep(t_philo *philo)
{
	msg_sleep(calcul_ms(philo->infos), philo->index);
	usleep(philo->infos->ms_sleep * 1000);
	philo->state = "think";
}

static void	get_think(t_philo *philo)
{
	msg_think(calcul_ms(philo->infos), philo->index);
	// take fork
	philo->state = "eat";
}

static void	get_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	//msg take fork
	msg_eat(calcul_ms(philo->infos), philo->index);
	philo->nb_eat++;
	philo->eat_start = calcul_ms(philo->infos);
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
		if (ft_strcpm(philo->state, "sleep") == 0)
			get_sleep(philo);
		else if (ft_strcpm(philo->state, "think") == 0)
			get_think(philo);
		else if (ft_strcpm(philo->state, "eat") == 0)
			get_eat(philo);
	}
	return (0);
}

// eat -> sleep -> think -> ...
void	philo(t_infos infos)
{
	int		i;
	int		j;
	t_philo	*philos;

	msg_take(804, 1);
	msg_eat(infos.ms_eat, 1);
	msg_sleep(infos.ms_sleep, 1);
	msg_think(804, 1);
	msg_dead(infos.ms_die, 1);
	printf("--------- START ---------\n");
	philos = malloc(infos.nb_philos * sizeof(t_philo));
	if (!philos)
		error_occured();
	pthread_mutex_init(&infos.mutex, NULL);
	pthread_mutex_lock(&infos.mutex);
	infos.ms_start = get_time();
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
