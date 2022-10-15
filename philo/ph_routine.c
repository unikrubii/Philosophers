/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:40:14 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/15 10:23:13 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_sleepthink(t_philo *philo)
{
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, SLEEP);
	ph_mysleep(philo->info->t_sleep);
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, THINK);
	return (0);
}

static int	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->forks);
	pthread_mutex_lock(&philo->forks);
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, FORK);
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, FORK);
	philo->last_eat = get_time();
	philo->ate++;
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, EAT);
	ph_mysleep(philo->info->t_eat);
	pthread_mutex_unlock(&philo->next->forks);
	pthread_mutex_unlock(&philo->forks);
	return (0);
}

static void	*ph_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ph_eat(philo))
			return (NULL);
		if (ph_sleepthink(philo))
			return (NULL);
		usleep(500);
	}
	return (NULL);
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
