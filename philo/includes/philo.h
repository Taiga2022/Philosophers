/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:52:42 by tshimizu          #+#    #+#             */
/*   Updated: 2025/09/28 19:47:52 by tshimizu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>     /* errno */
# include <pthread.h>   /* pthread_create/join/detach and mutex APIs */
# include <stddef.h>    /* size_t */
# include <stdint.h>    /* integer types if needed */
# include <stdio.h>     /* printf */
# include <stdlib.h>    /* malloc, free, calloc, realloc, exit */
# include <string.h>    /* memset, memcpy, strcmp, strdup... */
# include <sys/time.h>  /* gettimeofday, struct timeval */
# include <sys/types.h> /* ssize_t, off_t (often included via unistd.h) */
# include <unistd.h>    /* write, usleep, close, read, STDOUT_FILENO */

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}					t_bool;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal;
	pthread_t		thread;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	t_rules			*rules;
}					t_philo;

typedef struct s_rules
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	long long		start_time;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_died;

	t_philo			*philos;
}					t_rules;


void				ft_putstr_fd(char *s, int fd);

int					ft_atoi(const char *nptr);

t_bool				init_main(int argc, char *argv[], t_rules *rules);

t_bool				init_thread(t_rules *rules);

t_bool				init_game(t_rules *rules);

t_bool init_mutex_forks(t_rules *rules);

t_bool				cleanup_all(t_rules *rules);

t_bool				cleanup_on_thread_error(t_rules *rules, int created_count);

void				*routine(void *arg);

#endif // PHILO_H
