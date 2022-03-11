/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:35:22 by sclam             #+#    #+#             */
/*   Updated: 2021/12/13 14:26:20 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*ft_watcher_thread(void *ptr)
{
	t_phil	*philo;

	philo = (t_phil *)ptr;
	pthread_detach(philo->watcher);
	while (1)
	{
		gettimeofday(&philo->current, NULL);
		if ((philo->current.tv_sec * 1000
				+ philo->current.tv_usec / 1000) > philo->last_meal)
		{
			if (!philo->is_eating && philo->ttd < (philo->current.tv_sec * 1000
					+ philo->current.tv_usec / 1000) - philo->last_meal)
			{
				sem_wait(philo->lock);
				printf("%ldms %d died\n", (philo->current.tv_sec * 1000
						+ philo->current.tv_usec / 1000)
					- philo->start, philo->numb);
				break ;
			}
		}
		if (philo->notepme == 0)
			exit(EXIT_SUCCESS);
		usleep(100);
	}
	exit(EXIT_FAILURE);
}
