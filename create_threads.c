/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:41:17 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/20 20:28:08 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void create_threads(t_philo *philo)
{
    pthread_t	*threads;
    int			i;
    
    threads = malloc(sizeof(pthread_t) * philo->num_of_philos);
    if (threads == NULL)
    {
        printf("Error: Failed to allocate memory for threads.\n");
        return;
    }
    i = 0;
    while (i < philo->num_of_philos)
    {
        if (pthread_create(&threads[i], NULL, philo_routine, &philo[i]) != 0)
        {
            printf("Error: Failed to create thread for philosopher %d.\n", i);
            return;
        }
        i++;
    }
    i = 0;
    while (i < philo->num_of_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    free(threads);
}
void	init_mutexes(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
//TODO: pthread_join in NULL u değişip dönecek olan değişken oraya atanacak
void    init_philos(t_program *program, t_philo *philos, pthread_mutex_t *forks)
{
    int	i;

    i = 0;
    while (i < philos->num_of_philos)
    {
        program->philos[i].id = i + 1;
        program->philos[i].eating = 0;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = 0;
        program->philos[i].time_to_die = philos->time_to_die;
        program->philos[i].time_to_eat = philos->time_to_eat;
        program->philos[i].time_to_sleep = philos->time_to_sleep;
        size_t start_time = get_time();
        program->philos[i].start_time = start_time;
        program->philos[i].num_of_philos = philos->num_of_philos;
        program->philos[i].num_times_to_eat = philos->num_times_to_eat;
        program->philos[i].dead = &program->dead_flag;
        program->philos[i].write_lock = &program->write_lock;
        program->philos[i].dead_lock = &program->dead_lock;
        program->philos[i].meal_lock = &program->meal_lock;

        // Çatalların atanması
        program->philos[i].l_fork = &forks[i];
        program->philos[i].r_fork = &forks[(i + 1) % philos->num_of_philos];
        i++;
    }
}
