# Filename: process_1.py
# Multiprocessing - Python v3.3.0 documentation
# http://docs.python.org/2/library/multiprocessing.html
# 16.6.1.1. The Process class

from multiprocessing import Process

def hello(name):
    print("hello,", name)

if __name__ == "__main__":
    process = Process(target=hello, args=('bob',))
    process.start()
    process.join()
