/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:24:29 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/23 23:30:02 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
	}
	print_action(philo, "has taken a fork");
}

static void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal = ft_get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&(philo->meal_mutex));
}

void	eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	take_forks(philo);
	print_action(philo, "is eating");
	update_meal(philo);
	ft_precise_sleep(rules->time_to_eat);
	put_forks(philo);
}
