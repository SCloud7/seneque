/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:59:00 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/26 15:54:26 by ssoukoun         ###   ########.fr       */
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
	pthread_mutex_t		forks[PHILOMAX];
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	data->philos = philo;
	data->philos = forks;
	if (ac != 5 && ac != 6)
		return (printf("arg incorrect"), 0);
	if (verif(av, ac) == -1)
		exit(0);
	init(av, data, ac);
	init_p(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:34:44 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/19 14:27:02 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int time_to(size_t time)
{
    usleep(time * 1000);
    return (0);
}

void    eat(t_philo *p1)
{
    p1->eating = 1;
    pthread_mutex_lock(p1->fork_r);
    printf("%i a pris une fourchette\n", p1->index);
    pthread_mutex_lock(p1->fork_l);
    printf("%i a pris une deuxieme fourchette\n", p1->index);
    printf("%i is eating\n", p1->index);
    time_to(p1->time_t_eat);
    pthread_mutex_unlock(p1->fork_r);
    pthread_mutex_unlock(p1->fork_l);
    p1->eating = 0;
    p1->meals_eat++;
    p1->last_meal = ft_get_time();
}

void    *routine(void *cho)
{
    t_philo *ch;

    ch = (t_philo *)cho;
    /*while (ch->need_t_eat != ch->meals_eat || ch->ded != 1)
    {
        dead_verif(ch);
        eat(ch);
        printf("%i is sleeping\n", ch->index);
        dead_verif(ch);
        time_to(ch->time_t_sleep);
        printf("%i is thinking\n", ch->index);
    }*/
    return(cho) ;
}

void    *end_v(void *data)
{
    int i;
    t_data *dateboyo;

    i = 0;
    dateboyo = (t_data*) data;
    while (1)
    {
        
        i = 1;
        while (&dateboyo->philos[i])
        {
            printf("need eat %i\neat meal%i\nded%i\net le i = %i\n\n\n\n",
        dateboyo->philos[i].need_t_eat,
        dateboyo->philos[i].meals_eat,
        dateboyo->philos[i].ded,
        dateboyo->philos->index);
            if (dateboyo->philos[i].meals_eat > dateboyo->philos[i].need_t_eat)
                return (printf("pitie %i\n", dateboyo->philos[i].meals_eat), data);
            if (dateboyo->philos[i].ded >= 1 )
                return (printf("pitie2\n"), data);
            i++;
        }
    }
    free(data);
}


size_t  ft_get_time(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    dead_verif(t_philo *p)
{
    if (p->last_meal > p->time_t_eat)
        p->ded = 1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:54:20 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/01/25 16:10:11 by ssoukoun         ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:02:31 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/26 15:51:55 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:52:14 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/01/25 16:03:46 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:59:00 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/28 14:39:29 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	verif(char **av, int ac)
{
	if (ft_atol(av[1]) <= 1 || ft_isdigit(av[1] == 0) || ft_atol(av[1]) > 200)
		return(printf("arg incorrect1"), -1);
	if (ft_atol(av[2]) <= 0 || ft_isdigit(av[2] == 0))
		return(printf("arg incorrect2"), -1);
	if (ft_atol(av[3]) <= 0 || ft_isdigit(av[3] == 0))
		return(printf("arg incorrect3"), -1);
	if (ft_atol(av[4]) <= 0 || ft_isdigit(av[4] == 0))
		return(printf("arg incorrect4"), -1);
	if(ac == 6)
	{
		if (ft_atol(av[5]) <= 0 || ft_isdigit(av[5] == 0))
			return(printf("arg incorrect5"), -1);
	}
	return (0);

}

void	init_p(t_data *data)
{
	int			i;
	pthread_t	jefe;
	t_philo		*fifi;

	i = 0;
	data->start_time = ft_get_time();
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

		printf("index = %i, fork = %p, fork_n = %p eat %zu sleep %zu die %zu \n",
			data->philos[j].index,
			(void *)data->philos[j].fork,
			(void *)data->philos[j].fork_n,
			data->philos[j].time_t_eat,
			data->philos[j].time_t_sleep,
			data->philos[j].time_t_die);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:34:44 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/28 14:43:40 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int time_to(size_t time)
{
    usleep(time * 1000);
    return (0);
}

void    eat(t_philo *p1)
{
    p1->eating = 1;
    pthread_mutex_lock(p1->fork);
    dead_verif(p1);
    printf("%i a pris la fourchette une\n", p1->index);
    pthread_mutex_lock(p1->fork_n);
    printf("%i a pris une deuxieme fourchette\n", p1->index);
    dead_verif(p1);
    printf("%i is eating\n", p1->index);
    time_to(p1->time_t_eat);
    pthread_mutex_unlock(p1->fork);
    pthread_mutex_unlock(p1->fork_n);
    p1->eating = 0;
    p1->meals_eat++;
    p1->last_meal = ft_get_time();
}

void    *routine(void *cho)
{
    t_philo *ch;

    ch = (t_philo *)cho;
    if (ch->index % 2 == 1)
        usleep(1000);
    while (ch->need_t_eat != ch->meals_eat || ch->ded != 1)
    {
        eat(ch);
        dead_verif(ch);
        printf("%i amange : %i\n", ch->index, ch->meals_eat);
    	time_to(ch->time_t_sleep);
        dead_verif(ch);
        printf("%i is sleeping\n", ch->index);
        time_to(ch->time_t_sleep);
        printf("%i is thinking\n", ch->index);
        dead_verif(ch);
    }
    return(cho) ;
}

void    *end_v(void *data)
{
    int i;
    int j;
    t_data *dateboyo;

    i = 0;
    dateboyo = (t_data*) data;
    j = dateboyo->philos->need_t_eat;
    while (1)
    {
        
        i = 0;
        while (i < dateboyo->nbr_p)
        {
            //printf("Looking...\n");
            if (dateboyo->philos[i].meals_eat > dateboyo->philos[i].need_t_eat && j != -1)
                return (printf("tout mange %i\n", dateboyo->philos[i].need_t_eat), data);
            if (dateboyo->philos[i].ded >= 1 )
            {
                clear_data(data);
                printf("dead phiphi\n");
                return (data);
            }
            i++;
        }
    }
    clear_data(data);
}


size_t  ft_get_time(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    dead_verif(t_philo *p)
{
    size_t start;
    
    start = p->dt->start_time;
    printf("start = %zu\n", start);
    if (start - p->last_meal > p->time_t_die)
        p->ded = 1;

}
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
