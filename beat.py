import time
import ctypes
import os
import threading
from cext import beat, get_elapsed

start = time.time_ns()
elapsed = 0

beat_thread = threading.Thread(target=beat, args=(True,))
beat_thread.start()

for i in range(5):
    time.sleep(1.5)
    print(f"TIME: {get_elapsed()}")

beat_thread.join()

beat_thread = threading.Thread(target=beat, args=(False,))
beat_thread.start()
beat_thread.join()
print(time.time_ns() - start)
