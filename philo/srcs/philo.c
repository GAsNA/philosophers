/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:15:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/03/30 14:37:02 by rleseur          ###   ########.fr       */
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

static int	ate_enough(t_philo *philos)
{
	int	i;

	i = -1;
	//pthread_mutex_lock(&philos[0].infos->mutex);	
	while (++i < philos[0].infos->nb_philos)
	{
		if (philos[i].run && philos[i].nb_eat == philos[0].infos->nb_eat)
		{
			philos[i].run = 0;
			//pthread_mutex_unlock(&philos[0].infos->mutex);	
			return (1);
		}
	}
	//pthread_mutex_unlock(&philos[0].infos->mutex);	
	return (0);
}

static int	is_dead(t_philo *philos)
{
	int	i;

	i = -1;
	//pthread_mutex_lock(&philos[0].infos->mutex);	
	while (++i < philos[0].infos->nb_philos)
	{
		if (philos[i].run && calcul_ms(philos[0].infos) - philos[i].eat_time >= philos[0].infos->ms_die)
		{
			msg_dead(calcul_ms(philos[0].infos), philos[i].index);
			philos[i].run = 0;
		//	pthread_mutex_unlock(&philos[0].infos->mutex);
			return (1);
		}
	}
	//pthread_mutex_unlock(&philos[0].infos->mutex);	
	return (0);
}

static int	one_is_good(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].infos->nb_philos)
		if (philos[i].run)
			return (1);
	return (0);
}

static int	get_sleep(t_philo *philo)
{
	if(!philo->run)
		return (0);
	msg_sleep(calcul_ms(philo->infos), philo->index);
	usleep(philo->infos->ms_sleep * 1000);
	philo->state = "think";
	if (!philo->run)
		return (0);
	return (1);
}

static int	get_think(t_philo *philo)
{
	if (!philo->run)
		return (0);
	msg_think(calcul_ms(philo->infos), philo->index);
	philo->state = "eat";
	if (!philo->run)
		return (0);
	return (1);
}

static int	get_eat(t_philo *philo)
{
	if (!philo->run)
		return (0);
	pthread_mutex_lock(&philo->mutex);	
	// take fork
	msg_take(calcul_ms(philo->infos), philo->index);
	msg_take(calcul_ms(philo->infos), philo->index);
	msg_eat(calcul_ms(philo->infos), philo->index);
	philo->nb_eat++;
	philo->eat_time = calcul_ms(philo->infos);
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->infos->ms_eat * 1000);
	// free fork
	philo->state = "sleep";
	return (1);
}

static void	*routine(void *p_data)
{
	t_philo			*philo;

	philo = (t_philo *)p_data;
	while (1)
	{
		if (ft_strcpm(philo->state, "sleep") == 0)
		{
			if (!get_sleep(philo))
				break;
		}
		else if (ft_strcpm(philo->state, "think") == 0)
		{
			if (!get_think(philo))
				break;
		}
		else if (ft_strcpm(philo->state, "eat") == 0)
			if(!get_eat(philo))
				break;
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
		philos[i].eat_time = 0;
		philos[i].run = 1;
		pthread_mutex_init(&philos[i].mutex, NULL);
		philos[i].state = "eat";
		philos[i].fork.id_o = -1;
		philos[i].fork.used = 0;
		pthread_mutex_init(&philos[i].fork.mutex, NULL);
		philos[i].infos = &infos;
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			error_occured();
	}
	pthread_mutex_unlock(&infos.mutex);
	while ((!ate_enough(philos) && !is_dead(philos)) || one_is_good(philos))
		usleep(100);
	j = -1;
	while (++j < infos.nb_philos)
		if (pthread_join(philos[j].thread, NULL))
			error_occured();
	pthread_mutex_destroy(&infos.mutex);
}
