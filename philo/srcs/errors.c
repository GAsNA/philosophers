/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:30:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/08 14:23:17 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(void)
{
	printf("Error\n");
}

void	error_nb_args(void)
{
	error();
	printf("The number of arguments have to be between 4 and 5.\n");
	printf("USE: ./philo [number_of_philosophers] [time_to_die] [time_to_eat]\
 [time_to_sleep] (number_of_times_each_philosopher_must_eat)\n");
	exit(1);
}

void	error_args(void)
{
	error();
	printf("The arguments need to be not null positive integer.\n");
	exit(1);
}

void	error_occured(void)
{
	printf("An error has occured.\n");
	exit(0);
}
