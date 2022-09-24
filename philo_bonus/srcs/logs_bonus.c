/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:23:26 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/24 15:23:30 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	gettimestamp(t_exec_data exec_data)
{
	struct timeval	tv;	

	if (gettimeofday(&tv, 0) == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000
			- exec_data.init_timestamp);
	else
		return (exec_data.init_timestamp);
}

void	log_action(t_philo philo, char *action)
{
	printf("%.8ld %d %s\n",
		gettimestamp(*philo.exec_data), philo.id + 1, action);
}
