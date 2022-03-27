/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:30:38 by rleseur           #+#    #+#             */
/*   Updated: 2022/03/17 10:46:11 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(void)
{
	printf("Error\n");
}

void	error_args(void)
{
	error();
	printf("The number of arguments have to be between 4 and 5.\n");
	printf("They need to be not null positif integer.\n");
	exit(1);
}

void	error_occured(void)
{
	printf("An error has occured.\n");
	exit(0);
}
