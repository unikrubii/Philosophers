#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_info
{
	int		mails;
	pthread_mutex_t mutex;
	pthread_t	*th;
}	t_info;

void *greeting(void *info)
{
	int	i = 0;
	pthread_mutex_t mt = ((t_info *)info)->mutex;
	int	*mails = &((t_info *)info)->mails;

	while (i++ < 1000000)
	{
		pthread_mutex_lock(&mt);
		*mails += 1;
		pthread_mutex_unlock(&mt);
	}
	return (NULL);
}

int	main(void)
{
	t_info	info;

	info.mails = 0;
	info.th = malloc(sizeof(pthread_t) * 4);
	for (int i = 0; i < 4; i++)
	{
		pthread_mutex_init(&info.mutex, NULL);
		if (pthread_create(&info.th[i], NULL, greeting, &info))
			return 1;
		printf("Thread %d created\n", i);
		if (pthread_join(info.th[i], NULL))
			return 2;
	}
	pthread_mutex_destroy(&info.mutex);
	printf("%d\n", info.mails);
	return (0);
}