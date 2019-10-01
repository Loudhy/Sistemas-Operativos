import threading as th

contador = [0, 0]


def hilo(num):
    for i in range(1, 11):
        t = num
        print(f"[Hilo {num}]: valor de {i}", flush=True)
        other = contador[1-t]
        contador[t] = other + 1


threads = []
for i in range(2):
    t = th.Thread(target=hilo, args=(i,))
    threads.append(t)

for i in range(2):
    threads[i].start()

for i in range(2):
    threads[i].join()

print(f"contador de hilo 0 {contador[0]}")
print(f"contador de hilo 1 {contador[1]}")
