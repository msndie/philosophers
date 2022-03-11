/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:19:41 by sclam             #+#    #+#             */
/*   Updated: 2021/12/12 21:53:55 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_init_list(t_struct *stct)
{
	t_phil	*tmp;
	int		i;

	i = 1;
	stct->first = ft_lst_new(i, stct);
	if (!stct->first)
		exit(EXIT_FAILURE);
	tmp = stct->first;
	tmp->numb = i++;
	while (i <= stct->phils)
	{
		if (ft_lst_add_back(stct->first, ft_lst_new(i++, stct)) != 0)
		{
			ft_lst_clear(stct->first, stct->phils, ERROR);
			exit(EXIT_FAILURE);
		}
	}
	ft_lst_loop(stct);
}

static void	ft_time_and_sema(t_struct *stct)
{
	t_phil			*tmp;
	int				i;
	struct timeval	strt;
	long			start;

	tmp = stct->first;
	i = 0;
	gettimeofday(&strt, NULL);
	start = strt.tv_sec * 1000 + strt.tv_usec / 1000;
	while (i < stct->phils)
	{
		tmp->last_meal = start;
		tmp->start = start;
		tmp->forks = stct->forks;
		tmp->lock = stct->lock;
		tmp = tmp->next;
		i++;
	}
}

void	ft_init_struct(t_struct *stct, int argc, char **argv)
{
	if (argc == 6)
	{
		stct->notepme = ft_atoi_w_err(argv[5]);
		if (stct->notepme <= 0)
			exit(EXIT_FAILURE);
	}
	else
		stct->notepme = -1;
	stct->phils = ft_atoi_w_err(argv[1]);
	if (stct->phils <= 0)
		exit(EXIT_FAILURE);
	stct->ttd = ft_atoi_w_err(argv[2]);
	if (stct->ttd < 0)
		exit(EXIT_FAILURE);
	stct->tte = ft_atoi_w_err(argv[3]);
	if (stct->tte < 0)
		exit(EXIT_FAILURE);
	stct->tts = ft_atoi_w_err(argv[4]);
	if (stct->tts < 0)
		exit(EXIT_FAILURE);
	ft_init_list(stct);
}

void	ft_semaphore_init(t_struct *stct)
{
	sem_unlink("forks");
	sem_unlink("lock");
	stct->forks = sem_open("forks", O_CREAT, S_IRWXU, stct->phils);
	if (stct->forks == SEM_FAILED)
		exit(EXIT_FAILURE);
	stct->lock = sem_open("lock", O_CREAT, S_IRWXU, 1);
	if (stct->lock == SEM_FAILED)
	{
		sem_unlink("forks");
		exit(EXIT_FAILURE);
	}
	ft_time_and_sema(stct);
}
