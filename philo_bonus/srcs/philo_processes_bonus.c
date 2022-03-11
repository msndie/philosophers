/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:27:45 by sclam             #+#    #+#             */
/*   Updated: 2021/12/15 17:24:33 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_take_fork(t_phil *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->lock);
	printf("%ldms %d has taken a fork\n", (philo->current.tv_sec * 1000
			+ philo->current.tv_usec / 1000) - philo->start, philo->numb);
	sem_post(philo->lock);
}

static void	ft_eating(t_phil *philo)
{
	ft_take_fork(philo);
	ft_take_fork(philo);
	philo->is_eating = 1;
	philo->last_meal = philo->current.tv_sec * 1000
		+ philo->current.tv_usec / 1000;
	sem_wait(philo->lock);
	printf("%ldms %d is eating\n", philo->last_meal
		- philo->start, philo->numb);
	sem_post(philo->lock);
	ft_correct_usleep(philo->tte, philo);
	philo->is_eating = 0;
	sem_post(philo->forks);
	sem_post(philo->forks);
	if (philo->notepme > 0)
		philo->notepme -= 1;
}

static void	ft_sleep(t_phil *philo)
{
	sem_wait(philo->lock);
	printf("%ldms %d is sleeping\n", (philo->current.tv_sec * 1000
			+ philo->current.tv_usec / 1000) - philo->start, philo->numb);
	sem_post(philo->lock);
	ft_correct_usleep(philo->tts, philo);
}

static void	ft_think(t_phil *philo)
{
	sem_wait(philo->lock);
	printf("%ldms %d is thinking\n", (philo->current.tv_sec * 1000
			+ philo->current.tv_usec / 1000) - philo->start, philo->numb);
	sem_post(philo->lock);
}

void	ft_routine(t_phil *philo)
{
	if (pthread_create(&philo->watcher, NULL, ft_watcher_thread,
			(void *)philo) != 0)
	{
		sem_wait(philo->lock);
		exit(EXIT_FAILURE);
	}
	gettimeofday(&philo->current, NULL);
	while (1)
	{
		ft_eating(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
}
