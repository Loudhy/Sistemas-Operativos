from threading import Semaphore

class Lightswitch:
    def __init__(self):
        self.counter = 0
        self.mutex   = Semaphore(1)
    
    def lock(self, semaphore, turnstile=None):
        if turnstile is not None: turnstile.acquire()
        if turnstile is not None: turnstile.release()
        with self.mutex:
            self.counter += 1
            if self.counter == 1:
                semaphore.acquire()
        
    def unlock(self, semaphore):
        with self.mutex:
            self.counter -= 1
            if self.counter == 0:
                semaphore.release()
