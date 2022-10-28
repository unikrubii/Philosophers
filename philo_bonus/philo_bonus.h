/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:44:04 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/29 03:19:33 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PUR "\033[0;35m"
# define CYAN "\033[0;36m"
# define RES "\033[0m"

# define S_FORKS "/forks"
# define S_PRINT "/print"
# define S_DEAD "/dead"
# define S_MEAL "/meal"

enum e_error
{
	NO_ERROR,
	ARG_ERROR,
	ALLOC_ERROR,
	THREAD_ERROR,
	MUTEX_ERROR,
	FORK_ERROR,
};

enum e_status
{
	EAT,
	FORK,
	SLEEP,
	THINK,
	DEAD,
};

typedef struct s_info
{
	size_t			n_philo;
	size_t			t_die;
	size_t			t_eat;
	size_t			t_sleep;
	size_t			timer;
	size_t			start;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*dead;
	sem_t			*s_meal;
	int				ph_end;
	int				meal;
}	t_info;

typedef struct s_philo
{
	int			id;
	int			ate;
	size_t		last_eat;
	pid_t		pid;
	pthread_t	th;
	t_info		*info;
}	t_philo;

/* ph_print.c */
int		ph_error(int code);
void	ph_print(t_philo *philo, int code);

/* ph_utils */
int		ft_atoi(char *str);
void	get_args(t_info *info, int ac, char **av);
int		args_valid(int ac, char **av);
t_philo	*create_philo(t_info *info);

/* ph_time */
size_t	get_time(void);
void	ph_mysleep(size_t time);

/* ph_routine.c */
int		ph_routine(t_philo *philo);

/* ph_monitor.c */
void	*ph_monitor(void *arg);
void	ph_clear(t_philo *philo);

#endif