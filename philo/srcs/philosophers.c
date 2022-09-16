/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:19 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/16 23:02:46 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_exec_data(t_exec_data *exec_data, int argc, char const **argv)
{
	exec_data->err_no = 0;
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
	if (exec_data->nb_philo <= 0 || exec_data->t_to_die == -1
		|| exec_data->t_to_eat == -1 || exec_data->t_to_sleep == -1
		|| exec_data->nb_of_dinners == -1)
		return (ft_perror(exec_data, ERR_WRG_ARG, 3));
	exec_data->init_timestamp = 0;
	exec_data->init_timestamp = gettimestamp(*exec_data);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	log_action(*philo->exec_data, philo->id, ACT_IS_BORN);
	return (NULL);
}

static int	launch_philo_routines(t_exec_data *exec_data)
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
		if (pthread_create(&exec_data->philos[i].thread,
				NULL, &philo_routine, &exec_data->philos[i])
			!= 0)
			return (ft_perror(exec_data, ERR_UNKNOWN, 7));
	}
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
	while (1)
		;
	return (ft_exit(&exec_data));
}
