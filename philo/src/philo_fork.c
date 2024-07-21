/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:10:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 15:19:40 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <sys/time.h>
#include <unistd.h>

static inline bool	take_fork(t_philo *this, t_fork *fork);
static inline bool should_die(t_philo *this, u_long cur_time);

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
			took_left = take_fork(this, this->left_fork);
		if (!took_right)
			took_right = take_fork(this, this->right_fork);
		if (table_get_state(this->table) != RUNNING)
			return (false);
		gettimeofday(&tv, NULL);
		if (should_die(this, tv.tv_sec * 1000 + tv.tv_usec / 1000))
			return (philo_died(this, tv.tv_sec * 1000 + tv.tv_usec / 1000));
		usleep(100);
	}
	return (true);
}

void	philo_leave_forks(t_philo *this)
{
	pthread_mutex_lock(&this->left_fork->mutex);
	this->left_fork->available = true;
	pthread_mutex_unlock(&this->left_fork->mutex);
	pthread_mutex_lock(&this->right_fork->mutex);
	this->right_fork->available = true;
	pthread_mutex_unlock(&this->right_fork->mutex);
}

static inline bool	take_fork(t_philo *this, t_fork *fork)
{
	bool	was_available;

	pthread_mutex_lock(&fork->mutex);
	was_available = fork->available;
	fork->available = false;
	pthread_mutex_unlock(&fork->mutex);
	if (was_available)
		philo_log(this, TOOK_FORK);
	return (was_available);
}

static inline bool should_die(t_philo *this, u_long cur_time)
{
	return (cur_time - this->last_meal_time \
			> (u_long)this->table->time_to_die);
}
