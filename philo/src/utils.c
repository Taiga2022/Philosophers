/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:51:08 by tshimizu          #+#    #+#             */
/*   Updated: 2026/03/22 14:23:20 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

long long	ft_get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	ft_precise_sleep(int time_in_ms)
{
	long long	start;

	start = ft_get_timestamp();
	while ((ft_get_timestamp() - start) < time_in_ms)
		usleep(100);
}

void	print_action(t_philo *philo, char *action)
{
	t_rules	*rules;
	int		is_dead;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->print_mutex));
	pthread_mutex_lock(&(rules->death_mutex));
	is_dead = rules->someone_died;
	pthread_mutex_unlock(&(rules->death_mutex));
	if (!is_dead)
		printf("%lld %d %s\n", ft_get_timestamp() - rules->start_time, philo->id
			+ 1, action);
	pthread_mutex_unlock(&(rules->print_mutex));
}
