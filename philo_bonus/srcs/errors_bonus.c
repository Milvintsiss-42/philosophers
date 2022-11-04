/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 15:23:34 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 20:56:42 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

int	ft_exit(t_exec_data *exec_data, int from_child)
{
	free(exec_data->philos);
	if (!from_child && exec_data->forks != 0)
	{
		if (sem_close(exec_data->forks) == -1
			|| sem_unlink(SEM_FORKS_NAME) == -1)
			exec_data->err_no = 99;
	}
	return (exec_data->err_no);
}
