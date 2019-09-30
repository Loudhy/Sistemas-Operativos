import threading as th


def hilo(num):
    print(f"[THREAD {num}]: Hi, congratulations. You're running your first threading program, I'm thread {num}")
    print(f"[THREAD {num}]: Python threads are used in cases where the execution of a task involves some waiting, I'm thread {num}")
    print(f"[THREAD {num}]: Threading allows python to execute other code while waiting, I'm thread {num}")


hilos = []

for n in range(4):
    h = th.Thread(target=hilo, args=(n,))
    hilos.append(h)

for n in range(4):
    hilos[n].start()
