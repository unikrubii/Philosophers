/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:51:50 by sthitiku          #+#    #+#             */
/*   Updated: 2022/09/19 14:04:04 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data()
{
	
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong number of arguments"));
	data = init_data(av);
	if (!data)
		return (ft_error("Error while initializing data"));
	philo = ft_init_philo(data);
	if (!philo)
		return (ft_error("Error while initializing philo"));
	if (ft_start_threads(philo, data))
		return (ft_error("Error while starting threads"));
	ft_free_all(philo, data);
	return (0);
}
