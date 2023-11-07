/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:41:06 by mbatteux          #+#    #+#             */
/*   Updated: 2023/04/20 17:41:07 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	mod;
	int	div;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		div = n / 10;
		mod = n % 10;
		ft_putnbr_fd(div, fd);
	}
	if (n > 9)
		ft_putchar_fd(mod + '0', fd);
	else
		ft_putchar_fd(n + '0', fd);
}
