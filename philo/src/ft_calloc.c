/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: acourtar <acourtar@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 21:31:45 by acourtar      #+#    #+#                 */
/*   Updated: 2024/01/25 21:31:45 by acourtar      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	*ft_memset(void *s, int c, size_t n)
{
	void			*ptr;
	unsigned char	c_uchar;

	ptr = s;
	c_uchar = (unsigned char)c;
	while (n > 0)
	{
		*(unsigned char *)ptr = c_uchar;
		n--;
		ptr++;
	}
	return (s);
}

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*array;

	array = malloc(nelem * elsize);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, nelem * elsize);
	return (array);
}
