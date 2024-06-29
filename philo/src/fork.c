/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 05:49:25 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 06:04:11 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

u_long	take_fork(t_philo *philo, u_long *dead_philo, t_fork *fork)
{
	pthread_mutex_lock(fork->mutex);
	check_this_death(philo);
	while (fork->taken && !*dead_philo)
	{
		pthread_mutex_unlock(fork->mutex);
		usleep(50);
		pthread_mutex_lock(fork->mutex);
		check_this_death(philo);
	}
	if (!fork->taken)
		fork->taken = 1;
	pthread_mutex_unlock(fork->mutex);
	return (*dead_philo);
}

void	leave_fork(t_fork *fork, u_long value)
{
	pthread_mutex_lock(fork->mutex);
	fork->taken = value;
	pthread_mutex_unlock(fork->mutex);
}

u_long	check_fork(t_fork *fork)
{
	u_long	value;

	pthread_mutex_lock(fork->mutex);
	value = fork->taken;
	pthread_mutex_unlock(fork->mutex);
	return (value);
}
