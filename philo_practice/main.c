/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:01:29 by sthitiku          #+#    #+#             */
/*   Updated: 2022/09/25 17:59:19 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_error(int code)
{
	if (code == ARG_ERROR)
	{
		printf("Error: invalid arguments\n");
		printf("Usage: ./philo [number of philos] [time to die] [time to eat]");
		printf("[time to sleep] [number of time to eat: optional]\n");
	}
	exit(code);
}

void	getargs(t_info *info, t_philo *philo, int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		info->nb_philo = ft_atoi(av[i++]);
		info->time_to_die = ft_atoi(av[i++]);
		info->time_to_eat = ft_atoi(av[i++]);
		info->time_to_sleep = ft_atoi(av[i++]);
		if (ac == 6)
			info->nb_meal = ft_atoi(av[i++]);
		else
			info->nb_meal = 0;
		info->ate_meal = 0;
	}
}

void	ph_create(t_info *info)
{
	struct timeval	time;
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * info->nb_philo);
	i = 0;
	while (i < info->nb_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].thread = 0;
		info->philo[i].last_eat = 0;
		info->philo[i].status = THINK;
		i++;
	}
}

/* ./philo [number of philos] [time to die] [time to eat] [time to sleep] */
	/* optional "number of time to eat" */
int	main(int ac, char **av)
{
	t_info		info;
	t_philo		philo;
	pthread_t	*thread;
	// struct timeval	time;

	if (ac < 5 || ac > 6 || ft_atoi(av[1]) < 1)
		ph_error(ARG_ERROR);
	getargs(&info, &philo, ac, av);
	// ph_create(&info);
	
	// printf("info -> %zu %zu %zu %zu %zu\n", info.nb_philo, info.time_to_die, info.time_to_eat, info.time_to_sleep, info.nb_meal);
	// gettimeofday(&time, NULL);
	// printf("%zu\n", time.tv_sec * 1000 + time.tv_usec / 1000);
}
