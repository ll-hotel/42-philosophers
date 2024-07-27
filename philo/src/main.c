/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:45:52 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/27 19:40:14 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, const char **argv)
{
	t_table	table;
	int		error;

	if (argc < 5 || argc > 6)
	{
		puterr("philo_nb time_to_die time_to_eat time_to_sleep" \
				" [meals_to_eat]\n");
		return (1);
	}
	error = 0;
	if (create_table(&table, argv))
		error = start_philosophers(&table) == false;
	else
		error = 1;
	free_table(&table);
	return (error);
}
