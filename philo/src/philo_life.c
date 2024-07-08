/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:17:15 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/08 09:52:28 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static bool	philo_eat(t_philo *this, t_fork *dead_philo);

void	philo_life(t_philo *this)
{
	t_fork *const	dead_philo = &this->world->dead_philo;

	while (check_fork(dead_philo) != 0 && \
			check_fork(dead_philo) != this->world->philo_nb + 1)
		usleep(100);
	this->start_time = ms_now();
	this->last_meal_time = this->start_time;
	if (this->id % 2)
		ms_sleep(this, this->world->time_to_eat, &dead_philo->taken);
	while (this->meals_left != 0 && !check_fork(dead_philo))
	{
		if (!philo_eat(this, dead_philo))
			continue ;
		leave_fork(this->left, 0);
		leave_fork(this->right, 0);
		print_state(this, SLEEPING);
		if (ms_sleep(this, this->world->time_to_sleep, &dead_philo->taken))
			continue ;
		print_state(this, THINKING);
	}
	if (this->id == check_fork(dead_philo))
		print_state(this, DIED);
}

static bool	philo_eat(t_philo *this, t_fork *dead_philo)
{
	if (take_fork(this, &dead_philo->taken, this->left))
		return (false);
	print_state(this, TOOK_FORK);
	if (take_fork(this, &dead_philo->taken, this->right))
		return (false);
	print_state(this, TOOK_FORK);
	if (check_this_death(this))
		return (false);
	this->last_meal_time = ms_now();
	print_state(this, EATING);
	if (ms_sleep(this, this->world->time_to_eat, &dead_philo->taken))
		return (false);
	this->meals_left -= (this->meals_left > 0);
	return (true);
}
