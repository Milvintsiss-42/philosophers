/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:25:06 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/20 15:32:07 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_fork_action(t_philo philo, int is_right)
{
	if (is_right)
		log_action(*philo.exec_data, philo.id, ACT_TAKE_RIGHT_FORK);
	else
		log_action(*philo.exec_data, philo.id, ACT_TAKE_LEFT_FORK);
}

int	eat(t_philo *philo)
{
	int	right_fork;
	int	left_fork;
	int	first_fork;
	int	second_fork;

	left_fork = (philo->id == 0) * (philo->exec_data->nb_philo - 1)
		+ (philo->id != 0) * (philo->id - 1);
	right_fork = philo->id;
	first_fork = (philo->id % 2 == 1) * right_fork
		+ (philo->id % 2 == 0) * left_fork;
	second_fork = (philo->id % 2 == 0) * right_fork
		+ (philo->id % 2 == 1) * left_fork;
	if (pthread_mutex_lock(&philo->exec_data->forks[first_fork]) != 0)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 7));
	take_fork_action(*philo, first_fork == right_fork);
	if (pthread_mutex_lock(&philo->exec_data->forks[second_fork]) != 0)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 7));
	take_fork_action(*philo, second_fork == right_fork);
	log_action(*philo->exec_data, philo->id, ACT_IS_EATING);
	pthread_mutex_unlock(&philo->exec_data->forks[first_fork]);
	pthread_mutex_unlock(&philo->exec_data->forks[second_fork]);
	return (1);
}
