/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:00:55 by tshimizu          #+#    #+#             */
/*   Updated: 2026/03/22 14:08:24 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	create_philo_threads(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
	{
		if (!init_philo(rules, i))
		{
			ft_putstr_fd("Error: meal_mutex initialization failed\n", 2);
			cleanup_on_thread_error(rules, i);
			return (FALSE);
		}
		if (pthread_create(&(rules->philos[i].thread), NULL, routine,
				&(rules->philos[i])) != 0)
		{
			ft_putstr_fd("Error: pthread_create failed\n", 2);
			pthread_mutex_destroy(&(rules->philos[i].meal_mutex));
			cleanup_on_thread_error(rules, i);
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	signal_start(t_rules *rules)
{
	int	i;

	rules->start_time = ft_get_timestamp();
	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_mutex_lock(&(rules->philos[i].meal_mutex));
		rules->philos[i].last_meal = rules->start_time;
		pthread_mutex_unlock(&(rules->philos[i].meal_mutex));
	}
	pthread_mutex_lock(&(rules->ready_mutex));
	rules->start_flag = TRUE;
	pthread_mutex_unlock(&(rules->ready_mutex));
}

static t_bool	create_monitor_thread(t_rules *rules)
{
	if (pthread_create(&(rules->monitor_thread), NULL, monitor, rules) != 0)
		return (FALSE);
	return (TRUE);
}

static t_bool	join_all_threads(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
		if (pthread_join(rules->philos[i].thread, NULL) != 0)
			return (ft_putstr_fd("pthread_join failed", 2),
				cleanup_on_join_error(rules, i), FALSE);
	if (pthread_join(rules->monitor_thread, NULL) != 0)
		return (ft_putstr_fd("monitor thread join failed", 2),
			cleanup_on_join_error(rules, i), FALSE);
	return (TRUE);
}

t_bool	init_thread(t_rules *rules)
{
	if (!create_philo_threads(rules))
		return (FALSE);
	if (!create_monitor_thread(rules))
	{
		ft_putstr_fd("Error: monitor thread create failed\n", 2);
		cleanup_on_thread_error(rules, rules->n_philo);
		return (FALSE);
	}
	signal_start(rules);
	if (!join_all_threads(rules))
		return (FALSE);
	return (TRUE);
}
