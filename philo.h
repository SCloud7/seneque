/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoukoun <ssoukoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:34:01 by ssoukoun          #+#    #+#             */
/*   Updated: 2025/05/28 16:14:46 by ssoukoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include<unistd.h>
# include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

#ifndef PHILO_H
# define PHILO_H
# define PHILOMAX 200
typedef struct s_philo t_philo;

typedef struct s_data
{
	t_philo					*philos;
	int						meals;
	int						dead_flag;
	pthread_mutex_t			windows;
	int			f_t_eat;
	int			nbr_p;
	size_t			start_time;
}   t_data;
struct s_philo
{
	pthread_t		core;
	size_t			time_t_die;
	size_t			time_t_eat;
	size_t			time_t_sleep;
	size_t			last_meal;
	size_t			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*fork_n;
	int				index;
	int 			eating;
	int 			meals_eat;
	int				need_t_eat;
	int				nbr_p;
	int				ded;
	t_data			*dt;
	t_philo			*next;

};



long	ft_atol(const char *str);
int		ft_isdigit(int c);
void    *end_v(void*);
size_t  ft_get_time(void);
void    dead_verif(t_philo *p);
void    *routine(void*cho);
void	clear_data(t_data *data);
#endif