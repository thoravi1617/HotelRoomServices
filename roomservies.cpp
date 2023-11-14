#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class RoomService {
public:
    string serviceName;
    double serviceCharge;

    RoomService(const string& name, double charge) : serviceName(name), serviceCharge(charge) {}
};

class Room {
public:
    int roomNumber;
    bool isBooked;
    vector<RoomService> roomServices;

    Room(int number) : roomNumber(number), isBooked(false) {}

    double getTotalServiceCharges() const {
        double totalCharges = 0.0;
        for (const auto& service : roomServices) {
            totalCharges += service.serviceCharge;
        }
        return totalCharges;
    }
};

class Hotel {
private:
    vector<Room> rooms;

public:
    Hotel(int numRooms) {
        rooms.reserve(numRooms);
        for (int i = 1; i <= numRooms; ++i) {
            rooms.emplace_back(i);
        }
    }

    void displayAvailableRooms() const {
        cout << "Available Rooms:" << endl;
        cout << setw(15) << "Room Number" << setw(15) << "Status" << endl;
        for (const Room& room : rooms) {
            cout << setw(15) << room.roomNumber << setw(15) << (room.isBooked ? "Booked" : "Available") << endl;
        }
        cout << endl;
    }

    void bookRoom(int roomNumber) {
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number. Please try again." << endl;
            return;
        }

        Room& room = rooms[roomNumber - 1];
        if (room.isBooked) {
            cout << "Room " << roomNumber << " is already booked." << endl;
        } else {
            room.isBooked = true;
            cout << "Room " << roomNumber << " booked successfully." << endl;
        }
    }

    void displayRoomServices(int roomNumber) const {
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number. Please try again." << endl;
            return;
        }

        const Room& room = rooms[roomNumber - 1];
        cout << "Room Service Details for Room " << roomNumber << ":" << endl;
        cout << setw(20) << "Service Name" << setw(20) << "Service Charge" << endl;
        for (const auto& service : room.roomServices) {
            cout << setw(20) << service.serviceName << setw(20) << service.serviceCharge << endl;
        }
        cout << "Total Room Service Charges: " << room.getTotalServiceCharges() << endl;
    }

    void addRoomService(int roomNumber, const string& serviceName, double serviceCharge) {
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number. Please try again." << endl;
            return;
        }

        Room& room = rooms[roomNumber - 1];
        if (!room.isBooked) {
            cout << "Room " << roomNumber << " is not booked. Cannot add room service." << endl;
        } else {
            room.roomServices.emplace_back(serviceName, serviceCharge);
            cout << "Room service added for Room " << roomNumber << "." << endl;
        }
    }
};

int main() {
    const int numRooms = 5;
    Hotel hotel(numRooms);

    int choice;
    do {
        cout << "Hotel Booking System Menu:" << endl;
        cout << "1. Display available rooms" << endl;
        cout << "2. Book a room" << endl;
        cout << "3. Display room services" << endl;
        cout << "4. Add room service" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.displayAvailableRooms();
                break;
            case 2: {
                int roomNumber;
                cout << "Enter the room number to book: ";
                cin >> roomNumber;
                hotel.bookRoom(roomNumber);
                break;
            }
            case 3: {
                int roomNumber;
                cout << "Enter the room number to display room services: ";
                cin >> roomNumber;
                hotel.displayRoomServices(roomNumber);
                break;
            }
            case 4: {
                int roomNumber;
                string serviceName;
                double serviceCharge;
                cout << "Enter the room number to add room service: ";
                cin >> roomNumber;
                cout << "Enter the service name: ";
                cin.ignore(); 
                getline(cin, serviceName);
                cout << "Enter the service charge: ";
                cin >> serviceCharge;
                hotel.addRoomService(roomNumber, serviceName, serviceCharge);
                break;
            }
            case 5:
                cout << "Exiting the program. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

