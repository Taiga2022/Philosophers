/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:00:18 by tshimizu          #+#    #+#             */
/*   Updated: 2025/10/05 17:00:374y tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_rules		*rules;
	int			i;
	int			done_eating;
	long long	now;

	rules = (t_rules *)arg;

	while (TRUE)
	{
		pthread_mutex_lock(&(rules->ready_mutex));
		int ready = rules->ready_count;
		pthread_mutex_unlock(&(rules->ready_mutex));
		if (ready >= rules->n_philo)
			break;
		usleep(100);
	}

	while (TRUE)
	{
		i = 0;
		done_eating = 0;
		while (i < rules->n_philo)
		{
			now = ft_get_timestamp();

			pthread_mutex_lock(&(rules->death_mutex));
			int died = rules->someone_died;
			pthread_mutex_unlock(&(rules->death_mutex));

			pthread_mutex_lock(&(rules->philos[i].meal_mutex));
			if (!died && now - rules->philos[i].last_meal > rules->time_to_die)
			{
				pthread_mutex_lock(&(rules->print_mutex));
				printf("%lld %d died\n", now - rules->start_time,
					rules->philos[i].id + 1);
				pthread_mutex_unlock(&(rules->print_mutex));

				pthread_mutex_lock(&(rules->death_mutex));
				rules->someone_died = TRUE;
				pthread_mutex_unlock(&(rules->death_mutex));

				pthread_mutex_unlock(&(rules->philos[i].meal_mutex));
				return (NULL);
			}
			if (rules->eat_count != -1
				&& rules->philos[i].meals_eaten >= rules->eat_count)
				done_eating++;
			pthread_mutex_unlock(&(rules->philos[i].meal_mutex));
			i++;
		}

		if (rules->eat_count != -1 && done_eating == rules->n_philo)
		{
			pthread_mutex_lock(&(rules->death_mutex));
			rules->someone_died = TRUE;
			pthread_mutex_unlock(&(rules->death_mutex));
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
