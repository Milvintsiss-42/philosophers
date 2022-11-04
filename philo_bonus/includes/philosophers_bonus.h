/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:59:10 by ple-stra          #+#    #+#             */
/*   Updated: 2022/11/04 12:16:49 by ple-stra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

# ifndef KDEBUG
#  define KDEBUG 0
# endif

# define ERR_WRG_NB_ARG			"Incorrect number of arguments"
# define ERR_WRG_ARG			"Some arguments are incorrect"
# define ERR_UNKNOWN			"Unknown error"

# define SEM_FORKS_NAME			"/forks"

# define ACT_IS_BORN			"is born"
# define ACT_TAKE_FORK			"has taken a fork"
# define ACT_IS_EATING			"is eating"
# define ACT_IS_SLEEPING		"is sleeping"
# define ACT_IS_THINKING		"is thinking"
# define ACT_DIED				"died"

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
	int				t_to_think;
	int				nb_of_dinners;
	struct s_philo	*philos;
	sem_t			*forks;
	int				err_no;
}	t_exec_data;

typedef struct s_philo
{
	int				id;
	int				pid;
	long			t_last_meal;
	int				nb_of_dinners_eat;
	t_exec_data		*exec_data;
}	t_philo;

int			ft_perror(t_exec_data *exec_data, char *str, int err);
int			ft_exit(t_exec_data *exec_data);

long		gettimestamp(t_exec_data exec_data);
void		log_action(t_philo philo, char *action);

int			get_input(const char *str);
size_t		ft_strlen(char *str);

int			launch_philo_processes(t_exec_data *exec_data);
int			wait_for_philo_processes(t_exec_data *exec_data);
void		monitoring(t_exec_data *exec_data);

int			eat(t_philo *philo);

#endif