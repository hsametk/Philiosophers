/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:51:35 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/09 18:43:31 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	size_t				last_meal;
	struct s_program	*program;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
}	t_philo;

typedef struct s_program
{
	int				num_of_philos;
	int				dead_flag;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_program;

int		ft_isdigit(int c);
long	ft_atol(const char *str);
int		check_input(int argc, char *argv[]);
int		check_arg(int argc, char *argv[]);
int		is_valid_number(const char *str);
void	handle_single_philo(t_philo *philo);
void	destroy_mutexes(t_program *program);
void	init_mutexes(t_program *program);
void	init_philos(t_program *program);
void	create_threads(t_program *program);
size_t	get_time(void);
void	*philo_routine(void *arg);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	take_forks(t_philo *philo);
void	print_status(t_philo *philo, char *status);
void	precise_sleep(size_t duration);
void	wait_until_death(t_philo *philo);
int		check_all_ate(t_program *program);
void	update_meal_time(t_philo *philo);
void	handle_death(t_program *program, int i);
int		check_philosopher_status(t_program *program, int i);
int		init_some_struct(int argc, char *argv[], t_program *program);

#endif