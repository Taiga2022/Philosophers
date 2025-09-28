/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:51:31 by tshimizu          #+#    #+#             */
/*   Updated: 2025/09/28 12:21:59by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_main(int argc, char *argv[], t_rules *rules)
{
	rules->n_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->start_time = 0;
	rules->someone_died = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return (FALSE);
	rules->philos = malloc(sizeof(t_philo) * rules->n_philo);
	if (!rules->philos)
		return (free(rules->forks), FALSE);
	if (argc == 6)
	{
		rules->eat_count = ft_atoi(argv[5]);
		if (rules->eat_count <= 0)
			return (FALSE);
	}
	else
		rules->eat_count = -1;
	if (rules->n_philo <= 0 || rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
		return (FALSE);
	return (TRUE);
}

t_bool	init_game(t_rules *rules)
{
	if (!init_mutex_forks(rules) || !pthread_mutex_init(&(rules->print_mutex),
			NULL) || !pthread_mutex_init(&(rules->death_mutex), NULL))
		return (perror("pthread_mutex_init failed"), FALSE);
	if (!init_thread(rules))
		return (FALSE);
	if (!cleanup_all(rules))
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			2);
		return (1);
	}
	if (!init_main(argc, argv, &rules))
	{
		ft_putstr_fd("Error: invalid argument(s)\n", 2);
		return (1);
	}
	if (!init_game(&rules))
	{
		ft_putstr_fd("Error: not created thread\n", 2);
		return (1);
	}
	return (0);
}
