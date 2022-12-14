/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:38:04 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/23 22:45:12 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_sleep(t_philo *philo, int first_fork, int second_fork)
{
	if (is_dead_or_stop(philo))
		return (died_or_stop(philo));
	log_action(*philo->exec_data, philo->id, ACT_IS_SLEEPING);
	release_forks(philo, first_fork, second_fork);
	usleep(philo->exec_data->t_to_sleep * 1000);
	return (1);
}
