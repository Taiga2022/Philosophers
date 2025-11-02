/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:00:55 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/02 19:15:38 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	create_philo_threads(t_rules *rules)
{
	int	i;

	i = -1;
	rules ->start_time = ft_get_timestamp();
	while (++i < rules->n_philo)
	{
		init_philo(rules, i);
		if (pthread_create(&(rules->philos[i].thread), NULL, routine,
				&(rules->philos[i])) != 0)
			return (perror("pthread_create failed"),
				cleanup_on_thread_error(rules, i), FALSE);
	}
	return (TRUE);
}

static t_bool	create_monitor_thread(t_rules *rules)
{
	if (pthread_create(&(rules->monitor_thread), NULL, monitor, rules) != 0)
		return (perror("monitor thread create failed"), FALSE);
	return (TRUE);
}

static t_bool	join_all_threads(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
		if (pthread_join(rules->philos[i].thread, NULL) != 0)
			return (perror("pthread_join failed"),
				cleanup_on_thread_error(rules, i), FALSE);
	if (pthread_join(rules->monitor_thread, NULL) != 0)
		return (perror("monitor thread join failed"),
			cleanup_on_thread_error(rules, i), FALSE);
	return (TRUE);
}

t_bool	init_thread(t_rules *rules)
{
	if (!create_philo_threads(rules))
		return (FALSE);
	if (!create_monitor_thread(rules))
		return (FALSE);
	if (!join_all_threads(rules))
		return (FALSE);
	return (TRUE);
}
