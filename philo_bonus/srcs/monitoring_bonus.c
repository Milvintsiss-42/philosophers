/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:55:24 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 20:54:48 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	do_all_philos_have_exited(t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
	{
		if (exec_data->philos[i].have_exited == 0)
			return (0);
	}
	return (1);
}

static t_philo	*get_philo_by_pid(pid_t pid, t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
		if (exec_data->philos[i].pid == pid)
			return (&exec_data->philos[i]);
	return (0);
}

static void	kill_all_philosophers(t_exec_data *exec_data)
{
	int		i;

	i = -1;
	while (++i < exec_data->nb_philo)
	{
		if (!exec_data->philos[i].have_exited)
			kill(exec_data->philos[i].pid, SIGKILL);
	}
}

void	monitoring(t_exec_data *exec_data)
{
	pid_t	exited_process_pid;
	int		wstatus;

	exited_process_pid = waitpid(-1, &wstatus, 0);
	if (exited_process_pid == -1)
	{
		ft_perror(exec_data, ERR_UNKNOWN, 9);
		exit(ft_exit(exec_data, 1));
	}
	get_philo_by_pid(exited_process_pid, exec_data)->have_exited = 1;
	if (WEXITSTATUS(wstatus) == 0 && !do_all_philos_have_exited(exec_data))
		monitoring(exec_data);
	else if (WEXITSTATUS(wstatus) != 0)
		kill_all_philosophers(exec_data);
}
