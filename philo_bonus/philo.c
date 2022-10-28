/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:58:02 by sthitiku          #+#    #+#             */
/*   Updated: 2022/10/29 03:40:35 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	if (!args_valid(ac, av))
		return (ph_error(ARG_ERROR));
	get_args(&info, ac, av);
	if (info.n_philo == 0)
		return (NO_ERROR);
	philo = create_philo(&info);
	if (!philo)
		return (ph_error(ALLOC_ERROR));
	if (ph_routine(philo))
		return (ph_error(FORK_ERROR));
	ph_clear(philo);
}
