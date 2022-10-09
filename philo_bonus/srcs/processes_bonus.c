/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:24:03 by ple-stra          #+#    #+#             */
/*   Updated: 2022/10/09 23:40:29 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philo_proccess(t_philo *philo)
{
	if (KDEBUG)
		log_action(*philo, ACT_IS_BORN);
	return (0);
}

int	launch_philo_processes(t_exec_data *exec_data)
{
	int	i;
	int	pid;

	exec_data->philos = malloc(sizeof(t_philo) * exec_data->nb_philo);
	if (!exec_data->philos)
		return (ft_perror(exec_data, ERR_UNKNOWN, 4));
	i = -1;
	while (++i < exec_data->nb_philo)
	{
		exec_data->philos[i].id = i;
		exec_data->philos[i].pid = 0;
		exec_data->philos[i].exec_data = exec_data;
		exec_data->philos[i].nb_of_dinners_eat = 0;
		exec_data->philos[i].t_last_meal = 0;
		pid = fork();
		if (pid == -1)
			return (ft_perror(exec_data, ERR_UNKNOWN, 5));
		if (pid == 0)
			return (philo_proccess(&exec_data->philos[i]));
		if (pid != 0)
			exec_data->philos[i].pid = pid;
	}
	return (1);
}

// TODO
int	wait_for_philo_processes(t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
		if (waitpid(exec_data->philos[i].pid, NULL, 0) == -1)
			return (ft_perror(exec_data, ERR_UNKNOWN, 6));
	return (1);
}
