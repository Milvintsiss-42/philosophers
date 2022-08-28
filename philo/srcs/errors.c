/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:09:54 by ple-stra          #+#    #+#             */
/*   Updated: 2022/08/28 21:19:14 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_perror_errno(void)
{
	return (ft_perror(strerror(errno), errno));
}

int	ft_perror(char *str, int err)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	if (err != 0)
		return (err);
	return (-1);
}
