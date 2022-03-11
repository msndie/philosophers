/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:28:24 by sclam             #+#    #+#             */
/*   Updated: 2021/12/13 15:18:48 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define ERROR 1
# define END 0

typedef struct s_phil
{
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	tts;
	unsigned int	notepme;
	unsigned int	numb;
	int				is_eating;
	long			last_meal;
	long			*curr_time;
	long			*start;
	int				*end;
	struct s_phil	*next;
	struct s_phil	*prev;
	pthread_t		t;
	pthread_mutex_t	fork;
}	t_phil;

typedef struct s_struct
{
	int				ttd;
	int				tte;
	int				tts;
	int				phils;
	int				notepme;
	int				end;
	long			curr_time;
	long			start;
	pthread_t		wathcher;
	t_phil			*first;
}			t_struct;

void	ft_lst_clear(t_phil *lst, int n, int status);
t_phil	*ft_lst_new(int i, t_struct *stct);
int		ft_lst_add_back(t_phil *lst, t_phil *new);
void	ft_lst_loop(t_struct *stct);
void	ft_init_start_time(t_struct *stct);
int		ft_mutex_init(t_struct *stct);
int		ft_init_struct(t_struct *stct, int argc, char **argv);
void	ft_mutex_destroy(t_struct *stct);
void	*ft_watcher(void *ptr);
void	*ft_philo(void *ptr);
int		ft_atoi_w_err(const char *str);
void	ft_correct_usleep(unsigned int n, t_phil *lst);

#endif /*PHILO_H*/