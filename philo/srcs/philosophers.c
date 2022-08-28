/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:19 by ple-stra          #+#    #+#             */
/*   Updated: 2022/08/28 21:35:42 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_exec_data(t_exec_data *exec_data, int argc, char const **argv)
{
	if (argc < 5 || argc > 6)
		exit(ft_perror(ERR_WRG_NB_ARG, -1));
	exec_data->nb_philo = get_input(argv[1]);
	exec_data->t_to_die = get_input(argv[2]);
	exec_data->t_to_eat = get_input(argv[3]);
	exec_data->t_to_sleep = get_input(argv[4]);
	if (argc == 6)
		exec_data->nb_of_dinners = get_input(argv[5]);
	else
		exec_data->nb_of_dinners = INTMAX;
	if (exec_data->nb_philo == -1 || exec_data->t_to_die == -1
		|| exec_data->t_to_eat == -1 || exec_data->t_to_sleep == -1
		|| exec_data->nb_of_dinners == -1)
		exit(ft_perror(ERR_WRG_ARG, -1));
}

int	main(int argc, char const **argv)
{
	t_exec_data	exec_data;

	init_exec_data(&exec_data, argc, argv);
	return (0);
}
