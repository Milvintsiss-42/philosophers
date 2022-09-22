/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:19 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/22 14:11:07 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_exec_data(t_exec_data *exec_data, int argc, char const **argv)
{
	exec_data->err_no = 0;
	exec_data->one_philo_died = 0;
	exec_data->forks = 0;
	exec_data->philos = 0;
	if (argc < 5 || argc > 6)
		return (ft_perror(exec_data, ERR_WRG_NB_ARG, 2));
	exec_data->nb_philo = get_input(argv[1]);
	exec_data->t_to_die = get_input(argv[2]);
	exec_data->t_to_eat = get_input(argv[3]);
	exec_data->t_to_sleep = get_input(argv[4]);
	if (argc == 6)
		exec_data->nb_of_dinners = get_input(argv[5]);
	else
		exec_data->nb_of_dinners = INTMAX;
	if (exec_data->nb_philo <= 0 || exec_data->t_to_die * 1000 < 0
		|| exec_data->t_to_eat * 1000 < 0 || exec_data->t_to_sleep * 1000 < 0
		|| exec_data->nb_of_dinners == -1)
		return (ft_perror(exec_data, ERR_WRG_ARG, 3));
	exec_data->t_to_think = 1;
	if (exec_data->t_to_eat > exec_data->t_to_sleep)
		exec_data->t_to_think += exec_data->t_to_eat - exec_data->t_to_sleep;
	exec_data->init_timestamp = 0;
	exec_data->init_timestamp = gettimestamp(*exec_data);
	return (1);
}

static int	init_mutexs(t_exec_data *exec_data)
{
	int	i;

	exec_data->forks = malloc(sizeof(pthread_mutex_t) * exec_data->nb_philo);
	if (!exec_data->forks)
		return (ft_perror(exec_data, ERR_UNKNOWN, 4));
	i = -1;
	while (++i < exec_data->nb_philo)
		if (pthread_mutex_init(&exec_data->forks[i], NULL) != 0)
			return (ft_perror(exec_data, ERR_UNKNOWN, 5));
	if (pthread_mutex_init(&exec_data->mutex_one_philo_died, NULL) != 0)
		return (ft_perror(exec_data, ERR_UNKNOWN, 8));
	return (1);
}

int	main(int argc, char const **argv)
{
	t_exec_data	exec_data;

	if (!init_exec_data(&exec_data, argc, argv))
		return (ft_exit(&exec_data));
	if (!init_mutexs(&exec_data))
		return (ft_exit(&exec_data));
	if (!launch_philo_routines(&exec_data))
		return (ft_exit(&exec_data));
	if (!wait_for_philo_routines(&exec_data))
		return (ft_exit(&exec_data));
	return (ft_exit(&exec_data));
}
