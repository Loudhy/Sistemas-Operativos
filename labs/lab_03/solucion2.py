import threading as th


def line1():
    event2.wait()
    print("Operativos")
    

def line2():
    print("INF", end=' ')
    event1.set()


def line3():
    event1.wait()
    print("Sistemas", end=' ')
    event2.set()


event1 = th.Event()
event1.clear()

event2 = th.Event()
event2.clear()

thread = th.Thread(target=line1)
thread.start()

thread = th.Thread(target=line2)
thread.start()

thread = th.Thread(target=line3)
thread.start()
