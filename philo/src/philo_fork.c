/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:10:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 14:09:14 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

static bool	__take_fork(t_philo *this, t_fork *fork);

bool	philo_take_forks(t_philo *this)
{
	struct timeval	tv;
	bool			took_left;
	bool			took_right;

	took_left = false;
	took_right = false;
	while (!took_left || !took_right)
	{
		if (!took_left)
			took_left = __take_fork(this, this->left_fork);
		if (!took_right)
			took_right = __take_fork(this, this->right_fork);
		if (table_get_state(this->table) != RUNNING)
			return (false);
		gettimeofday(&tv, NULL);
		if ((tv.tv_sec * 1000 + tv.tv_usec / 1000) > this->table->time_to_die)
		{
			pthread_mutex_lock(&this->table->state_mutex);
			this->table->state += 1;
			pthread_mutex_unlock(&this->table->state_mutex);
			return (false);
		}
		usleep(100);
	}
	return (true);
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
