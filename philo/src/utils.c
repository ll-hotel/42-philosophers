/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:57:15 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/26 19:06:40 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

int	check_this_death(t_philo *this)
{
	struct timeval	tv[1];
	u_long	now;

	now = ms_now(tv);
	if (now - this->last_meal_time > this->world->time_to_die)
	{
		pthread_mutex_lock(this->world->dead_philo.mutex);
		if (this->world->dead_philo.taken == 0)
			this->world->dead_philo.taken = this->id;
		pthread_mutex_unlock(this->world->dead_philo.mutex);
		return (1);
	}
	return (0);
}

u_long	ms_sleep(t_philo *philo, u_long ms_delay, u_long *dead_philo)
{
	struct timeval	tv[1];
	const u_long	start = ms_now(tv);

	while (ms_now(tv) - start < ms_delay && !*dead_philo)
	{
		check_this_death(philo);
		usleep(49);
	}
	return (*dead_philo);
}

u_long	ms_now(struct timeval *tv)
{
	gettimeofday(tv, NULL);
	return (tv->tv_sec * 1000 + tv->tv_usec / 1000);
}
