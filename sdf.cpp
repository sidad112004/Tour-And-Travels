#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Passenger
{
private:
    string name;
    string email;
    string phone;

public:
    Passenger(const string &n, const string &e, const string &p)
        : name(n), email(e), phone(p) {}

    void display() const
    {
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
    }

    string getName() const { return name; }

    string getInfoString() const
    {
        return "Name: " + name + "\nEmail: " + email + "\nPhone: " + phone + "\n";
    }
};

class Tour
{
private:
    string name;
    string destination;
    string date;
    int duration;
    double amount;
    int availableSeats;
    vector<Passenger> passengers;

public:
    Tour(const string &n, const string &dest, const string &dt, int dur, double amt, int seats)
        : name(n), destination(dest), date(dt), duration(dur), amount(amt), availableSeats(seats) {}

    void bookSeat(const string &passengerName, const string &email, const string &phone)
    {
        if (availableSeats > 0)
        {
            passengers.push_back(Passenger(passengerName, email, phone));
            availableSeats--;

            ofstream outFile(name + "_passenger_info.txt", ios::app); 
            if (outFile.is_open())
            {
                outFile << "Tour: " << name << endl;
                outFile << "Passenger: " << passengerName << endl;
                outFile << "Email: " << email << endl;
                outFile << "Phone: " << phone << endl << endl;
                outFile.close();
                cout << "Seat booked successfully!\n";
            }
            else
            {
                cout << "Unable to open file for tour: " << name << endl;
            }
        }
        else
        {
            cout << "No seats available for tour: " << name << endl;
        }
    }

    void cancelBooking()
    {
        if (passengers.empty())
        {
            cout << "No bookings to cancel for tour: " << name << endl;
        }
        else
        {
            passengers.pop_back();
            availableSeats++;
            cout << "Booking cancelled for tour: " << name << endl;
        }
    }

    void display() const
    {
        cout << "Name: " << name << endl;
        cout << "Destination: " << destination << endl;
        cout << "Date: " << date << endl;
        cout << "Duration: " << duration << " days" << endl;
        cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "Available Seats: " << availableSeats << endl;
    }

    void displayPassengers() const
    {
        cout << "Passengers for tour " << name << ":" << endl;
        for (const auto &passenger : passengers)
        {
            passenger.display();
            cout << endl;
        }
    }   

    const string &getName() const { return name; }
};

class TourAgency
{
private:
    vector<Tour> tours;

public:
    size_t getTourCount() const { return tours.size(); }

    void addTour(const string &name, const string &dest, const string &date, int duration, double amount, int seats)
    {
        tours.push_back(Tour(name, dest, date, duration, amount, seats));
        ofstream outFile(name + "_tour_info.txt"); 
        if (outFile.is_open())
        {
            outFile << "Tour Name: " << name << endl;
            outFile << "Destination: " << dest << endl;
            outFile << "Date: " << date << endl;
            outFile << "Duration: " << duration << " days" << endl;
            outFile << "Amount: $" << fixed << setprecision(2) << amount << endl;
            outFile << "Available Seats: " << seats << endl;
            outFile.close();
            cout << "Tour added successfully!" << endl;
        }
        else
        {
            cout << "Unable to create file for tour: " << name << endl;
        }
    }

    void displayTours() const
    {
        if (tours.empty())
        {
            cout << "No tours available." << endl;
            return;
        }
        cout << "Available Tours:" << endl;
        for (size_t i = 0; i < tours.size(); ++i)
        {
            cout << i + 1 << ". ";
            tours[i].display();
            cout << endl;
        }
    }

    void bookSeat(int tourIndex, const string &passengerName, const string &email, const string &phone)
    {
        if (tourIndex >= 0 && static_cast<size_t>(tourIndex) < tours.size())
        {
            tours[tourIndex].bookSeat(passengerName, email, phone);
        }
        else
        {
            cout << "Invalid tour number!" << endl;
        }
    }

    void cancelBooking(int tourIndex)
    {
        if (tourIndex >= 0 && static_cast<size_t>(tourIndex) < tours.size())
        {
            tours[tourIndex].cancelBooking();
        }
        else
        {
            cout << "Invalid tour number!" << endl;
        }
    }

    void displayPassengers(int tourIndex) const
    {
        if (tourIndex >= 0 && static_cast<size_t>(tourIndex) < tours.size())
        {
            tours[tourIndex].displayPassengers();
        }
        else
        {
            cout << "Invalid tour number!" << endl;
        }
    }

    bool isAdmin(const string &username, const string &password) const
    {
        return username == "admin" && password == "pass";
    }
};

int main()
{
    TourAgency agency;

    while (true)
    {
        cout << "\nWelcome to the Tours and Travel Agency...." << endl;
        cout << "============================================" << endl;
        cout << "1. Display Available Tours" << endl;
        cout << "2. Book a Seat" << endl;
        cout << "3. Cancel Booking" << endl;
        cout << "4. Display Passengers" << endl;
        cout << "5. Add a New Tour (Admin)" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            agency.displayTours();
            break;
        case 2:
        {
            agency.displayTours();
            cout << "Enter the number of the tour to book a seat: ";
            int tourIndex;
            cin >> tourIndex;
            if (tourIndex >= 1 && tourIndex <= static_cast<int>(agency.getTourCount()))
            {
                string passengerName, email, phone;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, passengerName);
                cout <<"Enter your email: ";
                getline(cin, email);
                cout << "Enter your phone number: ";
                getline(cin, phone);
                agency.bookSeat(tourIndex - 1, passengerName, email, phone);
            }
            else
            {
                cout << "Invalid tour number!" << endl;
            }
            break;
        }
        case 3:
        {
            agency.displayTours();
            cout << "Enter the number of the tour to cancel the booking: ";
            int tourIndex;
            cin >> tourIndex;
            if (tourIndex >= 1 && tourIndex <= static_cast<int>(agency.getTourCount()))
            {
                agency.cancelBooking(tourIndex - 1);
            }
            else
            {
                cout << "Invalid tour number!" << endl;
            }
            break;
        }
        case 4:
        {
            agency.displayTours();
            cout << "Enter the number of the tour to display passengers: ";
            int tourIndex;
            cin >> tourIndex;
            if (tourIndex >= 1 && tourIndex <= static_cast<int>(agency.getTourCount()))
            {
                agency.displayPassengers(tourIndex - 1);
            }
            else
            {
                cout << "Invalid tour number!" << endl;
            }
            break;
        }
        case 5:
        {
            cout << "Admin Login" << endl;
            cout << "Username: ";
            string username;
            cin >> username;
            cout << "Password: ";
            string password;
            cin >> password;
            if (agency.isAdmin(username, password))
            {
                string name, destination, date;
                int duration, seats;
                double amount;

                cout << "Enter tour details:" << endl;

                cout << "Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Destination: ";
                getline(cin, destination);

                cout << "Date: ";
                getline(cin, date);

                cout << "Duration (days): ";
                cin >> duration;

                cout << "Amount: ";
                cin >> amount;

                cout << "Available Seats: ";
                cin >> seats;

                agency.addTour(name, destination, date, duration, amount, seats);
            }
            else
            {
                cout << "Invalid admin credentials!" << endl;
            }
            break;
        }
        case 6:
            cout << "Exiting the program..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
