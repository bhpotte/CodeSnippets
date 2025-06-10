"""This is an autoclicker project done in Python. This is simple just coding practice
   and following this guide: (https://www.geeksforgeeks.org/how-to-make-a-python-auto-clicker/) 
   to help understand pip, multithreading and using automated keyboard controls.
"""

# step 1: necessary modules
import time
import threading

from pynput.mouse import Button, Controller
from pynput.keyboard import Listener, KeyCode


# step 2: set key variables
delay = 0.001
btn = Button.left

start_key = KeyCode(char='a')
exit_key = KeyCode(char='b')


# step 3: use the threading module to prevent the 
# autoclicker from interfering with keyboard controls

class AutoClicker(threading.Thread):
    def __init__(self, delay, btn):
        super().__init__()
        self.delay = delay
        self.btn = btn
        self.clicking = False
        self.active = True

    def start_click(self):
        self.clicking = True

    def stop_click(self):
        self.clicking = False

    def exit(self):
        self.stop_click()
        self.active = False

    def run(self):
        while self.active:
            while self.clicking:
                mouse.click(self.btn)
                time.sleep(self.delay)


# step 4: create controller instance to simulate the mouse
mouse = Controller()
clicker = AutoClicker(delay, btn)
clicker.start()


# step 5: function that listens to the key press to determine
# to continue or exit

def on_press(k):
    if k == start_key:
        if clicker.clicking:
            clicker.stop_click()
            print("[INFO] Clicker Stopped.")
        else:
            clicker.start_click()
            print("[INFO] Clicker started.")
    elif k == exit_key:
        clicker.exit()
        print("[INFO] Exiting.")
        return False # stops the listener
    
# step 6: start the listener
with Listener(on_press=on_press) as listener:
    listener.join()