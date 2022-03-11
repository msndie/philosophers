/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:27:45 by sclam             #+#    #+#             */
/*   Updated: 2021/12/11 15:55:55 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_eat_helper(t_phil *philo)
{
	pthread_mutex_lock(&philo->next->fork);
	philo->is_eating = 1;
	if (*philo->end != 0)
		return ;
	philo->last_meal = *philo->curr_time;
	if (*philo->end == 0)
		printf("%ldms %d has taken a fork\n", *philo->curr_time
			- *philo->start, philo->numb);
	if (*philo->end != 0)
		return ;
	if (*philo->end == 0)
		printf("%ldms %d is eating\n", *philo->curr_time
			- *philo->start, philo->numb);
}

static void	ft_eating(t_phil *philo)
{
	pthread_mutex_lock(&philo->fork);
	if (*philo->end != 0)
		return ;
	if (*philo->end == 0)
		printf("%ldms %d has taken a fork\n", *philo->curr_time
			- *philo->start, philo->numb);
	ft_eat_helper(philo);
	ft_correct_usleep(philo->tte, philo);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	if (philo->notepme > 0)
		philo->notepme -= 1;
}

static void	ft_sleep(t_phil *philo)
{
	if (*philo->end != 0)
		return ;
	if (*philo->end == 0)
		printf("%ldms %d is sleeping\n", *philo->curr_time
			- *philo->start, philo->numb);
	ft_correct_usleep(philo->tts, philo);
}

static void	ft_think(t_phil *philo)
{
	if (*philo->end != 0)
		return ;
	if (*philo->end == 0)
		printf("%ldms %d is thinking\n", *philo->curr_time
			- *philo->start, philo->numb);
}

void	*ft_philo(void *ptr)
{
	t_phil	*philo;

	philo = (t_phil *)ptr;
	while (*philo->end == 0)
	{
		ft_eating(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}
