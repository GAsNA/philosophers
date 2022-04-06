/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:50:03 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/06 09:47:19 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	all_digits(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (0);
	}
	return (1);
}

static int	all_not_null(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (!av[i][0])
			return (0);
	}
	return (1);
}

static int	all_not_overflow_or_zero(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (ft_atoll(av[i]) > 2147483647)
			return (0);
		if (ft_atoi(av[i]) == 0 && i != 5)
			return (0);
	}
	return (1);
}

int	are_valid_args(char **av)
{
	if (!all_not_null(av) || !all_digits(av) || !all_not_overflow_or_zero(av))
		return (0);
	return (1);
}
