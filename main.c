/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:59:00 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/27 14:57:36 by ssoukoun         ###   ########.fr       */
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
	t_philo		*fifi;

	i = 0;
	if (pthread_create(&jefe, NULL, &end_v, data) != 0)
		clear_data(data);
	while (i < data->nbr_p)
	{
		pthread_mutex_init(data->philos[i].fork, NULL);
		fifi = &data->philos[i];
		if (pthread_create(&data->philos[i].core, NULL, &routine, fifi) != 0)
			clear_data(data);
		i++;
	}
	if (pthread_join(jefe, NULL) != 0)
		clear_data(data);
	while (data->nbr_p < i--)
	{
		if (pthread_join(data->philos[i].core, NULL) != 0)
			clear_data(data);
	}
}

void	init(char **av, t_data *data, int ac, pthread_mutex_t *forks)
{
	int	i;
	int	j;
	int	k;

	i = ft_atol(av[1]);
	j = 0;
	data->nbr_p = i;
	while (j < i)
	{
		k = j;
		data->philos[j].index = j + 1;
		data->philos[j].time_t_die = ft_atol(av[2]);
		data->philos[j].time_t_eat = ft_atol(av[3]);
		data->philos[j].time_t_sleep = ft_atol(av[4]);
		data->philos[j].ded = 0;
		data->philos[j].meals_eat = 0;
		data->philos[j].last_meal = 0;
		data->philos[j].dt = data;
		data->philos[j].fork = &forks[j];
		if (ac == 6)
			data->philos[j].need_t_eat = ft_atol(av[5]);
		else
			data->philos[j].need_t_eat = -1;
		data->philos[j].next = &data->philos[(j + 1) % i];
		data->philos[j].fork_n = &forks[(j + 1) % i];

		/*printf("index = %i, fork = %p, fork_n = %p\n",
			data->philos[j].index,
			(void *)data->philos[j].fork,
			(void *)data->philos[j].fork_n);*/
		j++;
	}
}

int	main(int ac, char **av)
{
	t_data				*data;
	t_philo				philo[PHILOMAX];
	pthread_mutex_t		forks[PHILOMAX];
	
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
	init(av, data, ac, forks);
	init_p(data);
	free(data);
	//clear_data(data);
}
