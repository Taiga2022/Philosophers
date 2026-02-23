/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:22:22 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/23 22:30:54 by tshimizu         ###   ########.fr       */
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
			return (ft_putstr_fd("cleanup_all: fork mutex destroy failed", 2),
				FALSE);
		i++;
	}
	if (pthread_mutex_destroy(&(rules->print_mutex)) != 0
		|| pthread_mutex_destroy(&(rules->death_mutex)) != 0
		|| pthread_mutex_destroy(&(rules->ready_mutex)) != 0)
		return (ft_putstr_fd("cleanup_all: global mutex destroy failed", 2),
			FALSE);
	free(rules->forks);
	free(rules->philos);
	return (TRUE);
}

void	cleanup_on_thread_error(t_rules *rules, int created_count)
{
	int	i;

	i = 0;
	while (i < created_count)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		if (i < created_count)
			pthread_mutex_destroy(&(rules->philos[i].meal_mutex));
		i++;
	}
	pthread_mutex_destroy(&(rules->print_mutex));
	pthread_mutex_destroy(&(rules->death_mutex));
	pthread_mutex_destroy(&(rules->ready_mutex));
	free(rules->forks);
	free(rules->philos);
}

void	cleanup_init_game_error(t_rules *rules, int stage)
{
	int	i;

	if (stage >= 4)
		pthread_mutex_destroy(&(rules->ready_mutex));
	if (stage >= 3)
		pthread_mutex_destroy(&(rules->death_mutex));
	if (stage >= 2)
		pthread_mutex_destroy(&(rules->print_mutex));
	if (stage >= 1)
	{
		i = 0;
		while (i < rules->n_philo)
		{
			pthread_mutex_destroy(&(rules->forks[i]));
			i++;
		}
	}
	free(rules->philos);
	free(rules->forks);
}

void	cleanup_partial_philos(t_rules *rules, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(rules->philos[i].meal_mutex));
		i++;
	}
}
