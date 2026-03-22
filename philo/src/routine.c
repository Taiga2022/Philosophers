/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:24:15 by tshimizu          #+#    #+#             */
/*   Updated: 2026/03/22 16:28:13 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_for_start(t_rules *rules)
{
	while (TRUE)
	{
		pthread_mutex_lock(&(rules->ready_mutex));
		if (rules->start_flag)
		{
			pthread_mutex_unlock(&(rules->ready_mutex));
			break ;
		}
		pthread_mutex_unlock(&(rules->ready_mutex));
		usleep(100);
	}
}

static int	calc_delay(t_philo *philo)
{
	t_rules	*rules;
	int		position;

	rules = philo->rules;
	if (rules->n_philo <= 1)
		return (0);
	if (rules->n_philo % 2 == 0)
	{
		if (philo->id % 2 == 1)
			return (rules->time_to_eat);
		return (0);
	}
	if (philo->id % 2 == 0)
		position = philo->id / 2;
	else
		position = (rules->n_philo + 1) / 2 + philo->id / 2;
	return (position * rules->time_to_eat / (rules->n_philo / 2));
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
	int		think_time;

	rules = philo->rules;
	eat(philo);
	print_action(philo, "is sleeping");
	ft_precise_sleep(rules->time_to_sleep);
	print_action(philo, "is thinking");
	think_time = rules->n_philo * (rules->time_to_eat / (rules->n_philo / 2))
		- rules->time_to_eat - rules->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 0)
		ft_precise_sleep(think_time);
	else
		usleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		delay;

	philo = (t_philo *)arg;
	wait_for_start(philo->rules);
	delay = calc_delay(philo);
	if (delay > 0)
		ft_precise_sleep(delay);
	if (philo->rules->n_philo == 1)
		return (print_action(philo, "has taken a fork"), NULL);
	while (TRUE)
	{
		if (check_death(philo->rules))
			break ;
		if (has_eaten_enough(philo))
			break ;
		philo_cycle(philo);
	}
	return (NULL);
}
