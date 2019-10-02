import threading as th
import time


def an_order_for_me_available(name):
    print(f"[WAITER]: {name} checking", flush=True)
    return name in orders and orders[name] is not None


def make_order(waiter, dish):
    orders[waiter] = dish


def attend_order(name):
    print(f"[WAITER] I'm {name} attending the order '{orders[name]}'", flush=True)
    orders[name] = None


def waiter(name):
    with cond:
        cond.wait_for(lambda: an_order_for_me_available(name))
        attend_order(name)


def customer():
    for waiter,dish in zip(waiters, dishes):
        time.sleep(0.1)
        with cond:
            make_order(waiter, dish)
            print(f"[CUSTOM]: Order to {waiter} the dish '{dish}'", flush=True)
            cond.notify()


cond    = th.Condition()
orders  = {}
waiters = ["Walter", "Wendy", "Will", "Wong"]
dishes  = ["rice", "chicken", "salad", "dessert"]


waiter_thread   = th.Thread(target=waiter, args=("Will",))
customer_thread = th.Thread(target=customer)

waiter_thread.start()
customer_thread.start()

waiter_thread.join()
customer_thread.join()

print(f"[RESULT]: {orders}")