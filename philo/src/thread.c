/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:49:47 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/23 22:31:14 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_philo(t_rules *rules, int i)
{
	rules->philos[i].id = i;
	rules->philos[i].meals_eaten = 0;
	rules->philos[i].last_meal = 0;
	rules->philos[i].left_fork = &(rules->forks[i]);
	rules->philos[i].right_fork = &(rules->forks[(i + 1) % rules->n_philo]);
	if (pthread_mutex_init(&(rules->philos[i].meal_mutex), NULL) != 0)
		return (FALSE);
	rules->philos[i].rules = rules;
	return (TRUE);
}

t_bool	init_mutex_forks(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(rules->forks[i]));
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
