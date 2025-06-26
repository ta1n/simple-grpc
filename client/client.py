import grpc
import rfcontrol_pb2
import rfcontrol_pb2_grpc


def display_menu():
    print("\nRF Controller Client")
    print("1. Configure Device")
    print("2. View Current Settings")
    print("3. Exit")
    return input("Select an option (1-3): ")


device_id = "dev1"


def configure_device(stub):
    print("\nConfigure Device")
    device_id = input("Enter Device ID: ")

    while True:
        try:
            frequency = float(input("Enter Frequency (Hz): "))
            break
        except ValueError:
            print("Please enter a valid number for frequency")

    while True:
        try:
            gain = float(input("Enter Gain (dB): "))
            break
        except ValueError:
            print("Please enter a valid number for gain")

    response = stub.SetRFSettings(
        rfcontrol_pb2.RFConfig(
            device_id=device_id,
            frequency=frequency,
            gain=gain
        )
    )

    print("\nConfiguration Result:")
    print(f"Success: {'Yes' if response.success else 'No'}")
    print(f"Message: {response.message}")
    print(f"Status: {response.device_status}")


def view_current_settings(stub):
    print("\nView Current Settings")
    # device_id = input("Enter Device ID to query: ")
    # device_id = "1"

    response = stub.GetCurrentSettings(
        rfcontrol_pb2.DeviceQuery(device_id=device_id)
    )

    print("\nCurrent Device Settings:")
    print(f"Device ID: {response.device_id}")
    print(f"Frequency: {response.current_frequency} Hz")
    print(f"Gain: {response.current_gain} dB")
    print(f"Status: {response.status_message}")


def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = rfcontrol_pb2_grpc.RFControllerStub(channel)

    while True:
        choice = display_menu()

        if choice == '1':
            configure_device(stub)
        elif choice == '2':
            view_current_settings(stub)
        elif choice == '3':
            print("Exiting...")
            break
        else:
            print("Invalid option. Please try again.")


if __name__ == '__main__':
    run()
