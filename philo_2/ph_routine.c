/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:40:14 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/14 17:52:02 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ph_sleepthink(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	ph_print(philo, SLEEP);
	pthread_mutex_unlock(&philo->info->print);
	ph_mysleep(philo->info->t_sleep);
	pthread_mutex_lock(&philo->info->print);
	ph_print(philo, THINK);
	pthread_mutex_unlock(&philo->info->print);
}

static void	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->forks);
	pthread_mutex_lock(&philo->forks);
	pthread_mutex_lock(&philo->info->print);
	ph_print(philo, FORK);
	ph_print(philo, FORK);
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_lock(&philo->info->print);
	ph_print(philo, EAT);
	philo->ate++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->info->print);
	ph_mysleep(philo->info->t_eat);
	pthread_mutex_unlock(&philo->next->forks);
	pthread_mutex_unlock(&philo->forks);
}

static void	*ph_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ph_eat(philo);
		usleep(100);
		ph_sleepthink(philo);
	}
	return (NULL);
}

void	*ph_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time() - philo->last_eat > philo->info->t_die)
		{
			pthread_mutex_lock(&philo->info->print);
			ph_print(philo, DEAD);
			pthread_mutex_unlock(&philo->info->print);
			return (NULL);
		}
	}
}

int	ph_routine(t_philo *philo)
{
	int	i;

	i = 0;
	philo->info->start = get_time();
	while (i < philo->info->n_philo)
	{
		if (pthread_create(&philo[i].th, NULL, &ph_life, &philo[i]))
			return (ph_error(THREAD_ERROR));
		if (pthread_detach(philo[i].th))
			return (ph_error(THREAD_ERROR));
		i += 2;
		if (i >= philo->info->n_philo && i % 2 == 0)
		{
			i = 1;
			usleep(500);
		}
	}
	return (0);
}
