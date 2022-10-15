/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:32:55 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/15 10:30:29 by sthitiku         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->info->print);
	time = get_time() - philo->info->start;
	if (code == FORK)
		printf(CYAN"%6zu ms " PUR"%4d "RES "has taken a fork\n", \
			time, philo->id);
	else if (code == EAT)
		printf(CYAN"%6zu ms " PUR"%4d " GREEN"is eating\n"RES, \
			time, philo->id);
	else if (code == SLEEP)
		printf(CYAN"%6zu ms " PUR"%4d " BLUE"is sleeping\n"RES, \
			time, philo->id);
	else if (code == THINK)
		printf(CYAN"%6zu ms " PUR"%4d " YELLOW"is thinking\n"RES, \
			time, philo->id);
	else if (code == DEAD)
		printf(CYAN"%6zu ms " PUR"%4d " RED"died\n"RES, \
			time, philo->id);
	pthread_mutex_unlock(&philo->info->print);
}
