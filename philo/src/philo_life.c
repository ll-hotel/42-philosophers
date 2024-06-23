/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:17:15 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/26 18:34:31 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	philo_life(t_philo *self)
{
	t_fork *const	dead_philo = &self->world->dead_philo;
	struct timeval	tv[1];

	while (check_fork(dead_philo) != 0)
		usleep(100);
	self->start_time = ms_now(tv);
	self->last_meal_time = self->start_time;
	if (self->id % 2)
		ms_sleep(self, self->world->time_to_eat, &dead_philo->taken);

	while (self->meals_left != 0 && !check_fork(dead_philo))
	{
		if (take_fork(self, &dead_philo->taken, self->left))
			continue ;
		printf("%lu %lu has taken a fork\n", \
				ms_now(tv) - self->start_time, self->id);
		if (take_fork(self, &dead_philo->taken, self->right))
			continue ;
		printf("%lu %lu has taken a fork\n", \
				ms_now(tv) - self->start_time, self->id);
		if (check_self_death(self))
			continue ;
		self->last_meal_time = ms_now(tv);
		printf("%lu %lu is eating\n", self->last_meal_time - self->start_time, self->id);
		if (ms_sleep(self, self->world->time_to_eat, &dead_philo->taken))
			continue ;
		self->meals_left -= (self->meals_left > 0);

		leave_fork(self->left, 0);
		leave_fork(self->right, 0);
		printf("%lu %lu is sleeping\n", ms_now(tv) - self->start_time, self->id);
		if (ms_sleep(self, self->world->time_to_sleep, &dead_philo->taken))
			continue ;

		printf("%lu %lu is thinking\n", ms_now(tv) - self->start_time, self->id);
	}

	if (self->id == check_fork(dead_philo))
		printf("%lu %lu died\n", ms_now(tv) - self->start_time, self->id);
}
