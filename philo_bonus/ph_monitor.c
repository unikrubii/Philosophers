/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 01:28:54 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/29 02:28:16 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_eat(t_philo *philo)
{
	if (philo->ate < philo->info->meal || philo->info->meal == -1)
		return (0);
	sem_post(philo->info->s_meal);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	return (1);
}

static void	check_status(t_philo *philo)
{
	int	status;

	status = 0;
	if (philo->info->meal != -1)
	{
		while (waitpid(-1, &status, 0) > 0)
		{
			if (WEXITSTATUS(status) == EAT)
				sem_wait(philo->info->s_meal);
			else if (WEXITSTATUS(status) == DEAD)
				break ;
		}
		if (WEXITSTATUS(status) == EAT)
			printf(YELLOW"All philosophers have eaten the meals\n"RES);
	}
}

void	ph_clear(t_philo *philo)
{
	size_t	i;

	check_status(philo);
	sem_wait(philo->info->dead);
	sem_close(philo->info->forks);
	sem_close(philo->info->print);
	sem_close(philo->info->dead);
	sem_unlink(S_FORKS);
	sem_unlink(S_PRINT);
	sem_unlink(S_DEAD);
	i = 0;
	while (i < philo->info->n_philo)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
	free(philo);
}

void	*ph_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_eat(philo))
		{
			philo->info->ph_end = 1;
			sem_post(philo->info->dead);
			exit (EAT);
		}
		if (get_time() - philo->last_eat >= philo->info->t_die)
		{
			philo->info->ph_end = 1;
			ph_print(philo, DEAD);
			sem_wait(philo->info->print);
			if (philo->info->meal != -1)
				sem_post(philo->info->s_meal);
			sem_post(philo->info->dead);
			exit (DEAD);
		}
		usleep(200);
	}
	return (NULL);
}
