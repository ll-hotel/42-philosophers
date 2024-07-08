/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:28:32 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/19 22:07:23 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static bool	__take_fork(t_philo *this, t_fork *fork);

void	philo_log(const t_philo *this, const char *log_txt)
{
	const u_long	timestamp = get_ms_time() - this->table->start_time;

	if (table_get_state(this->table) != END || log_txt[0] == 'd')
		printf("%lu %lu %s\n", timestamp, this->id, log_txt);
}

void	philo_take_forks(t_philo *this)
{
	bool	took_left;
	bool	took_right;

	took_left = false;
	took_right = false;
	while ((!took_left || !took_right) && table_get_state(this->table) != END)
	{
		if (!took_left)
			took_left = __take_fork(this, this->left_fork);
		if (!took_right)
			took_right = __take_fork(this, this->right_fork);
	}
}

void	philo_leave_forks(t_philo *this)
{
	pthread_mutex_lock(&this->left_fork->mutex);
	this->left_fork->taken = false;
	pthread_mutex_unlock(&this->left_fork->mutex);
	pthread_mutex_lock(&this->right_fork->mutex);
	this->right_fork->taken = false;
	pthread_mutex_unlock(&this->right_fork->mutex);
}

static bool	__take_fork(t_philo *this, t_fork *fork)
{
	bool	was_taken;

	pthread_mutex_lock(&fork->mutex);
	was_taken = fork->taken;
	fork->taken = true;
	pthread_mutex_unlock(&fork->mutex);
	if (!was_taken)
		philo_log(this, TOOK_FORK);
	return (!was_taken);
}

void	philo_msleep(const t_philo *this, u_long ms_delay)
{
	const u_long	start = get_ms_time();

	while (table_get_state(this->table) != END && \
			get_ms_time() - start < ms_delay)
		usleep(100);
}
