/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:01:10 by sclam             #+#    #+#             */
/*   Updated: 2021/12/12 21:18:13 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_struct	stct;

	if (argc > 6 || argc < 5)
	{
		printf("Wrong number of arguments\n");
		return (-1);
	}
	ft_init_struct(&stct, argc, argv);
	ft_processes(&stct);
	ft_lst_clear(stct.first, stct.phils, END);
	return (0);
}
