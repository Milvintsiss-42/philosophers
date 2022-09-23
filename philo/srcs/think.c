/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:27:35 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/23 22:44:48 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	think(t_philo *philo)
{
	if (is_dead_or_stop(philo))
		return (died_or_stop(philo));
	log_action(*philo->exec_data, philo->id, ACT_IS_THINKING);
	usleep(philo->exec_data->t_to_think * 1000);
	return (1);
}
