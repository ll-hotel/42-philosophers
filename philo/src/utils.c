/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:16:29 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/07/21 14:01:12 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (p)
		memset(p, 0, nmemb * size);
	return (p);
}

inline u_long	get_ms_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_atol(const char *s)
{
	long	value;
	int		negative;
	int		i;

	value = 0;
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	negative = (s[i] != '-') - (s[i] == '-');
	i += (s[i] == '-' || s[i] == '+');
	while ('0' <= s[i] && s[i] <= '9')
		value = (value * 10) + (s[i++] - '0');
	return (negative * value);
}

void	puterr(const char *__s)
{
	unsigned int	i;

	i = 0;
	while (__s[i])
		i += 1;
	write(2, __s, i);
}
