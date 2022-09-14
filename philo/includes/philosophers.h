/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:45:28 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/15 00:21:10 by ple-stra         ###   ########.fr       */
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
# define ERR_WRG_ARG			"Some arguments are incorrect"
# define ERR_UNKNOWN			"Unknown error"

# define ACT_TAKE_FORK		"has taken a fork"
# define ACT_IS_EATING		"is eating"
# define ACT_IS_SLEEPING	"is sleeping"
# define ACT_IS_THINKING	"is thinking"
# define ACT_DIED			"died"	

# define INTMIN -2147483648
# define INTMAX 2147483647

typedef struct s_exec_data
{
	int				nb_philo;
	long			init_timestamp;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_of_dinners;
	pthread_mutex_t	*forks;
}	t_exec_data;

int			ft_perror(char *str, int err);
int			ft_perror_errno(void);

long		gettimestamp(t_exec_data exec_data);
void		log_action(t_exec_data exec_data, int philo_id, char *action);

int			get_input(const char *str);
size_t		ft_strlen(char *str);

#endif