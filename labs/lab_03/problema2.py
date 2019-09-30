import threading as th


def line1():
    print("Operativos")


def line2():
    print("INF", end=' ')


def line3():
    print("Sistemas", end=' ')


thread = th.Thread(target=line1)
thread.start()

thread = th.Thread(target=line2)
thread.start()

thread = th.Thread(target=line3)
thread.start()
