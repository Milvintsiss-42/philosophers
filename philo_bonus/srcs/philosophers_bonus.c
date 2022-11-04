/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:47:36 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 20:42:26 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	parse_input(t_exec_data *exec_data, int argc, char const **argv)
{
	exec_data->nb_philo = get_input(argv[1]);
	exec_data->t_to_die = get_input(argv[2]);
	exec_data->t_to_eat = get_input(argv[3]);
	exec_data->t_to_sleep = get_input(argv[4]);
	if (argc == 6)
		exec_data->nb_of_dinners = get_input(argv[5]);
	else
		exec_data->nb_of_dinners = INTMAX;
}

static int	init_exec_data(t_exec_data *exec_data, int argc, char const **argv)
{
	exec_data->err_no = 0;
	exec_data->philos = 0;
	exec_data->forks = 0;
	if (argc < 5 || argc > 6)
		return (ft_perror(exec_data, ERR_WRG_NB_ARG, 2));
	parse_input(exec_data, argc, argv);
	if (exec_data->nb_philo <= 0 || exec_data->t_to_die * 1000 < 0
		|| exec_data->t_to_eat * 1000 < 0 || exec_data->t_to_sleep * 1000 < 0
		|| exec_data->nb_of_dinners == -1)
		return (ft_perror(exec_data, ERR_WRG_ARG, 3));
	if (exec_data->t_to_die < exec_data->t_to_eat)
		exec_data->t_to_eat = exec_data->t_to_die;
	if (exec_data->t_to_die < exec_data->t_to_sleep + exec_data->t_to_eat)
		exec_data->t_to_sleep = exec_data->t_to_die - exec_data->t_to_eat;
	exec_data->init_timestamp = 0;
	exec_data->init_timestamp = gettimestamp(*exec_data);
	return (1);
}

static int	create_semaphore(t_exec_data *exec_data)
{
	exec_data->forks = sem_open(SEM_FORKS_NAME,
			O_CREAT | O_EXCL, 0644, exec_data->nb_philo);
	if (exec_data->forks == SEM_FAILED)
	{
		sem_unlink(SEM_FORKS_NAME);
		exec_data->forks = sem_open(SEM_FORKS_NAME,
				O_CREAT | O_EXCL, 0644, exec_data->nb_philo);
		if (exec_data->forks == SEM_FAILED)
			return (ft_perror(exec_data, ERR_UNKNOWN, 7));
	}
	return (1);
}

int	main(int argc, char const **argv)
{
	t_exec_data	exec_data;

	if (!init_exec_data(&exec_data, argc, argv))
		return (ft_exit(&exec_data, 0));
	if (!create_semaphore(&exec_data))
		return (ft_exit(&exec_data, 0));
	if (!launch_philo_processes(&exec_data))
		return (ft_exit(&exec_data, 0));
	monitoring(&exec_data);
	return (ft_exit(&exec_data, 0));
}
