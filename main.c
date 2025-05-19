/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:59:00 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/19 14:53:44 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	verif(char **av, int ac)
{
	if (ft_atol(av[1]) <= 1 || ft_isdigit(av[1] == 0) || ft_atol(av[1]) > 200)
		return(printf("arg incorrect"), -1);
	if (ft_atol(av[2]) <= 0 || ft_isdigit(av[2] == 0))
		return(printf("arg incorrect"), -1);
	if (ft_atol(av[3]) <= 0 || ft_isdigit(av[3] == 0))
		return(printf("arg incorrect"), -1);
	if (ft_atol(av[4]) <= 0 || ft_isdigit(av[4] == 0))
		return(printf("arg incorrect"), -1);
	if(ac == 6)
	{
		if (ft_atol(av[5]) <= 0 || ft_isdigit(av[5] == 0))
			return(printf("arg incorrect"), -1);
	}
	return (0);

}

void	init_p(t_data *data)
{
	int			i;
	pthread_t	jefe;
	t_philo		fifi;

	i = 0;
	if (pthread_create(&jefe, NULL, &end_v, data) != 0)
		exit(-1);
	while (i < data->nbr_p)
	{
		fifi = data->philos[i];
		if (pthread_create(&data->philos[i].core, NULL, &routine, &fifi) != 0)
			exit(-1);
		i++;
	}
	if (pthread_join(jefe, NULL) != 0)
		exit(-1);
	while (data->nbr_p < i--)
	{
		if (pthread_join(data->philos[i].core, NULL) != 0)
			exit(-1);
	}
} 

void	init(char **av, t_data *data, int ac)
{
	int	i;
	int	j;

	i = ft_atol(av[1]);
	j = 0;
	data->nbr_p = i;
	while (j < i)
	{
		data->philos[j].index = j + 1;
		data->philos[j].time_t_die = ft_atol(av[2]);
		data->philos[j].time_t_eat = ft_atol(av[3]);
		data->philos[j].time_t_sleep = ft_atol(av[4]);
		data->philos[j].ded = 0;
		data->philos[j].meals_eat = 0;
		printf("l index = %i\net le i = %i\n", data->philos[j].index, j);
		if (ac == 6)
			data->philos[j].need_t_eat = ft_atol(av[5]);
		else
			data->philos[j].need_t_eat = -1;
		/*printf("need eat %i\neat meal %i\nded %i\n",
			data->philos[j].need_t_eat,
			data->philos[j].meals_eat,
			data->philos[j].ded);*/
		j++;
	}
}

int	main(int ac, char **av)
{
	t_data				*data;
	t_philo				philo[PHILOMAX];
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	data->philos = philo;
	if (ac != 5 && ac != 6)
	{
		free(data);
		return (printf("arg incorrect\n"), 0);
	}
	if (verif(av, ac) == -1)
	{
		free(data);
		exit(0);
	}
	init(av, data, ac);
	init_p(data);
}
