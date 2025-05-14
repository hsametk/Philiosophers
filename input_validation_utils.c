/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42istanbul.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:07:25 by hakotu            #+#    #+#             */
/*   Updated: 2025/05/14 14:50:52 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int		result;
	int		sign;

	sign = 1;
	result = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		printf("Error: Argument is empty.\n");
		return (0);
	}
	// if (str[0] == '-' || str[0] == '+')
	// {
	// 	printf("Error: Negative or positive signs are not allowed.\n");
	// 	return (0);
	// }
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			//printf("Error: Argument contains non-digit characters.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_arg(int argc, char *argv[], t_philo *philo)
{
    int	num_philos;
    int	i;

    if (argc < 5 || argc > 6)
    {
        printf("Error: Invalid number of arguments.\n");
        return (1);
    }
    i = 1;
    while (i < argc)
    {
        if (!is_valid_number(argv[i]))
        {
            printf("Error: Argument %d is not a valid positive integer.\n", i);
            return (1);
        }
        i++;
    }
    num_philos = ft_atoi(argv[1]);
    if (num_philos < 1 || num_philos > 200)
    {
        printf("Error: Number of philosophers must be between 1 and 200.\n");
        return (1);
    }
    if (argc == 6 && ft_atoi(argv[5]) <= 0)
    {
        printf("Error: Number of times to eat must be a positive integer.\n");
        return (1);
    }
    philo->num_of_philos = num_philos;
    return (0);
}

// philoların bilgilerini doldur
