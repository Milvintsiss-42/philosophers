/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milvintsiss <milvintsiss@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:19 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/11 23:03:33 by milvintsiss      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_exec_data(t_exec_data *exec_data, int argc, char const **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_perror(ERR_WRG_NB_ARG, -1));
	exec_data->nb_philo = get_input(argv[1]);
	exec_data->t_to_die = get_input(argv[2]);
	exec_data->t_to_eat = get_input(argv[3]);
	exec_data->t_to_sleep = get_input(argv[4]);
	if (argc == 6)
		exec_data->nb_of_dinners = get_input(argv[5]);
	else
		exec_data->nb_of_dinners = INTMAX;
	if (exec_data->nb_philo <= 0 || exec_data->t_to_die == -1
		|| exec_data->t_to_eat == -1 || exec_data->t_to_sleep == -1
		|| exec_data->nb_of_dinners == -1)
		return (ft_perror(ERR_WRG_ARG, -1));
	exec_data->init_timestamp = 0;
	exec_data->init_timestamp = gettimestamp(*exec_data);
	return (0);
}

int	main(int argc, char const **argv)
{
	t_exec_data	exec_data;

	if (init_exec_data(&exec_data, argc, argv) == -1)
		return (-1);
	return (0);
}
