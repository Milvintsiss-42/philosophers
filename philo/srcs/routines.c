/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:51:13 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/21 18:17:33 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	log_action(*philo->exec_data, philo->id, ACT_IS_BORN);
	while (1)
	{
		if (philo->nb_of_dinners_eat == philo->exec_data->nb_of_dinners)
			return (NULL);
		if (!eat(philo))
			return (NULL);
		if (!p_sleep(philo))
			return (NULL);
		think(*philo);
	}
	return (NULL);
}

int	launch_philo_routines(t_exec_data *exec_data)
{
	int	i;

	exec_data->philos = malloc(sizeof(t_philo) * exec_data->nb_philo);
	if (!exec_data->philos)
		return (ft_perror(exec_data, ERR_UNKNOWN, 6));
	i = -1;
	while (++i < exec_data->nb_philo)
	{
		exec_data->philos[i].id = i;
		exec_data->philos[i].exec_data = exec_data;
		exec_data->philos[i].nb_of_dinners_eat = 0;
		exec_data->philos[i].t_last_meal = 0;
		if (pthread_create(&exec_data->philos[i].thread,
				NULL, &philo_routine, &exec_data->philos[i])
			!= 0)
			return (ft_perror(exec_data, ERR_UNKNOWN, 7));
	}
	return (1);
}

// This method should never return!
int	wait_for_philo_routines(t_exec_data *exec_data)
{
	int	i;

	i = -1;
	while (++i < exec_data->nb_philo)
		pthread_join(exec_data->philos[i].thread, NULL);
	return (0);
}
