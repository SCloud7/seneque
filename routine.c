/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:34:44 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/16 18:10:39 by ssoukoun         ###   ########.fr       */
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
    //printf("need eat %i\n eat meal%i\nded%i\n", ch->need_t_eat, ch->meals_eat, ch->ded);
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

    dateboyo = (t_data*) data;

    while (1)
    {
        i = 0;
        while (dateboyo->philos[i].ded != 1 || dateboyo->philos[i].meals_eat < dateboyo->philos[i].need_t_eat)
            i++;
    }
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
