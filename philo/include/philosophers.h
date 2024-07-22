/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:56:47 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/22 16:12:54 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <sys/types.h>
# include <stdbool.h>
# define TOOK_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

enum	e_state
{
	RUNNING = 0,
	GRIEF = 42,
};

typedef struct s_fork
{
	t_mutex	mutex;
	u_long	available;
}	t_fork;

struct	s_philo
{
	pthread_t	thread;
	t_fork		own_fork;
	u_long		id;
	long		meals_left;
	u_long		start_time;
	u_long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_table		*table;
};

struct	s_table
{
	t_mutex		state_mutex;
	long		state;
	u_long		start_time;
	t_philo		*philos;
	pthread_t	monitoring_thread;
	long		meals_to_eat;
	long		philo_nb;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
};

bool	philo_eat(t_philo *philo);
bool	philo_msleep(t_philo *philo, u_long delay);
void	philo_log(const t_philo *philo, const char *log_txt);
bool	philo_died(t_philo *philo, u_long death_time);
void	philo_leave_forks(t_philo *philo);

bool	create_table(t_table *table, const char **argv);
void	free_table(t_table *table);
long	table_get_state(t_table *table);

bool	setup_routines(t_table *table);
void	philo_routine(t_philo *philo);
void	*philo_alone_routine(t_philo *philo);

void	*ft_calloc(size_t nmemb, size_t size);
long	ft_atol(const char *nptr);
void	puterr(const char *__s);

#endif
