/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:28:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 16:02:39 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

bool			philo_take_forks(t_philo *philo);
static inline u_long	get_ms_time(void);

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
	return (this->meals_left != 0);
}

void	philo_log(const t_philo *this, const char *log_txt)
{
	const u_long	timestamp = get_ms_time() - this->start_time;

	pthread_mutex_lock(&this->table->state_mutex);
	if (this->table->state == RUNNING)
	{
		printf("%lu %lu %s\n", timestamp, this->id, log_txt);
	}
	pthread_mutex_unlock(&this->table->state_mutex);
}

bool	philo_msleep(t_philo *this, u_long ms_delay)
{
	const u_long	end = get_ms_time() + ms_delay;
	u_long			cur_time;

	while (table_get_state(this->table) == RUNNING)
	{
		cur_time = get_ms_time();
		if (cur_time >= end)
			return (true);
		else if (cur_time - this->last_meal_time \
				> (u_long)this->table->time_to_die)
			return (philo_died(this, cur_time));
		usleep(100);
	}
	return (true);
}

bool	philo_died(t_philo *this, u_long death_time)
{
	pthread_mutex_lock(&this->table->state_mutex);
	if (this->table->state != GRIEF)
	{
		this->table->state = GRIEF;
		printf("%lu %lu %s\n", \
				death_time - this->start_time, this->id, DIED);
	}
	pthread_mutex_unlock(&this->table->state_mutex);
	return (false);
}

static inline u_long	get_ms_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
