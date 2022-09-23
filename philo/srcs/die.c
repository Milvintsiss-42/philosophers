/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:09:08 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/23 19:19:21 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	log_philo_died(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->exec_data->mutex_die_has_been_logged) != 0)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 10));
	if (!philo->exec_data->die_has_been_logged)
	{
		log_action(*philo->exec_data, philo->id, ACT_DIED);
		philo->exec_data->die_has_been_logged = 1;
	}
	pthread_mutex_unlock(&philo->exec_data->mutex_die_has_been_logged);
	return (1);
}

int	is_dead_or_stop(t_philo *philo)
{
	if (philo->exec_data->err_no != 0)
		return (1);
	if (gettimestamp(*philo->exec_data) - philo->t_last_meal
		> philo->exec_data->t_to_die)
		return (1);
	if (pthread_mutex_lock(&philo->exec_data->mutex_one_philo_died) != 0)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 9));
	if (philo->exec_data->one_philo_died)
	{
		pthread_mutex_unlock(&philo->exec_data->mutex_one_philo_died);
		return (1);
	}
	pthread_mutex_unlock(&philo->exec_data->mutex_one_philo_died);
	return (0);
}

int	died_or_stop(t_philo *philo)
{
	if (gettimestamp(*philo->exec_data) - philo->t_last_meal
		> philo->exec_data->t_to_die
		|| philo->exec_data->err_no != 0)
	{
		if (pthread_mutex_lock(&philo->exec_data->mutex_one_philo_died) != 0)
			return (ft_perror(philo->exec_data, ERR_UNKNOWN, 9));
		philo->exec_data->one_philo_died = 1;
		pthread_mutex_unlock(&philo->exec_data->mutex_one_philo_died);
		if (philo->exec_data->err_no == 0)
			if (!log_philo_died(philo))
				return (0);
		return (0);
	}
	if (pthread_mutex_lock(&philo->exec_data->mutex_one_philo_died) != 0)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 9));
	if (philo->exec_data->one_philo_died)
	{
		pthread_mutex_unlock(&philo->exec_data->mutex_one_philo_died);
		return (0);
	}
	pthread_mutex_unlock(&philo->exec_data->mutex_one_philo_died);
	return (1);
}
