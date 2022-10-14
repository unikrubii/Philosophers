/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:44:04 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/13 23:51:21 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PUR "\033[0;35m"
# define CYAN "\033[0;36m"
# define RES "\033[0m"

enum e_error
{
	NO_ERROR,
	ARG_ERROR,
	ALLOC_ERROR,
	THREAD_ERROR,
	MUTEX_ERROR,
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
	pthread_mutex_t	print;
	int				ph_end;
	int				meal;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				ate;
	size_t			last_eat;
	pthread_t		th;
	pthread_mutex_t	forks;
	struct s_philo	*next;
	t_info			*info;
}	t_philo;

/* ph_print.c */
int		ph_error(int code);
void	ph_print(t_philo *philo, int code);

/* ph_utc */
int		ft_atoi(char *str);
void	get_args(t_info *info, int ac, char **av);
int		args_valid(int ac, char **av);
t_philo	*ph_create(t_info *info);

/* ph_ti */
size_t	get_time(void);
void	ph_mysleep(size_t time);

/* ph_roe.c */
int		ph_routine(t_philo *philo);
void	*ph_death(void *arg);

#endif