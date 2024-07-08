/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 04:57:15 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/08 09:53:56 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	check_this_death(t_philo *this)
{
	if (ms_now() - this->last_meal_time > this->world->time_to_die)
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
	const u_long	start = ms_now();

	while (ms_now() - start < ms_delay && !*dead_philo)
	{
		check_this_death(philo);
		usleep(49);
	}
	return (*dead_philo);
}

u_long	ms_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_state(t_philo *this, enum e_state state)
{
	const char	*messages[] = { \
		"%lu %lu has taken a fork\n", \
		"%lu %lu is eating\n", \
		"%lu %lu is sleeping\n", \
		"%lu %lu is thinking\n", \
		"%lu %lu died\n"};

	printf(messages[state], ms_now() - this->start_time, this->id);
}
