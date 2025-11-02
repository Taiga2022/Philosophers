/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:23:59 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/02 18:24:02 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_ready(t_rules *rules)
{
	int	ready;

	while (TRUE)
	{
		pthread_mutex_lock(&(rules->ready_mutex));
		ready = rules->ready_count;
		pthread_mutex_unlock(&(rules->ready_mutex));
		if (ready >= rules->n_philo)
			break ;
		usleep(100);
	}
}

static int	check_death(t_rules *rules, int i)
{
	long long	now;

	now = ft_get_timestamp();
	pthread_mutex_lock(&(rules->philos[i].meal_mutex));
	if (now - rules->philos[i].last_meal > rules->time_to_die)
	{
		pthread_mutex_lock(&(rules->print_mutex));
		printf("%lld %d died\n", now - rules->start_time, rules->philos[i].id
			+ 1);
		pthread_mutex_unlock(&(rules->print_mutex));
		pthread_mutex_lock(&(rules->death_mutex));
		rules->someone_died = TRUE;
		pthread_mutex_unlock(&(rules->death_mutex));
		pthread_mutex_unlock(&(rules->philos[i].meal_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(rules->philos[i].meal_mutex));
	return (0);
}

static int	check_all_done(t_rules *rules)
{
	int	i;
	int	done;

	done = 0;
	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_mutex_lock(&(rules->philos[i].meal_mutex));
		if (rules->eat_count != -1
			&& rules->philos[i].meals_eaten >= rules->eat_count)
			done++;
		pthread_mutex_unlock(&(rules->philos[i].meal_mutex));
	}
	if (rules->eat_count != -1 && done == rules->n_philo)
	{
		pthread_mutex_lock(&(rules->death_mutex));
		rules->someone_died = TRUE;
		pthread_mutex_unlock(&(rules->death_mutex));
		return (1);
	}
	return (0);
}

static void	monitor_loop(t_rules *rules)
{
	int	i;

	while (TRUE)
	{
		i = -1;
		while (++i < rules->n_philo)
			if (check_death(rules, i))
				return ;
		if (check_all_done(rules))
			return ;
		usleep(1000);
	}
}

void	*monitor(void *arg)
{
	t_rules	*rules;

	rules = (t_rules *)arg;
	wait_for_ready(rules);
	monitor_loop(rules);
	return (NULL);
}
