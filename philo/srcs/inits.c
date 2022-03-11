/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:19:41 by sclam             #+#    #+#             */
/*   Updated: 2021/12/11 15:24:11 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_init_list(t_struct *stct)
{
	t_phil	*tmp;
	int		i;

	i = 1;
	stct->first = ft_lst_new(i, stct);
	if (!stct->first)
		return (-1);
	tmp = stct->first;
	tmp->numb = i++;
	while (i <= stct->phils)
	{
		if (ft_lst_add_back(stct->first, ft_lst_new(i++, stct)) != 0)
		{
			ft_lst_clear(stct->first, stct->phils, ERROR);
			return (-1);
		}
	}
	ft_lst_loop(stct);
	return (0);
}

void	ft_init_start_time(t_struct *stct)
{
	t_phil			*tmp;
	int				i;
	struct timeval	strt;

	tmp = stct->first;
	i = 0;
	gettimeofday(&strt, NULL);
	stct->start = strt.tv_sec * 1000 + strt.tv_usec / 1000;
	while (i < stct->phils)
	{
		tmp->last_meal = stct->start;
		tmp->start = &stct->start;
		tmp->curr_time = &stct->curr_time;
		tmp = tmp->next;
		i++;
	}
}

int	ft_mutex_init(t_struct *stct)
{
	t_phil	*tmp;
	int		i;

	i = 0;
	tmp = stct->first;
	while (i < stct->phils)
	{
		if (pthread_mutex_init(&tmp->fork, NULL) != 0)
			return (-1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int	ft_init_struct(t_struct *stct, int argc, char **argv)
{
	if (argc == 6)
	{
		stct->notepme = ft_atoi_w_err(argv[5]);
		if (stct->notepme <= 0)
			return (-1);
	}
	else
		stct->notepme = -1;
	stct->phils = ft_atoi_w_err(argv[1]);
	if (stct->phils <= 0)
		return (-1);
	stct->ttd = ft_atoi_w_err(argv[2]);
	if (stct->ttd < 0)
		return (-1);
	stct->tte = ft_atoi_w_err(argv[3]);
	if (stct->tte < 0)
		return (-1);
	stct->tts = ft_atoi_w_err(argv[4]);
	if (stct->tts < 0)
		return (-1);
	if (ft_init_list(stct) != 0)
		return (-1);
	stct->end = 0;
	return (0);
}
