/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:00 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/14 19:46:04 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_philo *philo)
{
	int	i;

	i = 0;
	
	while (i < philo->info->n_philo)
	{
		if (philo[i].ate < philo->info->meal || philo->info->meal == -1)
			return (0);
		i++;
	}
	pthread_mutex_lock(&philo->info->print);
	return (1);
}

void	*ph_monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philo->info->n_philo)
		{
			if (check_eat(philo))
				return (NULL);
			pthread_mutex_lock(&philo->info->print);
			if (get_time() - philo[i].last_eat >= philo->info->t_die)
			{
				ph_print(&philo[i], DEAD);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->info->print);
			i++;
		}
	}
	return (NULL);
}

void ph_clear(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->n_philo)
	{
		pthread_mutex_destroy(&philo[i].forks);
		i++;
	}
	free(philo);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;
	pthread_t	*th;
	int			i;

	if (!args_valid(ac, av))
		return (ph_error(ARG_ERROR));
	get_args(&info, ac, av);
	if (info.n_philo == 0)
		return (NO_ERROR);
	philo = ph_create(&info);
	if (!philo)
		return (1);
	ph_routine(philo);
	th = malloc(sizeof(pthread_t) * info.n_philo);
	ph_monitor(philo);
	// i = 0;
	// while (i < info.n_philo)
	// {
	// 	pthread_create(&th[i], NULL, ph_monitor, &philo[i]);
	// 	pthread_detach(th[i]);
	// 	i++;
	// }
	// pthread_create(&th[i], NULL, ph_monitor, philo[i]);
	// pthread_join(th, NULL);
	ph_clear(philo);
	pthread_mutex_destroy(&philo->info->print);
	return (0);
}