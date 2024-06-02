import bluetooth
import threading
import time
import random
import math

DEBUG = False

BLUETOOTH_ADDR = "00:22:05:00:31:4D"
BLUETOOTH_PORT = 1

current_pitch = 2000
current_bpm = 100

bpm_range = [ 85, 120 ]
pitch_range = [ 1500, 2500 ]

gg = False

def int_to_16bit_bytes(value):
  """
  Convert a given integer to a 2-byte representation if it fits in a 16-bit signed integer range.

  Args:
      value (int): The integer value to convert.

  Returns:
      bytes: A 2-byte representation of the integer.

  Raises:
      ValueError: If the integer is out of the 16-bit signed integer range.
  """
  # 16-bit signed integer range: -32768 to 32767
  if value < -32768 or value > 32767:
      raise ValueError("Integer out of range for 16-bit signed integer.")

  # Convert to 2-byte representation using little-endian byte order
  return value.to_bytes(2, byteorder='big', signed=True)

def random_normal_around(value, std_dev=0.2):
    """
    Generate a random number around 'value' using a normal distribution.
    
    :param value: float, the center value around which to generate the random number, must be between 0.0 and 1.0
    :param std_dev: float, the standard deviation of the normal distribution, default is 0.1
    :return: float, a random number within the vicinity of 'value'
    """
    # Ensure the value is within the valid range
    if not 0.0 <= value <= 1.0:
        raise ValueError("Value must be between 0.0 and 1.0")
    
    # Generate the random number
    random_value = random.gauss(value, std_dev)
    
    # Clamp the value to ensure it stays within the range [0.0, 1.0]
    random_value = max(0.0, min(random_value, 1.0))
    
    return random_value

def light_delta_conversion(x):
  if 0 <= x <= 0.3:
    # Constant value 1
    return 1
  elif 0.3 < x <= 0.5:
    # Linear interpolation between 1 and 2
    return 1 + ((x - 0.3) / (0.5 - 0.3)) * (2 - 1)
  elif 0.5 < x <= 0.7:
    # Linear interpolation between 2 and 10
    return 2 + ((x - 0.5) / (0.7 - 0.5)) * (10 - 2)
  elif x > 0.7:
    # Linear interpolation between 10 and 180
    return 10 + ((x - 0.7) / (1 - 0.7)) * (180 - 10)
  else:
    raise ValueError("Input x should be in the range [0, 1]")

def wtraff_updater():
  if not DEBUG:
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((BLUETOOTH_ADDR, BLUETOOTH_PORT))

    data = bytes(list(int_to_16bit_bytes(80)))
    sock.send(data)

  global gg
  while not gg:
    bpm_intensity = (current_bpm - bpm_range[0]) / (bpm_range[1] - bpm_range[0])
    print(f"{bpm_intensity=}")

    light_delta1 = round(light_delta_conversion(bpm_intensity))
    if (light_delta1 == 0): light_delta1 = 1

    light_delta2 = -round(2.5 * light_delta1)

    assert light_delta1 > 0
    assert light_delta2 < 0

    sleep_duration = (math.pow(1.05 - bpm_intensity, 2.0)) * 2.0

    pitch_intesity = (current_pitch - pitch_range[0]) / (pitch_range[1] - pitch_range[0])

    pitch_vicinity = random_normal_around(pitch_intesity, 0.4)

    if pitch_vicinity < 0.33333:
      led = 0
    elif pitch_vicinity > 0.66667:
      led = 1
    else:
      led = 2

    assert 0 <= led <= 2

    print(f"{led=}, {sleep_duration=}, {light_delta1}")

    data = [led, 200] + list(int_to_16bit_bytes(light_delta1))
    if not DEBUG:
      sock.send(bytes(data))
    time.sleep(sleep_duration)
    #data = [led, 0] + list(int_to_16bit_bytes(light_delta2))
    #if not DEBUG:
    #  sock.send(bytes(data))
    #time.sleep(sleep_duration / 2.0)
  
  if not DEBUG:
    sock.close()

def init():
  wtraff_thread = threading.Thread(target=wtraff_updater)
  wtraff_thread.start()

def update(bpm, pitch):
  global bpm_range
  global pitch_range
  global current_bpm
  global current_pitch

  if bpm < bpm_range[0]:
    bpm_range[0] = bpm
  elif bpm > bpm_range[1]:
    bpm_range[1] = bpm

  if pitch < pitch_range[0]:
    pitch_range[0] = pitch
  elif pitch > pitch_range[1]:
    pitch_range[1] = pitch

  current_bpm = bpm
  current_pitch = pitch

def end():
  global gg
  gg = True
