/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:10:41 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 00:11:03 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

static bool	__take_fork(t_philo *this, t_fork *fork);

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
		usleep(100);
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
