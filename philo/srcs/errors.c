/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 21:09:54 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/15 01:16:14 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_perror(t_exec_data *exec_data, char *str, int err)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	if (err != 0)
		exec_data->err_no = err;
	else
		exec_data->err_no = 1;
	return (0);
}

void	cleanup_mutexs(t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
		pthread_mutex_destroy(&exec_data->forks[i]);
	free(exec_data->forks);
}

int	ft_exit(t_exec_data *exec_data)
{
	cleanup_mutexs(exec_data);
	return (exec_data->err_no);
}
