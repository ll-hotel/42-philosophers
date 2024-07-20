/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:28:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 14:11:15 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

bool	philo_take_forks(t_philo *philo);

bool	philo_eat(t_philo *this)
{
	if (!philo_take_forks(this))
		return (false);
	philo_log(this, EATING);
	this->meals_left -= (this->meals_left > 0);
	this->last_meal_time = get_ms_time();
	if (!philo_msleep(this, this->table->time_to_eat))
		return (false);
	philo_leave_forks(this);
	return (true);
}

void	philo_log(const t_philo *this, const char *log_txt)
{
	const u_long	timestamp = get_ms_time() - this->table->start_time;

	pthread_mutex_lock(&this->table->state_mutex);
	if (this->table->state == RUNNING || \
			(this->table->state == 1 && log_txt[0] == 'd'))
	{
		printf("%lu %lu %s\n", timestamp, this->id, log_txt);
	}
	pthread_mutex_unlock(&this->table->state_mutex);
}

bool	philo_msleep(const t_philo *this, u_long ms_delay)
{
	const u_long	end = get_ms_time() + ms_delay;
	u_long			cur_time;

	while (table_get_state(this->table) == RUNNING)
	{
		cur_time = get_ms_time();
		if (cur_time >= ms_delay)
			return (true);
		else if (cur_time - this->last_meal_time > this->table->time_to_die)
		{
		}
		usleep(100);
	}
	return (true);
}

bool	philo_died(t_philo *this)
{
	pthread_mutex_lock(&this->table->state_mutex);
	this->table->state += 1;
	pthread_mutex_unlock(&this->table->state_mutex);
	philo_log(
	return (false);
}
