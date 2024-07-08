/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:36:37 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/18 15:44:48 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	table_get_state(t_table *table)
{
	long	tmp;

	pthread_mutex_lock(&table->state_mutex);
	tmp = table->state;
	pthread_mutex_unlock(&table->state_mutex);
	return (tmp);
}

void	table_set_state(t_table *table, long value)
{
	pthread_mutex_lock(&table->state_mutex);
	table->state = value;
	pthread_mutex_unlock(&table->state_mutex);
}
