/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:24:03 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 18:19:48 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	philo_proccess(t_philo *philo)
{
	int	is_first_iteration;

	is_first_iteration = 1;
	if (KDEBUG)
		log_action(*philo, ACT_IS_BORN);
	if (philo->id % 2)
		usleep(philo->exec_data->t_to_eat * 1000 - 1000);
	while (1)
	{
		if (!is_first_iteration)
			while (gettimestamp(*philo->exec_data) - philo->t_last_meal
				< philo->exec_data->t_to_die * 2 / 3)
				die_if_have_to(philo, 0);
		is_first_iteration = 0;
		eat(philo);
	}
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
		exec_data->philos[i].have_exited = 0;
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
