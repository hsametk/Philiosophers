/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:21:17 by hakotu            #+#    #+#             */
/*   Updated: 2025/06/06 14:22:55 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_death(t_program *program, int i)
{
	pthread_mutex_lock(&program->write_lock);
	printf("%zu %d died\n", get_time() - program->start_time,
		program->philos[i].id);
	pthread_mutex_unlock(&program->write_lock);
	program->dead_flag = 1;
}

int	check_philosopher_status(t_program *program, int i)
{
	size_t current_time;

	current_time = get_time();
	if (current_time - program->philos[i].last_meal > program->time_to_die)
	{
		program->dead_flag = 1;
		printf("%zu %d died\n", current_time - program->start_time,
			program->philos[i].id);
		return (1);
	}
	if (program->num_times_to_eat != -1 && check_all_ate(program))
	{
		program->dead_flag = 1;
		return (1);
	}
	return (0);
}
