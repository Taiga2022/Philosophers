/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:49:47 by tshimizu          #+#    #+#             */
/*   Updated: 2025/09/28 19:26:31 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool init_philo(t_rules *rules,int count,pthread_t *threads)
{
	rules->philos[count].id=count;
	rules->philos[count].meals_eaten = 0;
	rules->philos[count].last_meal = 0;
	rules->philos[count].thread = threads[count];
	rules->philos[count].left_fork = &(rules->forks[count]);
	rules->philos[count].right_fork = &(rules->forks[(count + 1) % rules->n_philo]);
	rules->philos[count].rules = rules;
	return TRUE;
}

t_bool	init_thread(t_rules *rules)
{
	pthread_t *threads;
	int i;

	i = 0;
	threads = malloc(sizeof(pthread_t)*rules->n_philo);

	while (i<rules->n_philo)
	{
		init_philo(rules,i,threads);
		if (pthread_create(&(rules->philos[i].thread), NULL, routine, rules) != 0)
			return (perror("pthread_create failed"),cleanup_on_thread_error(rules,i),free(threads),FALSE);

		if(pthread_join(rules->philos[i].thread,NULL)!=0)
			return (perror("pthread_join failed"),cleanup_on_thread_error(rules,i),free(threads),FALSE);
		i++;
	}
	free(threads);
	return TRUE;
}

t_bool init_mutex_forks(t_rules *rules)
{
	int i;
	i=0;

	while (i<rules->n_philo)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL)!=0)
			return FALSE;
		i++;
	}
	return TRUE;
}
