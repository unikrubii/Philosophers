/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:13:25 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/29 02:27:31 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (str[i] == '-')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (result);
}

void	init_sem(t_info *info)
{
	sem_unlink(S_FORKS);
	sem_unlink(S_PRINT);
	sem_unlink(S_DEAD);
	sem_unlink(S_MEAL);
	info->forks = sem_open(S_FORKS, O_CREAT, 0644, info->n_philo);
	info->print = sem_open(S_PRINT, O_CREAT, 0644, 1);
	info->dead = sem_open(S_DEAD, O_CREAT, 0644, info->n_philo);
	if (info->meal != -1)
		info->s_meal = sem_open(S_MEAL, O_CREAT, 0644, info->n_philo);
}

void	get_args(t_info *info, int ac, char **av)
{
	info->n_philo = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->meal = ft_atoi(av[5]);
	else
		info->meal = -1;
	info->timer = 0;
	info->start = 0;
	info->ph_end = 0;
	init_sem(info);
}

int	args_valid(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_philo	*create_philo(t_info *info)
{
	t_philo	*philo;
	size_t	i;

	philo = malloc(sizeof(t_philo) * info->n_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < info->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].ate = 0;
		philo[i].last_eat = get_time();
		philo[i].info = info;
		i++;
	}
	return (philo);
}
