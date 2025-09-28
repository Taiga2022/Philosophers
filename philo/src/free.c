/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:00:18 by tshimizu          #+#    #+#             */
/*   Updated: 2025/09/28 19:36:23 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	cleanup_all(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_mutex_destroy(&(rules->forks[i])) != 0||pthread_mutex_destroy(&(rules->print_mutex))!=0||pthread_mutex_destroy(&(rules->death_mutex))!=0)
			return (perror("pthread_mutex_init failed"), FALSE);
		i++;
	}
	free(rules->forks);
	free(rules->philos);
	return (TRUE);
}

t_bool	cleanup_on_thread_error(t_rules *rules, int created_count)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < created_count)
	{
		if (pthread_join(rules->philos[j].thread, NULL) != 0)
			return (FALSE);
		j++;
	}
	while (i < rules->n_philo)
	{
		if (pthread_mutex_destroy(&(rules->forks[i])) != 0||pthread_mutex_destroy(&(rules->print_mutex))!=0||pthread_mutex_destroy(&(rules->death_mutex))!=0)
			return (perror("pthread_mutex_init failed"), FALSE);
		i++;
	}
	free(rules->forks);
	free(rules->philos);
	TRUE;
}
