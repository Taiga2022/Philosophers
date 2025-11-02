/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:24:15 by tshimizu          #+#    #+#             */
/*   Updated: 2025/11/02 18:24:18 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	t_rules	*rules;
	int		is_dead;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->print_mutex));
	pthread_mutex_lock(&(rules->death_mutex));
	is_dead = rules->someone_died;
	pthread_mutex_unlock(&(rules->death_mutex));
	if (!is_dead)
		printf("%lld %d %s\n", ft_get_timestamp() - rules->start_time, philo->id
			+ 1, action);
	pthread_mutex_unlock(&(rules->print_mutex));
}

static void	init_philo_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->meal_mutex));
	philo->last_meal = ft_get_timestamp();
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_lock(&(philo->rules->ready_mutex));
	philo->rules->ready_count++;
	pthread_mutex_unlock(&(philo->rules->ready_mutex));
	if (philo->id % 2 == 1)
		usleep(1000);
}

static int	check_death(t_rules *rules)
{
	pthread_mutex_lock(&(rules->death_mutex));
	if (rules->someone_died)
		return (pthread_mutex_unlock(&(rules->death_mutex)), 1);
	pthread_mutex_unlock(&(rules->death_mutex));
	return (0);
}

static void	philo_cycle(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	eat(philo);
	print_action(philo, "is sleeping");
	ft_precise_sleep(rules->time_to_sleep);
	print_action(philo, "is thinking");
	usleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	init_philo_state(philo);
	while (TRUE)
	{
		if (check_death(philo->rules))
			break ;
		philo_cycle(philo);
	}
	return (NULL);
}
