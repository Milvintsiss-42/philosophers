/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 15:45:28 by ple-stra          #+#    #+#             */
/*   Updated: 2022/09/23 23:14:46 by ple-stra         ###   ########.fr       */
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

# ifndef KDEBUG
#  define KDEBUG 0
# endif

# define ERR_WRG_NB_ARG			"Incorrect number of arguments"
# define ERR_WRG_ARG			"Some arguments are incorrect"
# define ERR_UNKNOWN			"Unknown error"

# define ACT_IS_BORN			"is born"
# if KDEBUG == 1
#  define ACT_TAKE_RIGHT_FORK	"has taken the fork at his right"
#  define ACT_TAKE_LEFT_FORK	"has taken the fork at his left"
# else
#  define ACT_TAKE_RIGHT_FORK	"has taken a fork"
#  define ACT_TAKE_LEFT_FORK	"has taken a fork"
# endif
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
	int				one_philo_died;
	pthread_mutex_t	mutex_one_philo_died;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	int				err_no;
}	t_exec_data;

typedef struct s_philo
{
	int				id;
	long			t_last_meal;
	int				nb_of_dinners_eat;
	pthread_mutex_t	mutex_nb_of_dinners_eat;
	pthread_t		thread;
	t_exec_data		*exec_data;
}	t_philo;

int			ft_perror(t_exec_data *exec_data, char *str, int err);
int			ft_exit(t_exec_data *exec_data);

long		gettimestamp(t_exec_data exec_data);
void		log_action(t_exec_data exec_data, int philo_id, char *action);

int			get_input(const char *str);
size_t		ft_strlen(char *str);

int			launch_philo_routines(t_exec_data *exec_data);
int			wait_for_philo_routines(t_exec_data *exec_data);
int			monitoring(t_exec_data *exec_data);

void		release_forks(t_philo *philo, int first_fork, int second_fork);
int			eat(t_philo *philo, int *first_fork, int *second_fork);
int			p_sleep(t_philo *philo, int first_fork, int second_fork);
int			think(t_philo *philo);

int			is_dead_or_stop(t_philo *philo);
int			died_or_stop(t_philo *philo);
#endif