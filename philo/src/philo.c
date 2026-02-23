/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:18:21 by tshimizu          #+#    #+#             */
/*   Updated: 2026/02/23 22:32:13 by tshimizu         ###   ########.fr       */
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
	rules->ready_count = 0;
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
	if (!init_mutex_forks(rules))
		return (ft_putstr_fd("Error: fork mutex initialization failed\n", 2),
			cleanup_init_game_error(rules, 0), FALSE);
	if (pthread_mutex_init(&(rules->print_mutex), NULL) != 0)
		return (ft_putstr_fd("Error: print_mutex initialization failed\n", 2),
			cleanup_init_game_error(rules, 1), FALSE);
	if (pthread_mutex_init(&(rules->death_mutex), NULL) != 0)
	{
		ft_putstr_fd("Error: death_mutex initialization failed\n", 2);
		cleanup_init_game_error(rules, 2);
		return (FALSE);
	}
	if (pthread_mutex_init(&(rules->ready_mutex), NULL) != 0)
	{
		ft_putstr_fd("Error: ready_mutex initialization failed\n", 2);
		cleanup_init_game_error(rules, 3);
		return (FALSE);
	}
	if (!init_thread(rules))
		return (FALSE);
	if (!cleanup_all(rules))
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_rules	*rules;

	if (!validate_args(argc, argv))
		return (1);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (1);
	if (!init_main(argc, argv, rules))
	{
		ft_putstr_fd("Error: invalid argument(s)\n", 2);
		free(rules);
		return (1);
	}
	if (!init_game(rules))
	{
		ft_putstr_fd("Error: not created thread\n", 2);
		free(rules);
		return (1);
	}
	free(rules);
	return (0);
}
