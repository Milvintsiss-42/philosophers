/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:38:04 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/22 14:13:46 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	p_sleep(t_philo *philo)
{
	log_action(*philo->exec_data, philo->id, ACT_IS_SLEEPING);
	usleep(philo->exec_data->t_to_sleep * 1000);
	if (is_dead_or_stop(philo))
		return (died_or_stop(philo));
	return (1);
}
