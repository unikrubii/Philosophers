/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 04:13:25 by sthitiku          #+#    #+#             */
/*   Updated: 2022/09/25 13:14:17 by sthitiku         ###   ########.fr       */
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
		ph_error(ARG_ERROR);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		ph_error(ARG_ERROR);
	return (result);
}
