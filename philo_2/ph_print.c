/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:32:55 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/14 17:46:45 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_error(int code)
{
	if (code == ARG_ERROR)
	{
		printf("Error: invalid arguments\nUsage: ./philo ");
		printf("[number of philos] [time to die] [time to eat] ");
		printf("[time to sleep] [number of time to eat: optional]\n");
	}
	else if (code == ALLOC_ERROR)
		printf("Error: memory allocation failed\n");
	else if (code == THREAD_ERROR)
		printf("Error: thread creation failed\n");
	else if (code == MUTEX_ERROR)
		printf("Error: mutex creation failed\n");
	return (code);
}

void	ph_print(t_philo *philo, int code)
{
	size_t	time;

	// pthread_mutex_lock(&philo->info->print);
	time = get_time() - philo->info->start;
	// printf(CYAN"%ld ms " PUR"%d "RES, time, philo->id);
	if (code == FORK)
		printf(CYAN"%zu ms " PUR"%d "RES "has taken a fork\n", \
			get_time() - philo->info->start, philo->id);
	else if (code == EAT)
		printf(CYAN"%zu ms " PUR"%d " GREEN"is eating\n"RES, \
			get_time() - philo->info->start, philo->id);
	else if (code == SLEEP)
		printf(CYAN"%zu ms " PUR"%d " BLUE"is sleeping\n"RES, \
			get_time() - philo->info->start, philo->id);
	else if (code == THINK)
		printf(CYAN"%zu ms " PUR"%d " YELLOW"is thinking\n"RES, \
			get_time() - philo->info->start, philo->id);
	else if (code == DEAD)
		printf(CYAN"%zu ms " PUR"%d " RED"died\n"RES, \
			get_time() - philo->info->start, philo->id);
	// pthread_mutex_unlock(&philo->info->print);
}
