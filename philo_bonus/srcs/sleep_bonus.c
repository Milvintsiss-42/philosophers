/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:47:43 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 19:51:41 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	sleep_action(t_philo *philo)
{
	log_action(*philo, ACT_IS_SLEEPING);
	release_forks(philo, 2);
	usleep(philo->exec_data->t_to_sleep * 1000);
	die_if_have_to(philo, 0);
	return (1);
}
