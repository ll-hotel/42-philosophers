/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:17:15 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/29 10:34:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static bool	philo_eat(t_philo *this, t_fork *dead_philo, struct timeval *tv);


void	philo_life(t_philo *this)
{
	t_fork *const	dead_philo = &this->world->dead_philo;
	struct timeval	tv[1];

	while (check_fork(dead_philo) != 0 && \
			check_fork(dead_philo) != this->world->philo_number + 1)
		usleep(100);
	this->start_time = ms_now(tv);
	this->last_meal_time = this->start_time;
	if (this->id % 2)
		ms_sleep(this, this->world->time_to_eat, &dead_philo->taken);

	while (this->meals_left != 0 && !check_fork(dead_philo))
	{
		if (!philo_eat(this, dead_philo, tv))
			continue ;
		leave_fork(this->left, 0);
		leave_fork(this->right, 0);
		printf("%lu %lu is sleeping\n", ms_now(tv) - this->start_time, this->id);
		if (ms_sleep(this, this->world->time_to_sleep, &dead_philo->taken))
			continue ;
		printf("%lu %lu is thinking\n", ms_now(tv) - this->start_time, this->id);
	}
	if (this->id == check_fork(dead_philo))
		printf("%lu %lu died\n", ms_now(tv) - this->start_time, this->id);
}

static bool	philo_eat(t_philo *this, t_fork *dead_philo, struct timeval *tv)
{
	if (take_fork(this, &dead_philo->taken, this->left))
		return (false);
	printf("%lu %lu has taken a fork\n", \
			ms_now(tv) - this->start_time, this->id);
	if (take_fork(this, &dead_philo->taken, this->right))
		return (false);
	printf("%lu %lu has taken a fork\n", \
			ms_now(tv) - this->start_time, this->id);
	if (check_self_death(this))
		return (false);
	this->last_meal_time = ms_now(tv);
	printf("%lu %lu is eating\n", this->last_meal_time - this->start_time, \
			this->id);
	if (ms_sleep(this, this->world->time_to_eat, &dead_philo->taken))
		return (false);
	this->meals_left -= (this->meals_left > 0);
	return (true);
}
