/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:49:59 by ple-stra          #+#    #+#             */
/*   Updated: 2022/08/28 21:34:16 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_int(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '\0')
		return (0);
	while (*str && *str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

static int	custom_atoi(const char *nptr)
{
	int	nb;
	int	nb_prec;
	int	neg;

	nb = 0;
	neg = 1 - (2 * (*nptr == '-'));
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		nb_prec = nb;
		nb = nb * 10 + (*(nptr++) - '0') * neg;
		if ((nb_prec > nb && neg == 1) || (nb_prec < nb && neg == -1))
			return (-1 * neg);
	}
	return (nb);
}

int	get_input(const char *str)
{
	if (!is_int(str) || *str == '-')
		return (-1);
	return (custom_atoi(str));
}

size_t	ft_strlen(char *str)
{
	char	*start;

	start = str;
	if (!str)
		return (0);
	while (*str++)
		;
	return (str - start);
}
