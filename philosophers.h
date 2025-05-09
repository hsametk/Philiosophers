	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:51:35 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/06 19:04:37 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/time.h>
# include	<limits.h>
# include	<stdbool.h>
# include	<pthread.h>
# include	<stdio.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;
typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;


int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	check_input(int argc, char *argv[], t_philo *philosopher);
int		check_arg(int argc, char *argv[], t_philo *philo);
int		is_valid_number(const char *str);
void	create_threads(t_philo *philo);
void	*philosopher_routine(void *arg);
void	init_mutexes(t_program *program, t_philo *philos);
void    init_philos(t_program *program, t_philo *philos, pthread_mutex_t *forks);
size_t	get_time(void);
#endif // PHILOSOPHERS_H