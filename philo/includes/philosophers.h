/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:45:28 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/19 16:24:48 by ple-stra         ###   ########.fr       */
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

# define ACT_IS_BORN		"is born"
# define ACT_TAKE_FORK		"has taken a fork"
# define ACT_IS_EATING		"is eating"
# define ACT_IS_SLEEPING	"is sleeping"
# define ACT_IS_THINKING	"is thinking"
# define ACT_DIED			"died"	

# define INTMIN -2147483648
# define INTMAX 2147483647

struct	s_philo;
typedef struct s_exec_data
{
	int				nb_philo;
	long			init_timestamp;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_of_dinners;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	int				err_no;
}	t_exec_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_exec_data	*exec_data;
}	t_philo;

int			ft_perror(t_exec_data *exec_data, char *str, int err);
int			ft_exit(t_exec_data *exec_data);

long		gettimestamp(t_exec_data exec_data);
void		log_action(t_exec_data exec_data, int philo_id, char *action);

int			get_input(const char *str);
size_t		ft_strlen(char *str);

int			launch_philo_routines(t_exec_data *exec_data);
int			wait_for_philo_routines(t_exec_data *exec_data);
#endif