/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:55:24 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 13:41:54 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	kill_philosophers(t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
	{
		kill(exec_data->philos[i].pid, SIGKILL);
	}
}

void	monitoring(t_exec_data *exec_data)
{
	int		i;
	t_philo	*philo;

	while (exec_data->err_no == 0)
	{
		i = -1;
		while (++i < exec_data->nb_philo)
		{
			philo = exec_data->philos + i;
			if (gettimestamp(*exec_data) - philo->t_last_meal
				> exec_data->t_to_die)
			{
				log_action(*philo, ACT_DIED);
				kill_philosophers(exec_data);
				return ;
			}
		}
	}
}
