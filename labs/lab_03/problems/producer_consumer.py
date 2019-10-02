"""
THE PRODUCER - CONSUMER PROBLEM

- While an item is being added to or removed from the buffer,
the buffer is in an inconsistent state. Therefore, threads must
have exlusive access to the buffer.

- If a consumer thread arrives while the buffer is empty, it
blocks until a producer adds a new item.

"""

import time
import threading as th


class Item(object):
    
    def __init__(self, number, message="None"):
        self.number  = number
        self.message = message
    
    def process(self):
        print(f"[ITEM {self.number}]: {self.message}", flush=True)
    
    def __str__(self):
        return str(self.number)
    
    def __repr__(self):
        return str(self.number)
    

class Buffer(object):
    
    def __init__(self, size=5):
        self.size  = size
        self.count = 0
        self.container = []
    
    def add_item(self, item):
        assert self.count < self.size, "Cannot add more items, buffer overfilled"
        self.count += 1
        self.container.append(item)

    def get_item(self):
        assert self.count > 0, "Cannot get more items, buffer empty"
        self.count -= 1
        return self.container.pop()

    def __str__(self):
        return str(self.container)


def wait_for_item(limit):
    for i in range(limit):
        yield Item(i, "it's a message")


def producer(limit=5):
    itemrator = wait_for_item(limit)

    for _ in range(limit):
        item = next(itemrator)
        spaces.acquire()
        mutex.acquire()
        buffer.add_item(item)
        print(f"BUFFER PRODUCER: {buffer}", flush=True)
        mutex.release()
        items.release()
        

def consumer(limit=5):
    for _ in range(limit):
        items.acquire()
        mutex.acquire()
        item = buffer.get_item()
        print(f"BUFFER CONSUMER: {buffer}", flush=True)
        mutex.release()
        spaces.release()
        item.process()


buffer = Buffer(size=10)
mutex  = th.Semaphore(1)
items  = th.Semaphore(0)
spaces = th.Semaphore(buffer.size)

th_consumer = th.Thread(target=producer, args=(30,))
th_producer = th.Thread(target=consumer, args=(30,))

th_consumer.start()
th_producer.start()

th_consumer.join()
th_producer.join()