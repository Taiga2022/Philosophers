/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:51:19 by tshimizu          #+#    #+#             */
/*   Updated: 2025/10/05 17:10:23 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_philo *philo, char *action)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->print_mutex));
	printf("[%lld] Philosopher %d %s\n", ft_get_timestamp() - rules->start_time,
		philo->id + 1, action);
	pthread_mutex_unlock(&(rules->print_mutex));
}

static void	eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	philo->last_meal = ft_get_timestamp();
	ft_precise_sleep(rules->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (TRUE)
	{
		pthread_mutex_lock(&(rules->death_mutex));
		if (rules->someone_died)
		{
			pthread_mutex_unlock(&(rules->death_mutex));
			break ;
		}
		pthread_mutex_unlock(&(rules->death_mutex));
		eat(philo);
		print_action(philo, "is sleeping");
		ft_precise_sleep(rules->time_to_sleep);
		print_action(philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}
