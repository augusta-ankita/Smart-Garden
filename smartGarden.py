import serial
import time

# Change COM port below as per your Arduino (check in Arduino IDE > Tools > Port)
PORT = 'COM3'  # e.g., 'COM4' on some systems

try:
    arduino = serial.Serial(PORT, 9600, timeout=1)
    time.sleep(2)
    print("Connected to Arduino on", PORT)
except Exception as e:
    print("Failed to connect:", e)
    exit()

def send_command(command):
    arduino.write((command + '\n').encode())
    time.sleep(0.5)
    while arduino.in_waiting:
        response = arduino.readline().decode().strip()
        if response:
            print("Arduino:", response)

def menu():
    print("\n=== Smart Garden Irrigation ===")
    print("1. Turn ON Pump")
    print("2. Turn OFF Pump")
    print("3. Simulate Soil DRY")
    print("4. Simulate Soil WET")
    print("5. AUTO Mode")
    print("6. STATUS")
    print("7. EXIT")

while True:
    menu()
    choice = input("Enter your choice: ").strip()

    if choice == '1':
        send_command("TURN_ON_PUMP")
    elif choice == '2':
        send_command("TURN_OFF_PUMP")
    elif choice == '3':
        send_command("SIMULATE_DRY")
    elif choice == '4':
        send_command("SIMULATE_WET")
    elif choice == '5':
        send_command("AUTO")
    elif choice == '6':
        send_command("STATUS")
    elif choice == '7':
        print("Exiting...")
        arduino.close()
        break
    else:
        print("Invalid choice.")
