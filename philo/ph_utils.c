/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:13:25 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/15 10:28:12 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	long	minus;
	long	result;
	int		i;

	minus = 1;
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
	if (pthread_mutex_init(&info->print, NULL))
		return ;
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

t_philo	*ph_create2(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->n_philo)
		philo[i].next = &philo[(i + 1 % info->n_philo)];
	return (philo);
}

t_philo	*ph_create(t_info *info)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * info->n_philo);
	if (!philo)
	{
		ph_error(ALLOC_ERROR);
		return (NULL);
	}
	while (i < info->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].info = info;
		philo[i].last_eat = get_time();
		philo[i].ate = 0;
		if (pthread_mutex_init(&philo[i].forks, NULL))
		{
			ph_error(MUTEX_ERROR);
			return (NULL);
		}
		i++;
	}
	return (ph_create2(info, philo));
}
