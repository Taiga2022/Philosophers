#ifndef PHILO_H
#define PHILO_H

#include <stddef.h>     /* size_t */
#include <stdint.h>     /* integer types if needed */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc, free, calloc, realloc, exit */
#include <string.h>     /* memset, memcpy, strcmp, strdup... */
#include <unistd.h>     /* write, usleep, close, read, STDOUT_FILENO */
#include <sys/types.h>  /* ssize_t, off_t (often included via unistd.h) */
#include <sys/time.h>   /* gettimeofday, struct timeval */
#include <errno.h>      /* errno */
#include <pthread.h>    /* pthread_create/join/detach and mutex APIs */

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}				t_bool;


typedef struct s_rules
{
    int n_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
	pthread_mutex_t	mutex;
} t_rules;

void	ft_putstr_fd(char *s, int fd);

int	ft_atoi(const char *nptr);


t_bool init_main(int argc, char *argv[], t_rules *rules);


void *routine(void *arg);

#endif //PHILO_H
