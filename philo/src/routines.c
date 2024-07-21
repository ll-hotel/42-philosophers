/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:53:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 15:15:06 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static u_long	get_ms_now(void);

void	philo_routine(t_philo *this)
{
	pthread_mutex_lock(&this->table->state_mutex);
	pthread_mutex_unlock(&this->table->state_mutex);
	usleep(500);
	this->start_time = get_ms_now();
	this->last_meal_time = this->start_time;
	if (this->id % 2 == 0)
	{
		philo_log(this, THINKING);
		usleep(500 * this->table->time_to_eat);
	}
	while (true)
	{
		if (!philo_eat(this))
			break ;
		philo_log(this, SLEEPING);
		philo_msleep(this, this->table->time_to_sleep);
		philo_log(this, THINKING);
		usleep(100);
	}
	philo_leave_forks(this);
	philo_log(this, THINKING);
}

void	*philo_alone_routine(t_philo *this)
{
	pthread_mutex_lock(&this->table->state_mutex);
	pthread_mutex_unlock(&this->table->state_mutex);
	this->start_time = get_ms_now();
	this->last_meal_time = this->start_time;
	philo_log(this, TOOK_FORK);
	philo_msleep(this, this->table->time_to_die + 10);
	return (NULL);
}

static u_long	get_ms_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
