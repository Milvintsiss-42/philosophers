/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:39:42 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/24 00:41:58 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	store_death(t_exec_data *exec_data)
{
	if (pthread_mutex_lock(&exec_data->mutex_one_philo_died) != 0)
		return (ft_perror(exec_data, ERR_UNKNOWN, 9));
	exec_data->one_philo_died = 1;
	pthread_mutex_unlock(&exec_data->mutex_one_philo_died);
	return (1);
}

static int	log_death(t_exec_data *exec_data, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mutex_nb_of_dinners_eat) != 0)
		return (ft_perror(exec_data, ERR_UNKNOWN, 12));
	if (philo->nb_of_dinners_eat < exec_data->nb_of_dinners)
		log_action(*exec_data, philo->id, ACT_DIED);
	pthread_mutex_unlock(&philo->mutex_nb_of_dinners_eat);
	return (1);
}

int	monitoring(t_exec_data *exec_data)
{
	int		i;
	t_philo	*philo;

	while (exec_data->err_no == 0)
	{
		i = -1;
		while (++i < exec_data->nb_philo)
		{
			philo = exec_data->philos + i;
			if (gettimestamp(*exec_data) - philo->t_last_meal
				> exec_data->t_to_die)
			{
				if (!store_death(exec_data))
					return (0);
				if (!log_death(exec_data, philo))
					return (0);
				return (1);
			}
		}
	}
	return (1);
}
