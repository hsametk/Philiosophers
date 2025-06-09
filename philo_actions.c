/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:07:54 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/06 14:23:56 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->dead_flag)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	print_status(philo, "is thinking");
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, "has taken a fork");
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (!philo->program->dead_flag)
	{
		pthread_mutex_lock(&philo->program->write_lock);
		printf("%zu %d %s\n",
			get_time() - philo->program->start_time,
			philo->id,
			status);
		pthread_mutex_unlock(&philo->program->write_lock);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
}
