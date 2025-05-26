/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:34:44 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/26 18:37:07 by ssoukoun         ###   ########.fr       */
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
    printf("%i a pris une fourchette\n", p1->index);
    pthread_mutex_lock(p1->fork_n);
    printf("%i a pris une deuxieme fourchette\n", p1->index);
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
    while (ch->need_t_eat != ch->meals_eat || ch->ded != 1)
    {
        dead_verif(ch);
        eat(ch);
        printf("%i is sleeping\n", ch->index);
        dead_verif(ch);
        time_to(ch->time_t_sleep);
        printf("%i is thinking\n", ch->index);
    }
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
        while (i < dateboyo->nbr_p)
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
    if (ft_get_time() - p->last_meal > p->time_t_die)
        p->ded = 1;

}
