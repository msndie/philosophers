/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:30:00 by sclam             #+#    #+#             */
/*   Updated: 2021/12/12 20:24:05 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_correct_usleep(unsigned int n, t_phil *philo)
{
	unsigned long	time;
	unsigned long	diff;

	if (n == 0)
		return ;
	time = philo->current.tv_sec * 1000 + philo->current.tv_usec / 1000;
	while (1)
	{
		usleep(250);
		diff = (philo->current.tv_sec * 1000
				+ philo->current.tv_usec / 1000) - time;
		if (diff >= n)
			return ;
	}
}

int	ft_atoi_w_err(const char *str)
{
	long	result;

	result = 0;
	if (*str == '-' || *str == '+')
		return (-1);
	if (!(*str <= '9' && *str >= '0'))
		return (-1);
	while (*str <= '9' && *str >= '0')
		result = result * 10 + (*str++ - '0');
	if (*str != '\0')
		return (-1);
	if (result > 2147483647)
		return (-1);
	return (result);
}
