/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:28:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 00:13:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	philo_take_forks(t_philo *philo);

void	philo_eat(t_philo *this)
{
	philo_take_forks(this);
	philo_log(this, EATING);
	this->meals_left -= (this->meals_left > 0);
	this->last_meal_time = get_ms_time();
	philo_msleep(this, this->table->time_to_eat);
	philo_leave_forks(this);
}

void	philo_log(const t_philo *this, const char *log_txt)
{
	const u_long	timestamp = get_ms_time() - this->table->start_time;

	pthread_mutex_lock(&this->table->state_mutex);
	if (this->table->state != END || log_txt[0] == 'd')
		printf("%lu %lu %s\n", timestamp, this->id, log_txt);
	pthread_mutex_unlock(&this->table->state_mutex);
}

void	philo_msleep(const t_philo *this, u_long ms_delay)
{
	const u_long	end = get_ms_time() + ms_delay;

	while (table_get_state(this->table) != END && \
			get_ms_time() < end)
		usleep(100);
}
