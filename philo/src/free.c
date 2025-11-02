/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:22:22 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/02 18:23:36 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	cleanup_all(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_mutex_destroy(&(rules->forks[i])) != 0
			|| pthread_mutex_destroy(&(rules->philos[i].meal_mutex)) != 0)
			return (perror("cleanup_all: fork mutex destroy failed"), FALSE);
		i++;
	}
	if (pthread_mutex_destroy(&(rules->print_mutex)) != 0
		|| pthread_mutex_destroy(&(rules->death_mutex)) != 0
		|| pthread_mutex_destroy(&(rules->ready_mutex)) != 0)
		return (perror("cleanup_all: global mutex destroy failed"), FALSE);
	free(rules->forks);
	free(rules->philos);
	return (TRUE);
}

t_bool	cleanup_on_thread_error(t_rules *rules, int created_count)
{
	int	i;

	i = 0;
	while (i < created_count)
	{
		if (pthread_join(rules->philos[i].thread, NULL) != 0)
			return (perror("pthread_join failed"), FALSE);
		i++;
	}
	while (i < rules->n_philo)
	{
		if (pthread_mutex_destroy(&(rules->forks[i])) != 0)
			return (perror("cleanup_on_thread_error: fork destroy failed"),
				FALSE);
		i++;
	}
	if (pthread_mutex_destroy(&(rules->print_mutex)) != 0
		|| pthread_mutex_destroy(&(rules->death_mutex)) != 0)
		return (perror("cleanup_one_thread_error: global mutex destroy failed"),
			FALSE);
	free(rules->forks);
	free(rules->philos);
	return (TRUE);
}
