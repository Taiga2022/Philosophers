/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:00:55 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/23 22:31:00 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	create_philo_threads(t_rules *rules)
{
	int	i;

	i = -1;
	rules->start_time = ft_get_timestamp();
	while (++i < rules->n_philo)
	{
		if (!init_philo(rules, i))
		{
			ft_putstr_fd("Error: meal_mutex initialization failed\n", 2);
			cleanup_partial_philos(rules, i);
			return (FALSE);
		}
		if (pthread_create(&(rules->philos[i].thread), NULL, routine,
				&(rules->philos[i])) != 0)
		{
			ft_putstr_fd("Error: pthread_create failed\n", 2);
			pthread_mutex_destroy(&(rules->philos[i].meal_mutex));
			cleanup_partial_philos(rules, i);
			cleanup_on_thread_error(rules, i);
			return (FALSE);
		}
	}
	return (TRUE);
}

static t_bool	create_monitor_thread(t_rules *rules)
{
	if (pthread_create(&(rules->monitor_thread), NULL, monitor, rules) != 0)
		return (ft_putstr_fd("monitor thread create failed", 2), FALSE);
	return (TRUE);
}

static t_bool	join_all_threads(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
		if (pthread_join(rules->philos[i].thread, NULL) != 0)
			return (ft_putstr_fd("pthread_join failed", 2),
				cleanup_on_thread_error(rules, i), FALSE);
	if (pthread_join(rules->monitor_thread, NULL) != 0)
		return (ft_putstr_fd("monitor thread join failed", 2),
			cleanup_on_thread_error(rules, i), FALSE);
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
	if (!join_all_threads(rules))
		return (FALSE);
	return (TRUE);
}
