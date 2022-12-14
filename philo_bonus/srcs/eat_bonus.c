/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:25:06 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 22:16:15 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static int	take_fork(t_philo *philo)
{
	if (sem_wait(philo->exec_data->forks) == -1)
		return (ft_perror(philo->exec_data, ERR_UNKNOWN, 8));
	log_action(*philo, ACT_TAKE_FORK);
	return (1);
}

void	release_forks(t_philo *philo, int nb)
{
	sem_post(philo->exec_data->forks);
	if (nb == 2)
		sem_post(philo->exec_data->forks);
}

void	philo_is_alone_sniff(t_philo *philo)
{
	while (1)
	{
		die_if_have_to(philo, 1);
	}
}

void	eat_action(t_philo *philo)
{
	if (!take_fork(philo))
		exit(ft_exit(philo->exec_data, 1));
	die_if_have_to(philo, 1);
	if (philo->exec_data->nb_philo == 1)
		philo_is_alone_sniff(philo);
	if (!take_fork(philo))
	{
		release_forks(philo, 1);
		exit(ft_exit(philo->exec_data, 1));
	}
	die_if_have_to(philo, 2);
	philo->t_last_meal = gettimestamp(*philo->exec_data);
	log_action(*philo, ACT_IS_EATING);
	usleep(philo->exec_data->t_to_eat * 1000);
	die_if_have_to(philo, 2);
	philo->nb_of_dinners_eat++;
}
