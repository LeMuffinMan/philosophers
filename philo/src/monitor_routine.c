
#include <pthread.h>
#include "philo.h"
#include <unistd.h> //usleep

bool are_philo_fed(t_data **data)
{
  int i;

  i = 0;
  while (i < (*data)->nb_philo)
  {
    pthread_mutex_lock(&(*data)->philosophers[i].fed_mutex);
    if ((*data)->philosophers[i].fed == false)
    {
      pthread_mutex_unlock(&(*data)->philosophers[i].fed_mutex);
      return (false);
    }
    pthread_mutex_unlock(&(*data)->philosophers[i].fed_mutex);
    i++;
  }
  return (true);
}

int main_thread_monitoring(t_data **data) // a bouger !
{
  while (1)
  {
    if (are_philo_fed(data))
    {
      pthread_mutex_lock(&(*data)->end_mutex);
      (*data)->end = true;
      pthread_mutex_unlock(&(*data)->end_mutex);
      return (1);
    }
    accurate_sleep (1000);
  /* pthread_mutex_lock(&(*data)->write_mutex); */
  /* printf("monitor started at %ld\n", get_time() - (*data)->start_time); */
  /* pthread_mutex_unlock(&(*data)->write_mutex); */
    usleep(100);
  }
  return (0);
}
