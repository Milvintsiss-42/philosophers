/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 20:38:02 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/21 20:14:22 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettimestamp(t_exec_data exec_data)
{
	struct timeval	tv;	

	if (gettimeofday(&tv, 0) == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000
			- exec_data.init_timestamp);
	else
		return (exec_data.init_timestamp);
}

void	log_action(t_exec_data exec_data, int philo_id, char *action)
{
	printf("%ld %d %s\n", gettimestamp(exec_data), philo_id + 1, action);
}
