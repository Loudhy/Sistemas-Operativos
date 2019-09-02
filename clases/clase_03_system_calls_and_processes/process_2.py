# Multiprocessing - Python v3.3.0 documentation
# http://docs.python.org/2/library/multiprocessing.html
# 16.6.1.1. The Process class

from multiprocessing import Process
import os


def info(title):
    print("\n", title, sep="")
    print("module name: ", __name__)

    if hasattr(os, "getppid"):
        print("parent process: ", os.getppid())
    
    print("process id: ", os.getpid())


def hello(name):
    info("function hello")
    print("hello,", name)


if __name__ == "__main__":
    info("main line")
    process = Process(target=hello, args=("bob",))
    process.start()
    process.join()
