/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:52:57 by sthitiku          #+#    #+#             */
/*   Updated: 2022/09/16 18:57:20 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	int				nb_forks;
	int				nb_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				last_meal;
	int				meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*meals_mutex;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_forks;
	int				nb_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}	t_data;



#endif
