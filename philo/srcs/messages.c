/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleseur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 11:51:05 by rleseur           #+#    #+#             */
/*   Updated: 2022/04/06 15:12:28 by rleseur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	msg_dead(int ms, int index)
{
	printf("%s%i\t%i\t%s%s\n", _RED, ms, index, "died", _END);
}

void	msg_think(int ms, int index)
{
	printf("%s%i\t%i\t%s%s\n", _PURPLE, ms, index, "is thinking", _END);
}

void	msg_sleep(int ms, int index)
{
	printf("%s%i\t%i\t%s%s\n", _BLUE, ms, index, "is sleeping", _END);
}

void	msg_eat(int ms, int index)
{
	printf("%s%i\t%i\t%s%s\n", _GREEN, ms, index, "is eating", _END);
}

void	msg_take(int ms, int index)
{
	printf("%s%i\t%i\t%s%s\n", _YELLOW, ms, index, "has taken a fork", _END);
}
