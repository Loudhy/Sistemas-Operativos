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


def reading():
    pass


def writirg():
    pass


def writer():
    pass


def reader():
    pass


writer_thread  = th.Thread(target=writing)
readers_thread = []

for _ in range(10):
    readers_thread.append(th.Thread(target=reading))

