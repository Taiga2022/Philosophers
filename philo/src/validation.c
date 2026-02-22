/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:43:55 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/22 14:17:44 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_number(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (LONG_MAX);
		str++;
	}
	return (result);
}

static int	validate_positive_int(const char *str, const char *name)
{
	long	value;

	if (!ft_is_number(str))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd((char *)name, 2);
		ft_putstr_fd(" must be a positive number\n", 2);
		return (0);
	}
	value = ft_atol(str);
	if (value <= 0 || value > INT_MAX)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd((char *)name, 2);
		ft_putstr_fd(" is out of valid range\n", 2);
		return (0);
	}
	return (1);
}

t_bool	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Usage: ./philo number_of_philosophers ", 2);
		ft_putstr_fd("time_to_die time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
		return (FALSE);
	}
	if (!validate_positive_int(argv[1], "number_of_philosophers"))
		return (FALSE);
	if (!validate_positive_int(argv[2], "time_to_die"))
		return (FALSE);
	if (!validate_positive_int(argv[3], "time_to_eat"))
		return (FALSE);
	if (!validate_positive_int(argv[4], "time_to_sleep"))
		return (FALSE);
	if (argc == 6 && !validate_positive_int(argv[5],
			"number_of_times_each_philosopher_must_eat"))
		return (FALSE);
	return (TRUE);
}
