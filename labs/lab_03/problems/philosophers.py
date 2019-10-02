
def get_forks(i):
    global n_philo
    


def eat():
    pass


def put_forks():
    pass


def left(i):
    return 1


def right(i):
    return (i+1) % 5


def philosopher():
    while True:
        get_forks()
        eat()
        put_forks()


n_philo = 5
forks   = [Semaphore(1) for i in range(5)]
