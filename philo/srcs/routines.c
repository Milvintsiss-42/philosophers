/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:51:13 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/24 00:52:55 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	has_eat_enough_or_error(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mutex_nb_of_dinners_eat) != 0)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 12), 1);
	if (philo->nb_of_dinners_eat == philo->exec_data->nb_of_dinners)
	{
		pthread_mutex_unlock(&philo->mutex_nb_of_dinners_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex_nb_of_dinners_eat);
	return (0);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		first_fork;
	int		second_fork;
	int		pre_slip_time;

	philo = (t_philo *)arg;
	if (KDEBUG)
		log_action(*philo->exec_data, philo->id, ACT_IS_BORN);
	pre_slip_time = 50000;
	if (philo->exec_data->t_to_eat < 50)
		pre_slip_time = philo->exec_data->t_to_eat;
	if (philo->id % 2 == 0)
		usleep(pre_slip_time);
	while (1)
	{
		if (has_eat_enough_or_error(philo))
			return (NULL);
		if (!eat(philo, &first_fork, &second_fork))
			return (NULL);
		if (!p_sleep(philo, first_fork, second_fork))
			return (NULL);
		if (!think(philo))
			return (NULL);
	}
	return (NULL);
}

int	launch_philo_routines(t_exec_data *exec_data)
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
		exec_data->philos[i].nb_of_dinners_eat = 0;
		exec_data->philos[i].t_last_meal = 0;
		if (pthread_mutex_init(
				&exec_data->philos[i].mutex_nb_of_dinners_eat, NULL) != 0)
			return (ft_perror(exec_data, ERR_UNKNOWN, 11));
		if (pthread_create(&exec_data->philos[i].thread,
				NULL, &philo_routine, &exec_data->philos[i])
			!= 0)
			return (ft_perror(exec_data, ERR_UNKNOWN, 7));
	}
	return (1);
}

// This method should never return!
int	wait_for_philo_routines(t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
		pthread_join(exec_data->philos[i].thread, NULL);
	return (0);
}
