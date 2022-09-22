/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:25:06 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/22 16:02:10 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	take_fork(t_philo *philo, int fork_id, int is_right)
{
	if (is_dead_or_stop(philo))
		return (died_or_stop(philo));
	if (pthread_mutex_lock(&philo->exec_data->forks[fork_id]) != 0)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 7));
	if (is_right)
		log_action(*philo->exec_data, philo->id, ACT_TAKE_RIGHT_FORK);
	else
		log_action(*philo->exec_data, philo->id, ACT_TAKE_LEFT_FORK);
	return (1);
}

void	release_forks(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_unlock(&philo->exec_data->forks[first_fork]);
	pthread_mutex_unlock(&philo->exec_data->forks[second_fork]);
}

static int	no_more_fork(t_philo *philo, int first_fork, int second_fork)
{
	release_forks(philo, first_fork, second_fork);
	while (1)
	{
		if (is_dead_or_stop(philo))
			return (died_or_stop(philo));
	}
	return (0);
}

static int	take_dinner_and_release_forks(t_philo *philo,
	int first_fork, int second_fork)
{
	if (is_dead_or_stop(philo))
	{
		release_forks(philo, first_fork, second_fork);
		return (died_or_stop(philo));
	}
	philo->t_last_meal = gettimestamp(*philo->exec_data);
	log_action(*philo->exec_data, philo->id, ACT_IS_EATING);
	usleep(philo->exec_data->t_to_eat * 1000);
	if (is_dead_or_stop(philo))
	{
		release_forks(philo, first_fork, second_fork);
		return (died_or_stop(philo));
	}
	philo->nb_of_dinners_eat++;
	return (1);
}

int	eat(t_philo *philo, int *first_fork, int *second_fork)
{
	int	right_fork;
	int	left_fork;

	left_fork = (philo->id == 0) * (philo->exec_data->nb_philo - 1)
		+ (philo->id != 0) * (philo->id - 1);
	right_fork = philo->id;
	*first_fork = (philo->id % 2 == 1) * right_fork
		+ (philo->id % 2 == 0) * left_fork;
	*second_fork = (philo->id % 2 == 0) * right_fork
		+ (philo->id % 2 == 1) * left_fork;
	if (!take_fork(philo, *first_fork, *first_fork == right_fork))
		return (0);
	if (philo->exec_data->nb_philo < 2)
		return (no_more_fork(philo, *first_fork, *second_fork));
	if (!take_fork(philo, *second_fork, *second_fork == right_fork))
	{
		release_forks(philo, *first_fork, *second_fork);
		return (0);
	}
	if (!take_dinner_and_release_forks(philo, *first_fork, *second_fork))
		return (0);
	return (1);
}
