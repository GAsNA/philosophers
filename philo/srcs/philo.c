/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:15:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/05 15:33:33 by rleseur          ###   ########.fr       */
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

static int	is_dead(t_philo *philos)
{
	int	i;
	int	j;

	i = -1;
	pthread_mutex_lock(&philos[0].infos->mutex_dead);
	while (++i < philos[0].infos->nb_philos)
	{
		if (philos[i].run && calcul_ms(philos[0].infos) - philos[i].eat_time
			>= philos[0].infos->ms_die)
		{
			msg_dead(calcul_ms(philos[0].infos), philos[i].index);
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

static int	one_is_good(t_philo *philos)
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

static int	get_sleep(t_philo *philo)
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

static int	get_think(t_philo *philo)
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

static int	take_fork(t_philo *philo)
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
	pthread_mutex_lock(&p1->fork.mutex);
	pthread_mutex_lock(&philo->infos->mutex);
	if (!philo->run)
	{
		pthread_mutex_unlock(&philo->infos->mutex);
		pthread_mutex_unlock(&p1->fork.mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->infos->mutex);
	msg_take(calcul_ms(philo->infos), philo->index);
	if (next->index == philo->index)
	{
		pthread_mutex_unlock(&p1->fork.mutex);
		return (0);
	}
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
	msg_take(calcul_ms(philo->infos), philo->index);
	return (1);
}

static void	free_fork(t_philo *philo)
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

static int	get_eat(t_philo *philo)
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

static void	*routine(void *p_data)
{
	t_philo			*philo;

	philo = (t_philo *)p_data;
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

void	philo(t_infos infos)
{
	int		i;
	int		j;
	int		k;
	t_philo	*philos;

	philos = malloc(infos.nb_philos * sizeof(t_philo));
	if (!philos)
		error_occured();
	pthread_mutex_init(&infos.mutex, NULL);
	pthread_mutex_init(&infos.mutex_ate, NULL);
	pthread_mutex_init(&infos.mutex_dead, NULL);
	infos.ms_start = get_time();
	infos.philos = philos;
	i = -1;
	while (++i < infos.nb_philos)
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
		philos[i].infos = &infos;
	}
	i = -1;
	while (++i < infos.nb_philos)
	{
		usleep(100);
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			error_occured();
	}
	while ((!ate_enough(philos) && !is_dead(philos)) || one_is_good(philos))
		usleep(100);
	j = -1;
	while (++j < infos.nb_philos)
		if (pthread_join(philos[j].thread, NULL))
			error_occured();
	pthread_mutex_destroy(&infos.mutex);
	k = -1;
	while (++k < infos.nb_philos)
		pthread_mutex_destroy(&philos[k].fork.mutex);
}
