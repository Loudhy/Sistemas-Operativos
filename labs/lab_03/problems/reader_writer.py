"""
Readers-Writers problem

1.- Any number of readers can be in the critical section simultaneously
2.- Writers must have exclusive to the critical section

In other words, a writer cannot enter the critical section while any
other thread(reader or writer) is there, and while the writer is there,
no other thread may enter.

Exclusion pattern: Categorical Mutual Exclusion
(A thread in the critical section does not necessarily excluse other
threads, but the presence of one category in the critical section excludes
other categories)
"""

import threading as th
import time



def waste_time(cycles=1_000_000):
    for _ in range(cycles):
        pass

def reading(id):
    print(f"[READER {id}]: {dashboard}", flush=True)
    time.sleep(0.01)


def writing(count):
    dashboard.append(count)
    print(f"[WRITER  ]: {dashboard}", flush=True)
    time.sleep(0.5)


def writer():
    for i in range(20):
        waste_time()
        room_empty.acquire()
        writing(i)
        room_empty.release()


def reader(id):
    global n_readers
    mutex.acquire()
    n_readers += 1
    if n_readers == 1:
        room_empty.acquire()
    mutex.release()
    
    reading(id)
    
    mutex.acquire()
    n_readers -= 1
    if n_readers == 0:
        room_empty.release()
    mutex.release()

# useful variables
dashboard = []
n_readers = 0
mutex = th.Semaphore(1)
room_empty = th.Semaphore(1)

# creating threads
writer_thread  = th.Thread(target=writer)
readers_thread = []
for i in range(10):
    readers_thread.append(th.Thread(target=reader, args=(i,)))


# start
writer_thread.start()
for i in range(10):
    readers_thread[i].start()

# join
writer_thread.join()
for i in range(10):
    readers_thread[i].join()
