/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:45:28 by ple-stra          #+#    #+#             */
/*   Updated: 2022/08/28 21:19:58 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/errno.h>

# define ERR_WRG_NB_ARG			"Incorrect number of arguments"
# define ERR_UNKNOWN			"Unknown error"

typedef struct s_exec_data
{
	int		nb_philo;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		nb_of_dinners;
}	t_exec_data;

int			ft_perror(char *str, int err);
int			ft_perror_errno(void);

#endif