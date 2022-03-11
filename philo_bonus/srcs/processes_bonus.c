/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 20:14:49 by sclam             #+#    #+#             */
/*   Updated: 2021/12/15 17:24:37 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	ft_check_pid(pid_t pid, t_struct *stct)
{
	t_phil	*tmp;
	int		i;

	i = 0;
	tmp = stct->first;
	while (i < stct->phils)
	{
		if (pid == tmp->pid)
		{
			tmp->terminated = 1;
			break ;
		}
		i++;
		tmp = tmp->next;
	}
}

static void	ft_kill(t_struct *stct)
{
	int		n;
	t_phil	*tmp;

	n = 0;
	tmp = stct->first;
	while (n < stct->phils)
	{
		if (tmp->pid != 0 && tmp->terminated != 1)
			kill(tmp->pid, SIGTERM);
		n++;
		tmp = tmp->next;
	}
}

static void	ft_wrap_up(t_struct *stct)
{
	pid_t	hang;
	t_phil	*tmp;
	int		i;
	int		status;

	i = 1;
	tmp = stct->first;
	hang = waitpid(-1, &status, 0);
	ft_check_pid(hang, stct);
	if (status == 1)
		ft_kill(stct);
	else if (status == 0)
	{
		while (i < stct->phils)
		{
			hang = waitpid(-1, &status, 0);
			ft_check_pid(hang, stct);
			if (status == 1)
			{
				ft_kill(stct);
				return ;
			}
			i++;
		}
	}
}

void	ft_processes(t_struct *stct)
{
	t_phil	*tmp;
	int		i;

	i = -1;
	tmp = stct->first;
	ft_semaphore_init(stct);
	while (++i < stct->phils)
	{
		tmp->pid = fork();
		if (tmp->pid < 0)
		{
			tmp->terminated = 1;
			ft_kill(stct);
			exit(EXIT_FAILURE);
		}
		else if (tmp->pid == 0)
			ft_routine(tmp);
		tmp = tmp->next;
	}
	ft_wrap_up(stct);
	sem_close(stct->forks);
	sem_close(stct->lock);
	sem_unlink("forks");
	sem_unlink("lock");
}
