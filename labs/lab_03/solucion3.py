import threading as th


indice = -1
buffer = [None] * 5


def productor():
    for n in range(20):
        global indice
        global buffer
        item = n*n

        libre.acquire()       
        mutex.acquire()

        indice += 1
        buffer[indice] = item
        print(f"[PRODUCTOR ]: {indice} {item} {buffer}", flush=True)

        mutex.release()
        ocupado.release()


def consumidor():
    item = None
    for _ in range(20):
        global indice
        global buffer

        ocupado.acquire()
        mutex.acquire()

        item = buffer[indice]
        buffer[indice] = None
        print(f"[CONSUMIDOR]: {indice} {item} {buffer}", flush=True)
        indice -= 1

        mutex.release()
        libre.release()


libre   = th.Semaphore(value=5)
ocupado = th.Semaphore(value=0)
mutex   = th.Semaphore(value=1)

thread = th.Thread(target=productor)
thread.start()

thread = th.Thread(target=consumidor)
thread.start()
