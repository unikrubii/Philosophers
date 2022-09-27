/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:44:04 by sthitiku          #+#    #+#             */
/*   Updated: 2022/09/25 12:47:48 by sthitiku         ###   ########.fr       */
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
# define CYAN "\033[0;36m"
# define RES "\033[0m"

# define DIE_TXT " has died\n"
# define SLEEP_TXT " is sleeping\n"
# define THINK_TXT " is thinking\n"
# define EAT_TXT " is eating\n"
# define FORK_TXT " has taken a fork\n"

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
	RELEASE,
	SLEEP,
	THINK,
	DEAD,
};

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	struct s_philo	*next;
	size_t			last_meal;
	int				status;
}	t_philo;

typedef struct s_info
{
	t_philo	*philo;
	size_t	nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	time;
	int		nb_meal;
	int		ate_meal;
}	t_info;

void	ph_error(int code);
int		ft_atoi(char *str);

#endif