/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:41:17 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/05 18:22:30 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    // Implement the philosopher's routine here
    // For example, eating, sleeping, thinking, etc.
    return (NULL);
}
void create_threads(t_philo *philo)
{
    pthread_t	*threads;
    
    int			i;
    
    threads = malloc(sizeof(pthread_t) * philo->num_of_philos);
    //thread_args args = {&mails, &mutex};
    if (threads == NULL)
    {
        printf("Error: Failed to allocate memory for threads.\n");
        return ;
    }
    i = 0;
    while (i < philo->num_of_philos)
    {
        if (pthread_create(threads[i], NULL, routine, &philo[i]) != 0) //
        {
            printf("Error: Failed to create thread for philosopher %d.\n", i);
            return ;
        }
        i++;
    }
    i = 0;
    while (i < philo->num_of_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}