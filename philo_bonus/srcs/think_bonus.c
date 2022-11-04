/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:55:18 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 20:18:02 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	think_action(t_philo *philo)
{
	log_action(*philo, ACT_IS_THINKING);
	while (gettimestamp(*philo->exec_data) - philo->t_last_meal
		< philo->exec_data->t_to_die * 2 / 3)
		die_if_have_to(philo, 0);
}
