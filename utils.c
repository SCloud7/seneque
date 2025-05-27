/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:54:20 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/27 15:43:43 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long	ft_atol(const char *str)
{
	int		sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (nbr * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
void	clear_data(t_data *data)
{
	int	i;

	if(!data)
		return ;
	i = 0;
	while (i < data->nbr_p)
	{
		pthread_join(data->philos[i].core, NULL);
		pthread_mutex_destroy(data->philos[i].fork);
		i++;
	}
	//pthread_mutex_destroy(&data->windows);
	//pthread_mutex_destroy(&data->dead_flag);
	//free(data->philos);
	free(data);
	exit(0);
}
