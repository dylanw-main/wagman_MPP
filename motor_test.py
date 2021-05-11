from time import sleep
from rp2 import PIO, StateMachine, asm_pio
from machine import Pin, PWM
import math

motor1a = Pin(14, Pin.OUT)
motor1b = Pin(15, Pin.OUT)
stdby = Pin(12, Pin.OUT)


stdby.high()


def forward():
   motor1a.high()
   motor1b.low()

def stop():
   motor1a.low()
   motor1b.low()
   
def run():
    forward()
    pwm.duty_u16(65535)

@asm_pio(sideset_init=PIO.OUT_LOW)
def pwm_prog():
    pull(noblock) .side(0)
    mov(x, osr) # Keep most recent pull data stashed in X, for recycling by noblock
    mov(y, isr) # ISR must be preloaded with PWM count max
    label("pwmloop")
    jmp(x_not_y, "skip")
    nop()         .side(1)
    label("skip")
    jmp(y_dec, "pwmloop")


class PIOPWM:
    def __init__(self, sm_id, pin, max_count, count_freq):
        self._sm = StateMachine(sm_id, pwm_prog, freq=2 * count_freq, sideset_base=Pin(pin))
        # Use exec() to load max count into ISR
        self._sm.put(max_count)
        self._sm.exec("pull()")
        self._sm.exec("mov(isr, osr)")
        self._sm.active(1)
        self._max_count = max_count

    def set(self, value):
        # Minimum value is -1 (completely turn off), 0 actually still produces narrow pulse
        value = max(value, -1)
        value = min(value, self._max_count)
        self._sm.put(value)


# Pin 13 is hooked up to PWMA
#pwm = PWM(Pin(13))
#pwm.freq(1000)
#pwm = PIOPWM(0, 13, max_count=(1 << 16) - 1, count_freq=10_000_000)
pwm = PIOPWM(0, 13, max_count=65535, count_freq=10_000_000)
def full_pwr():
    # jerky acceleration
    forward()
    pwm.set(65535)
    sleep(5)
    stop()
    
def smooth():
    forward()
    for x in range(100, 65535, 100):
        speed = int(0.0001*(x**2))
        pwm.set(speed)
        sleep(0.001)
    