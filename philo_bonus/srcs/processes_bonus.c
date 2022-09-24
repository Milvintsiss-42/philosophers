/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:24:03 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/24 15:24:09 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	launch_philo_processes(t_exec_data *exec_data)
{
	int	i;

	exec_data->philos = malloc(sizeof(t_philo) * exec_data->nb_philo);
	if (!exec_data->philos)
		return (ft_perror(exec_data, ERR_UNKNOWN, 6));
	i = -1;
	while (++i < exec_data->nb_philo)
	{
		exec_data->philos[i].id = i;
		exec_data->philos[i].exec_data = exec_data;
		exec_data->philos[i].nb_of_dinners_eat = 0;
		exec_data->philos[i].t_last_meal = 0;
		// TODO: Create process
	}
	return (1);
}

// TODO
int	wait_for_philo_processes(t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
		; // TODO: wait for processes
	return (0);
}
