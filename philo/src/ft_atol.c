/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:54:50 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/24 00:27:24 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static _Bool	_isspace(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

static _Bool	_isnum(char c)
{
	return ('0' <= c && c <= '9');
}

long	ft_atol(const char *nptr)
{
	long			rval;
	char			sign;
	unsigned int	i;

	if (!nptr)
		return (0);
	i = 0;
	while (_isspace(nptr[i]))
		i++;
	if (!nptr[i])
		return (0);
	sign = (nptr[i] == '-');
	i += ((nptr[i] == '-') || (nptr[i] == '+'));
	rval = 0;
	while (_isnum(nptr[i]))
		rval = 10 * rval + nptr[i++] - '0';
	return (rval * (sign == 0));
}
