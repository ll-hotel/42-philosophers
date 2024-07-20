/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:53:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 14:04:18 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	philo_routine(t_philo *this)
{
	pthread_mutex_lock(&this->table->state_mutex);
	pthread_mutex_unlock(&this->table->state_mutex);
	this->last_meal_time = this->table->start_time;
	if (this->id % 2 == 0)
	{
		philo_log(this, THINKING);
		usleep(500 * this->table->time_to_eat);
	}
	while (table_get_state(this->table) == RUNNING)
	{
		if (!philo_eat(this))
			break ;
		philo_log(this, SLEEPING);
		philo_msleep(this, this->table->time_to_sleep);
		philo_log(this, THINKING);
		usleep(100);
	}
	philo_leave_forks(this);
}

void	*philo_alone_routine(t_philo *this)
{
	pthread_mutex_lock(&this->table->state_mutex);
	pthread_mutex_unlock(&this->table->state_mutex);
	this->last_meal_time = this->table->start_time;
	philo_log(this, TOOK_FORK);
	philo_msleep(this, this->table->time_to_die);
	return (NULL);
}
