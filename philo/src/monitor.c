/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:00:18 by tshimizu          #+#    #+#             */
/*   Updated: 2025/10/05 17:00:37 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *arg)
{
	t_rules *rules = (t_rules *)arg;
	int i;

	while (TRUE)
	{
		i = 0;
		while (i < rules->n_philo)
		{
			pthread_mutex_lock(&(rules->death_mutex));
			long long now = ft_get_timestamp();
			if (!rules->someone_died
				&& now - rules->philos[i].last_meal > rules->time_to_die)
			{
				rules->someone_died = TRUE;
				pthread_mutex_unlock(&(rules->death_mutex));

				pthread_mutex_lock(&(rules->print_mutex));
				printf("%lld %d died\n",
					now - rules->start_time, rules->philos[i].id);
				pthread_mutex_unlock(&(rules->print_mutex));
				return NULL;
			}
			pthread_mutex_unlock(&(rules->death_mutex));
			i++;
		}
		usleep(1000);
	}
	return NULL;
}
