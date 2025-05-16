/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:31:09 by musisman          #+#    #+#             */
/*   Updated: 2024/11/03 01:26:42 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	number_digit(int n)
{
	size_t	i;

	if (n <= 0)
		i = 1;
	else
		i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void	fill_str(char *a, int n, size_t len)
{
	if (n <= 0)
	{
		if (n == 0)
			a[0] = '0';
		else if (n == -2147483648)
		{
			a[0] = '-';
			a[1] = '2';
			n = 147483648;
		}
		else
		{
			a[0] = '-';
			n = -n;
		}
	}
	while (n > 0)
	{
		a[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*a;

	len = number_digit(n);
	a = ft_calloc(len + 1, sizeof(char));
	if (!a)
		return (NULL);
	fill_str(a, n, len);
	return (a);
}
