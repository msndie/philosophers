/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:35:22 by sclam             #+#    #+#             */
/*   Updated: 2021/12/13 15:18:22 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check_notepme(t_struct *stct)
{
	int		i;
	int		n;
	t_phil	*tmp;

	i = 0;
	n = 0;
	tmp = stct->first;
	while (i < stct->phils)
	{
		if (tmp->notepme == 0)
			n++;
		tmp = tmp->next;
		i++;
	}
	if (n == stct->phils)
	{
		stct->end = 1;
		return (0);
	}
	return (1);
}

static int	ft_check_death(t_struct *stct)
{
	t_phil			*tmp;

	tmp = stct->first;
	while (tmp)
	{
		if (stct->curr_time > tmp->last_meal)
		{
			if (!tmp->is_eating && tmp->ttd < stct->curr_time - tmp->last_meal)
			{
				stct->end = 1;
				printf("%ldms %d died\n", stct->curr_time
					- stct->start, tmp->numb);
				break ;
			}
		}
		if (ft_check_notepme(stct) == 0)
			break ;
		if (tmp->next->numb == 1)
			usleep(100);
		tmp = tmp->next;
	}
	return (0);
}

static void	*ft_wait(t_struct *stct)
{
	t_phil	*tmp;
	int		i;

	i = 0;
	tmp = stct->first;
	while (i < stct->phils)
	{
		if (stct->phils == 1)
			pthread_mutex_unlock(&tmp->fork);
		pthread_join(tmp->t, NULL);
		tmp = tmp->next;
		i++;
	}
	stct->end = 2;
	return (0);
}

static int	ft_threads_create(t_struct *stct)
{
	t_phil	*tmp;
	int		i;

	i = -1;
	tmp = stct->first;
	while (++i < stct->phils)
	{
		if (i % 2 == 0)
			if (pthread_create(&tmp->t, NULL, ft_philo, (void *)tmp) != 0)
				return (-1);
		tmp = tmp->next;
	}
	usleep(1000);
	i = -1;
	while (++i < stct->phils)
	{
		if (i % 2 == 1)
			if (pthread_create(&tmp->t, NULL, ft_philo, (void *)tmp) != 0)
				return (-1);
		tmp = tmp->next;
	}
	return (0);
}

void	*ft_watcher(void *ptr)
{
	t_struct		*stct;

	stct = (t_struct *)ptr;
	ft_init_start_time(stct);
	if (ft_threads_create(stct) != 0)
	{
		ft_wait(stct);
		write(2, "Pthread create error\n", 22);
		return (0);
	}
	ft_check_death(stct);
	return (ft_wait(stct));
}
