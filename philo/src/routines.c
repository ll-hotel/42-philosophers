/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:53:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 00:16:28 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static bool	philo_must_die(t_philo *this);

void	philo_routine(t_philo *this)
{
	while (table_get_state(this->table) == WAIT)
		usleep(100);
	this->last_meal_time = this->table->start_time;
	pthread_mutex_lock(&this->table->state_mutex);
	this->table->state += 1;
	pthread_mutex_unlock(&this->table->state_mutex);
	if (this->id % 2 == 0)
	{
		philo_log(this, THINKING);
		usleep(500 * this->table->time_to_eat);
	}
	while (table_get_state(this->table) != END)
	{
		philo_eat(this);
		philo_log(this, SLEEPING);
		philo_msleep(this, this->table->time_to_sleep);
		philo_log(this, THINKING);
		usleep(100);
	}
	philo_leave_forks(this);
}

void	monitoring_routine(t_table *this)
{
	long	i;
	bool	no_more_meal;

	while (table_get_state(this) != START)
		usleep(100);
	while (this->state != END)
	{
		usleep(500);
		i = 0;
		no_more_meal = 1;
		while (i < this->philo_nb)
		{
			if (philo_must_die(&this->philos[i]))
			{
				table_set_state(this, END);
				philo_log(&this->philos[i], DIED);
				return ;
			}
			no_more_meal &= (this->philos[i].meals_left == 0);
			i++;
		}
		if (no_more_meal)
			table_set_state(this, END);
	}
}

void	*philo_alone_routine(t_philo *this)
{
	while (table_get_state(this->table) == WAIT)
		usleep(100);
	this->last_meal_time = this->table->start_time;
	pthread_mutex_lock(&this->table->state_mutex);
	this->table->state += 1;
	pthread_mutex_unlock(&this->table->state_mutex);
	philo_log(this, TOOK_FORK);
	philo_msleep(this, this->table->time_to_die);
	return (NULL);
}

static bool	philo_must_die(t_philo *this)
{
	return (get_ms_time() - this->last_meal_time \
			> (u_long)this->table->time_to_die);
}
