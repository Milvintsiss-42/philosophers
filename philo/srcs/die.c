/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:09:08 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/20 22:58:14 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead_or_friend(t_philo *philo)
{
	if (gettimestamp(*philo->exec_data) - philo->t_last_meal
		> philo->exec_data->t_to_die)
		return (1);
	if (philo->exec_data->one_philo_died)
		return (1);
	return (0);
}

int	died_or_stop(t_philo *philo)
{
	if (gettimestamp(*philo->exec_data) - philo->t_last_meal
		> philo->exec_data->t_to_die)
	{
		philo->exec_data->one_philo_died = 1;
		log_action(*philo->exec_data, philo->id, ACT_DIED);
		return (0);
	}
	if (philo->exec_data->one_philo_died)
		return (0);
	return (1);
}
