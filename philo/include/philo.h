/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:56:47 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 06:02:54 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/types.h>
# include <stdbool.h>

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_world	t_world;

struct	s_fork
{
	u_long			taken;
	pthread_mutex_t	mutex[1];
};

struct	s_philo
{
	u_long	id;
	u_long	meals_left;
	u_long	start_time;
	u_long	last_meal_time;
	t_fork	*left;
	t_fork	*right;
	t_world	*world;
};

struct	s_world
{
	u_long		time_to_die;
	u_long		time_to_eat;
	u_long		time_to_sleep;
	long		meals_number;
	u_long		philo_number;
	t_fork		dead_philo;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	*threads;
};

bool	alloc_world_entities(t_world *world);
void	threading(t_world *world);
void	philo_life(t_philo *self);
void	free_world_entities(t_world *world);

void	*ft_calloc(size_t nmemb, size_t size);
long	ft_atol(const char *nptr);

int		check_self_death(t_philo *self);
u_long	ms_sleep(t_philo *philo, u_long ms_delay, u_long *dead_philo);
u_long	ms_now(struct timeval *tv);

u_long	take_fork(t_philo *philo, u_long *dead_philo, t_fork *fork);
void	leave_fork(t_fork *fork, u_long value);
u_long	check_fork(t_fork *fork);

#endif
