import threading as th


indice = -1
buffer = [None] * 5


def productor():
    for n in range(20):
        global indice
        global buffer
        item = n*n
        if indice < 5:
            indice += 1
            buffer[indice] = item
            print(f"[PRODUCTOR ]: {indice} {item} {buffer}", flush=True)


def consumidor():
    item = None
    for _ in range(20):
        global indice
        global buffer
        if indice > -1:
            item = buffer[indice]
            buffer[indice] = None
            print(f"[CONSUMIDOR]: {indice} {item} {buffer}", flush=True)
            indice -= 1


thread = th.Thread(target=productor)
thread.start()

thread = th.Thread(target=consumidor)
thread.start()
