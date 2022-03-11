/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:30:23 by sclam             #+#    #+#             */
/*   Updated: 2021/12/11 15:53:58 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_phil	*ft_lst_last(t_phil *lst)
{
	t_phil	*tmp;

	tmp = lst;
	while (lst && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lst_clear(t_phil *lst, int n, int status)
{
	t_phil	*tmp;
	int		i;

	i = 0;
	if (lst)
	{
		while (i < n)
		{
			tmp = lst->next;
			free(lst);
			lst = tmp;
			i++;
		}
		lst = NULL;
	}
	if (status == ERROR)
		write(2, "Malloc error\n", 14);
}

t_phil	*ft_lst_new(int i, t_struct *stct)
{
	t_phil	*tmp;

	tmp = malloc(sizeof(t_phil));
	if (tmp == NULL)
		return (0);
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->numb = i;
	tmp->ttd = stct->ttd;
	tmp->tte = stct->tte;
	tmp->tts = stct->tts;
	tmp->notepme = stct->notepme;
	tmp->is_eating = 0;
	tmp->end = &stct->end;
	return (tmp);
}

int	ft_lst_add_back(t_phil *lst, t_phil *new)
{
	t_phil	*tmp;
	t_phil	*tmp1;

	if (!new)
		return (-1);
	else
	{
		tmp = ft_lst_last(lst);
		tmp1 = tmp;
		tmp->next = new;
		tmp1 = tmp1->next;
		tmp1->prev = tmp;
	}
	return (0);
}

void	ft_lst_loop(t_struct *stct)
{
	t_phil	*tmp;

	tmp = ft_lst_last(stct->first);
	tmp->next = stct->first;
	stct->first->prev = tmp;
}
