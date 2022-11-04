/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:57:44 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 20:41:41 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	die_if_have_to(t_philo *philo, int nb_of_forks_in_hand)
{
	if (gettimestamp(*philo->exec_data) - philo->t_last_meal
		> philo->exec_data->t_to_die)
	{
		log_action(*philo, ACT_DIED);
		philo->exec_data->err_no = 1;
		release_forks(philo, nb_of_forks_in_hand);
		exit(ft_exit(philo->exec_data, 1));
	}
}
