/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:01:10 by sclam             #+#    #+#             */
/*   Updated: 2022/02/28 15:41:10 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_exit(t_struct *stct, int status)
{
	ft_mutex_destroy(stct);
	ft_lst_clear(stct->first, stct->phils, END);
	if (status == -1)
		write(2, "Mutex or pthread create error\n", 31);
	return (status);
}

static void	ft_unlock(t_struct *stct)
{
	int		i;
	t_phil	*tmp;

	i = 0;
	tmp = stct->first;
	while (i < stct->phils)
	{
		pthread_mutex_unlock(&tmp->fork);
		tmp = tmp->next;
		i++;
	}
}

static void	ft_time(t_struct *stct)
{
	struct timeval	time;

	while (stct->end == 0)
	{
		gettimeofday(&time, NULL);
		stct->curr_time = time.tv_sec * 1000 + time.tv_usec / 1000;
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	t_struct	stct;

	if (argc > 6 || argc < 5)
	{
		printf("Wrong number of arguments\n");
		return (-1);
	}
	stct.curr_time = 0;
	if (ft_init_struct(&stct, argc, argv) != 0)
		return (-1);
	if (ft_mutex_init(&stct) != 0)
		return (ft_exit(&stct, -1));
	if (pthread_create(&stct.wathcher, NULL, ft_watcher, (void *)&stct) != 0)
		return (ft_exit(&stct, -1));
	ft_time(&stct);
	usleep(1000);
	if (stct.end != 2)
		ft_unlock(&stct);
	pthread_join(stct.wathcher, NULL);
	return (ft_exit(&stct, 0));
}
