#include "philo.h"


int	main(int argc, char *argv[])
{
    (void)argv;

    if (argc < 5 || argc > 6)
    {
        ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 2);
        return 1;
    }

	return (0);
}
