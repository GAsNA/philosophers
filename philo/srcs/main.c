/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:08:22 by rleseur           #+#    #+#             */
/*   Updated: 2022/03/27 20:13:15 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_infos	infos;

	if (ac < 5 || ac > 6 || !are_valid_args(av))
		error_args();
	infos.nb_philos = ft_atoi(av[1]);
	infos.ms_die = ft_atoi(av[2]);
	infos.ms_eat = ft_atoi(av[3]);
	infos.ms_sleep = ft_atoi(av[4]);
	infos.nb_eat = -1;
	if (ac == 6)
		infos.nb_eat = ft_atoi(av[5]);
	pthread_mutex_init(&infos.mutex, NULL);
	philo(infos);
	pthread_mutex_destroy(&infos.mutex);
	return (0);
}
