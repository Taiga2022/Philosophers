#include "philo.h"


t_bool init_main(int argc, char *argv[], t_rules *rules)
{
    rules->n_philo = ft_atoi(argv[1]);
    rules->time_to_die = ft_atoi(argv[2]);
    rules->time_to_eat = ft_atoi(argv[3]);
    rules->time_to_sleep = ft_atoi(argv[4]);

    if (argc == 6)
    {
        rules->eat_count = ft_atoi(argv[5]);
        if (rules->eat_count <= 0)
            return FALSE;
    }
    else
        rules->eat_count = -1;

    if (rules->n_philo <= 0 || rules->time_to_die <= 0 ||
        rules->time_to_eat <= 0 || rules->time_to_sleep <= 0)
        return FALSE;

    return TRUE;
}

t_bool init_thread(t_rules *rules)
{
    pthread_t t1, t2;
    int ret;

    ret = pthread_mutex_init(&(rules->mutex), NULL);
    if (ret != 0)
    {
        perror("pthread_mutex_init failed");
        return FALSE;
    }

    ret = pthread_create(&t1, NULL, routine, rules);
    if (ret != 0)
    {
        perror("pthread_create t1 failed");
        pthread_mutex_destroy(&rules->mutex);
        return FALSE;
    }

    ret = pthread_create(&t2, NULL, routine, rules);
    if (ret != 0)
    {
        perror("pthread_create t2 failed");
        pthread_join(t1, NULL);
        pthread_mutex_destroy(&rules->mutex);
        return FALSE;
    }

    ret = pthread_join(t1, NULL);
    if (ret != 0)
        perror("pthread_join t1 failed");

    ret = pthread_join(t2, NULL);
    if (ret != 0)
        perror("pthread_join t2 failed");

    ret = pthread_mutex_destroy(&(rules->mutex));
    if (ret != 0)
        perror("pthread_mutex_destroy failed");

    return TRUE;
}

int main(int argc, char *argv[])
{
    t_rules rules;

    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 2);
        return 1;
    }

    if (!init_main(argc, argv, &rules))
    {
        ft_putstr_fd("Error: invalid argument(s)\n", 2);
        return 1;
    }

    if (!init_thread(&rules))
    {
        ft_putstr_fd("Error: invalid argument(s)\n", 2);
        return 1;
    }


    return 0;
}
