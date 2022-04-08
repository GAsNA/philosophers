/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:08:22 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/08 14:18:30 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_infos	infos;

	if (ac < 5 || ac > 6)
		error_nb_args();
	if (!are_valid_args(av))
		error_args();
	infos.nb_philos = ft_atoi(av[1]);
	infos.ms_die = ft_atoi(av[2]);
	infos.ms_eat = ft_atoi(av[3]);
	infos.ms_sleep = ft_atoi(av[4]);
	infos.nb_eat = -1;
	if (ac == 6)
		infos.nb_eat = ft_atoi(av[5]);
	philo(infos);
	return (0);
}
