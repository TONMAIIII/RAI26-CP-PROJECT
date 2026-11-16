import cyberpi
import mbot2
import gamepad
import time

DEADZONE = 10      # Ignore small stick drift near center (-10 to 10)
MAX_RPM = 130      # Max encoder motor speed (up to 200 RPM)
SHAFT_POWER = 100   # M1 motor power for shaft up/down (0 to 100)

# Logical limits for S1 & S3 (S3 physical angle = 180 - s3_pos, so 58 to 150)
SERVO_MIN = 30
SERVO_MAX = 122

s4_angle = 20         # Starting angle for S4
mbot2.servo_set(s4_angle, "S4")
n2_prev = False
n3_prev = False

s1_pos = 90            # Middle starting angle for S1
s3_pos = 90            # Middle starting angle for S3 (180 - 90 = 90)
mbot2.servo_set(s1_pos, "S1")
mbot2.servo_set(180 - s3_pos, "S3")
n1_prev = False
n4_prev = False
l1_prev = False
l2_prev = False
r1_prev = False
r2_prev = False
left_prev = False

def apply_deadzone(value, deadzone=DEADZONE):
    if abs(value) < deadzone:
        return 0
    return value

while True:
    # --- 1. Tank Drive (Encoder Motors EM1 & EM2) ---
    ly = apply_deadzone(gamepad.get_joystick('Ly'))
    ry = apply_deadzone(gamepad.get_joystick('Ry'))

    left_speed = (ly / 100) * MAX_RPM
    right_speed = (ry / 100) * MAX_RPM

    # Negate right_speed if EM2 is mounted opposite to EM1
    mbot2.drive_speed(-right_speed, left_speed)

    # --- 2. Shaft Control (DC Motor M1) via D-pad (+ button) ---
    if gamepad.is_key_pressed("Up"):
        mbot2.motor_set(SHAFT_POWER, "M1")
    elif gamepad.is_key_pressed("Down"):
        mbot2.motor_set(-30, "M1")
    else:
        mbot2.motor_stop("M1")

    # --- 3. Servo on S4: +20 deg / -20 deg per click (Buttons 2 & 3) ---
    n2_now = gamepad.is_key_pressed("N2")
    n3_now = gamepad.is_key_pressed("N3")

    if n2_now and not n2_prev:             
        s4_angle = min(137, s4_angle + 20)
        mbot2.servo_set(s4_angle, "S4")

    if n3_now and not n3_prev:             
        s4_angle = max(0, s4_angle - 20)
        mbot2.servo_set(s4_angle, "S4")

    n2_prev = n2_now
    n3_prev = n3_now

    # --- 4. Servos on S1 & S3: +5 deg / -5 deg per click (Buttons 1 & 4) ---
    n1_now = gamepad.is_key_pressed("N1")
    n4_now = gamepad.is_key_pressed("N4")

    if (n1_now and not n1_prev) or (n4_now and not n4_prev):
        if s1_pos != s3_pos:                # If hands are uneven, reset both to equal (90)
            s1_pos = 90
            s3_pos = 90
        elif n1_now and not n1_prev:        # Button 1 clicked -> Open both +5 deg
            s1_pos = min(SERVO_MAX, s1_pos + 5)
            s3_pos = min(SERVO_MAX, s3_pos + 5)
        elif n4_now and not n4_prev:        # Button 4 clicked -> Close both -5 deg
            s1_pos = max(SERVO_MIN, s1_pos - 5)
            s3_pos = max(SERVO_MIN, s3_pos - 5)

        mbot2.servo_set(s1_pos, "S1")
        mbot2.servo_set(180 - s3_pos, "S3")

    n1_prev = n1_now
    n4_prev = n4_now

    # --- 5. Individual Open/Close: 10 deg per click (L1/L2 for S3, R1/R2 for S1) ---
    l1_now = gamepad.is_key_pressed("L2")
    l2_now = gamepad.is_key_pressed("L1")
    r1_now = gamepad.is_key_pressed("R2")
    r2_now = gamepad.is_key_pressed("R1")

    if l1_now and not l1_prev:             # L1 clicked -> Open S3 (+10 deg)
        s3_pos = min(SERVO_MAX, s3_pos + 10)
        mbot2.servo_set(180 - s3_pos, "S3")

    if l2_now and not l2_prev:             # L2 clicked -> Close S3 (-10 deg)
        s3_pos = max(SERVO_MIN, s3_pos - 10)
        mbot2.servo_set(180 - s3_pos, "S3")

    if r1_now and not r1_prev:             # R1 clicked -> Open S1 (+10 deg)
        s1_pos = min(SERVO_MAX, s1_pos + 10)
        mbot2.servo_set(s1_pos, "S1")

    if r2_now and not r2_prev:             # R2 clicked -> Close S1 (-10 deg)
        s1_pos = max(SERVO_MIN, s1_pos - 10)
        mbot2.servo_set(s1_pos, "S1")

    l1_prev = l1_now
    l2_prev = l2_now
    r1_prev = r1_now
    r2_prev = r2_now
    


    time.sleep(0.02)
