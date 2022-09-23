/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:39:42 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/23 18:53:29 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitoring(t_exec_data *exec_data)
{
	int	i;

	while (exec_data->err_no == 0)
	{
		i = -1;
		while (++i < exec_data->nb_philo)
		{
			if (gettimestamp(*exec_data) - exec_data->philos[i].t_last_meal
				> exec_data->t_to_die)
			{
				if (pthread_mutex_lock(&exec_data->mutex_one_philo_died) != 0)
					return (ft_perror(exec_data, ERR_UNKNOWN, 9));
				exec_data->one_philo_died = 1;
				pthread_mutex_unlock(&exec_data->mutex_one_philo_died);
				return (1);
			}
		}
	}
	return (1);
}
