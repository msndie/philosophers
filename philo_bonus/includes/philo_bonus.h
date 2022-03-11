/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:28:24 by sclam             #+#    #+#             */
/*   Updated: 2021/12/13 15:14:20 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

# define ERROR 1
# define END 0

typedef struct s_phil
{
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	int				numb;
	int				is_eating;
	long			last_meal;
	long			start;
	int				terminated;
	struct timeval	current;
	struct s_phil	*next;
	struct s_phil	*prev;
	sem_t			*forks;
	sem_t			*lock;
	pthread_t		watcher;
	pid_t			pid;
}	t_phil;

typedef struct s_struct
{
	int				ttd;
	int				tte;
	int				tts;
	int				phils;
	int				notepme;
	sem_t			*forks;
	sem_t			*lock;
	t_phil			*first;
}			t_struct;

void	ft_lst_clear(t_phil *lst, int n, int status);
t_phil	*ft_lst_new(int i, t_struct *stct);
int		ft_lst_add_back(t_phil *lst, t_phil *new);
void	ft_lst_loop(t_struct *stct);
void	ft_init_struct(t_struct *stct, int argc, char **argv);
void	ft_semaphore_init(t_struct *stct);
void	ft_processes(t_struct *stct);
void	*ft_watcher_thread(void *ptr);
void	ft_routine(t_phil *philo);
int		ft_atoi_w_err(const char *str);
void	ft_correct_usleep(unsigned int n, t_phil *lst);

#endif /*PHILO_BONUS_H*/