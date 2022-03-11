/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:30:00 by sclam             #+#    #+#             */
/*   Updated: 2022/02/28 15:43:20 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_mutex_destroy(t_struct *stct)
{
	int		i;
	t_phil	*tmp;

	i = 0;
	tmp = stct->first;
	while (i < stct->phils)
	{
		pthread_mutex_destroy(&tmp->fork);
		tmp = tmp->next;
		i++;
	}
}

void	ft_correct_usleep(unsigned int n, t_phil *philo)
{
	unsigned long	time;
	unsigned long	diff;

	if (*philo->end != 0)
		return ;
	if (n == 0)
		return ;
	time = *philo->curr_time;
	while (1)
	{
		usleep(250);
		diff = *philo->curr_time - time;
		if (diff >= n || *philo->end != 0)
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
