/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:51:35 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/23 16:17:09 by hakotu           ###   ########.fr       */
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
# include	<string.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;         // Filozofun thread'i
	int				id;             // Filozofun ID'si
	int				meals_eaten;    // Yediği yemek sayısı
	size_t			last_meal;      // Son yemek yediği zaman (ms)
	struct s_program	*program;    // Program yapısına erişim
	pthread_mutex_t	*r_fork;        // Sağ çatal
	pthread_mutex_t	*l_fork;        // Sol çatal
}					t_philo;
typedef struct s_program
{
    int				num_of_philos;  // Filozof sayısı
    int				dead_flag;      // Ölüm bayrağı (1: biri öldü, 0: herkes yaşıyor)
    size_t			start_time;     // Programın başlangıç zamanı (ms)
    size_t			time_to_die;    // Ölüm süresi (ms)
    size_t			time_to_eat;    // Yemek yeme süresi (ms)
    size_t			time_to_sleep;  // Uyuma süresi (ms)
    int				num_times_to_eat; // Yemesi gereken toplam yemek sayısı
    pthread_mutex_t	write_lock;     // Yazma işlemleri için mutex
    pthread_mutex_t	dead_lock;      // Ölüm bayrağı için mutex
    pthread_mutex_t	*forks;         // Çatalların mutex dizisi
    t_philo			*philos;        // Filozofların dizisi
}					t_program;


int		ft_isdigit(int c);
long	ft_atol(const char *str);
int		check_input(int argc, char *argv[]);
int		check_arg(int argc, char *argv[]);
int		is_valid_number(const char *str);
void    handle_single_philo(t_program *program);
void    destroy_mutexes(t_program *program);
void    init_mutexes(t_program *program);
void    init_philos(t_program *program);
void    create_threads(t_program *program);
size_t	get_time(void);
void	*philo_routine(void *arg);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
int     check_all_ate(t_program *program);

#endif // PHILOSOPHERS_H