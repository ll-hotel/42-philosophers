/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ll-hotel <ll-hotel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:17:28 by ll-hotel          #+#    #+#             */
/*   Updated: 2024/06/23 23:47:25 by ll-hotel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;
	size_t			bytes;

	bytes = nmemb * size;
	if ((bytes < nmemb && size) || (bytes < size && nmemb))
		return (NULL);
	p = malloc(bytes);
	if (!p)
		return (NULL);
	memset(p, 0, bytes);
	return (p);
}
