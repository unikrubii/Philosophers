/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 01:21:10 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/29 03:19:56 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->info->forks);
	sem_wait(philo->info->forks);
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, FORK);
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, FORK);
	philo->last_eat = get_time();
	if (philo->info->ph_end)
		return (1);
	ph_print(philo, EAT);
	philo->ate++;
	ph_mysleep(philo->info->t_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	return (0);
}

static void	*ph_life(t_philo *philo)
{
	while (1)
	{
		if (ph_eat(philo))
			return (NULL);
		if (ph_sleepthink(philo))
			return (NULL);
		usleep(200);
	}
}

int	ph_routine(t_philo *philo)
{
	size_t	i;

	philo->info->start = get_time();
	i = 0;
	while (i < philo->info->n_philo)
	{
		sem_wait(philo->info->dead);
		if (philo->info->meal != -1)
			sem_wait(philo->info->s_meal);
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (1);
		if (philo[i].pid == 0)
		{
			philo[i].last_eat = get_time();
			pthread_create(&philo[i].th, NULL, ph_monitor, &philo[i]);
			pthread_detach(philo[i].th);
			ph_life(&philo[i]);
			return (0);
		}
		i++;
	}
	return (0);
}
