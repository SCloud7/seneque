/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:34:44 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/28 16:15:14 by ssoukoun         ###   ########.fr       */
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
    printf("%i a pris la fourchette une\n", p1->index);
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
    if (ch->index % 2 == 1)
        usleep(1000);
    while (ch->need_t_eat != ch->meals_eat || ch->ded != 1)
    {
        eat(ch);
        dead_verif(ch);
        printf("%i a mange : %i\n", ch->index, ch->meals_eat);
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
            usleep(100);
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
    if (start - p->last_meal > p->time_t_die)
        p->dt->dead_flag = 1;
}
