#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;

// Function to display a welcome screen
void welcomeScreen() {
    cout << "\n======================================================\n";
    cout << "\t   WELCOME TO ABC HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "======================================================\n";
    cout << "Loading";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
    }
    cout << "\n\n";
}

// Function to print section headers
void printHeader(const string& section) {
    cout << "\n================ " << section << " ================\n";
}

// Base class representing a person in the hospital
class Person {
protected:
    string name;
    int id;

public:
    Person(const string& name, int id) : name(name), id(id) {}

    virtual void displayInfo() const {
        cout << "\nName: " << name << "\nID: " << id << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }

    virtual ~Person() {}
};

// Patient class derived from Person
class Patient : public Person {
private:
    int age;
    string gender;

public:
    Patient(const string& name, int age, const string& gender, int id)
        : Person(name, id), age(age), gender(gender) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Age: " << age << "\nGender: " << gender << endl;
    }

    int getAge() const { return age; }
    string getGender() const { return gender; }
};

// Doctor class derived from Person
class Doctor : public Person {
public:
    Doctor(const string& name, int id) : Person(name, id) {}

    void displayInfo() const override {
        Person::displayInfo();
        cout << "Role: Doctor" << endl;
    }
};

// Appointment class
class Appointment {
private:
    int patientId;
    int doctorId;
    string date;
    string timeSlot;

public:
    Appointment(int patientId, int doctorId, const string& date, const string& timeSlot)
        : patientId(patientId), doctorId(doctorId), date(date), timeSlot(timeSlot) {}

    void displayAppointment(const Patient& patient, const Doctor& doctor) const {
        cout << "Patient ID: " << patient.getId()
             << " || Name: " << patient.getName()
             << " || Age: " << patient.getAge()
             << " || Gender: " << patient.getGender() << endl;

        cout << "Doctor ID: " << doctor.getId()
             << " || Name: " << doctor.getName() << endl;

        cout << "Date: " << date << " || Time Slot: " << timeSlot << "\n";
        cout << "---------------------------------------------------\n";
    }

    int getPatientId() const { 
        return patientId; 
    }
    int getDoctorId() const { 
        return doctorId; 
    }
};

// Billing class
class Billing {
public:
    void generateBill(int patientId, const vector<Appointment>& appointments) const {
        int total = 0;
        for (const auto& appointment : appointments) {
            if (appointment.getPatientId() == patientId) {
                total += 500;  // Fixed cost per appointment
            }
        }
        cout << "\nTotal Bill for Patient ID " << patientId << ": " << total << " units\n";
    }
};

// Ward class to manage beds
class Ward {
private:
    vector<int> beds;
    int totalBeds;

public:
    Ward(int totalBeds) : totalBeds(totalBeds) {
        beds.resize(totalBeds, 0);
    }

    void admitPatient(int bedNumber) {
        if (bedNumber >= 0 && bedNumber < totalBeds && beds[bedNumber] == 0) {
            beds[bedNumber] = 1;
            cout << "\nPatient admitted to bed " << bedNumber << endl;
        } else {
            cout << "\nInvalid or occupied bed!" << endl;
        }
    }

    void dischargePatient(int bedNumber) {
        if (bedNumber >= 0 && bedNumber < totalBeds && beds[bedNumber] == 1) {
            beds[bedNumber] = 0;
            cout << "\nPatient discharged from bed " << bedNumber << endl;
        } else {
            cout << "\nInvalid or already free bed!" << endl;
        }
    }

    void viewBedStatus() const {
        printHeader("Bed Status");
        for (int i = 0; i < totalBeds; ++i) {
            cout << "Bed " << i << ": " << (beds[i] == 0 ? "Free" : "Occupied") << endl;
        }
    }
};

// Admin class to manage patients and appointments
class Admin {
public:
    void managePatients(vector<Patient>& patients, vector<Appointment>& appointments, const vector<Doctor>& doctors) {
        int choice;
        do {
            printHeader("Manage Patients");
            cout << "1. Add Patient\n2. Delete Patient\n3. View Patients\n4. View Appointments\n5. Book Appointment\n6. View Billing\n7. Go Back\n\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                string name, gender;
                int age;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Gender: ";
                cin >> gender;
                int id = patients.size() + 1;
                patients.emplace_back(name, age, gender, id);
                cout << "\nPatient added successfully!\n";
                break;
            }
            case 2: {
                int id;
                cout << "Enter Patient ID to delete: ";
                cin >> id;
                auto it = remove_if(patients.begin(), patients.end(),
                                    [id](const Patient& p) { return p.getId() == id; });
                if (it != patients.end()) {
                    patients.erase(it, patients.end());
                    cout << "\nPatient deleted successfully!\n";
                } else {
                    cout << "\nPatient not found!\n";
                }
                break;
            }
            case 3:
                for (const auto& patient : patients) {
                    patient.displayInfo();
                }
                break;
            case 4:
                for (const auto& appointment : appointments) {
                    const Patient& patient = *find_if(patients.begin(), patients.end(),
                                                      [&](const Patient& p) { return p.getId() == appointment.getPatientId(); });
                    const Doctor& doctor = *find_if(doctors.begin(), doctors.end(),
                                                    [&](const Doctor& d) { return d.getId() == appointment.getDoctorId(); });

                    appointment.displayAppointment(patient, doctor);
                }
                break;
            case 5: {
                int patientId, doctorId;
                string date, timeSlot;

                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Doctor ID: ";
                cin >> doctorId;
                cin.ignore();
                cout << "Enter Appointment Date (DD-MM-YYYY): ";
                getline(cin, date);
                cout << "Enter Time Slot (e.g., 10:00-11:00): ";
                getline(cin, timeSlot);

                appointments.emplace_back(patientId, doctorId, date, timeSlot);
                cout << "\nAppointment booked successfully!\n";
                break;
            }
            case 6: {
                int patientId;
                cout << "Enter Patient ID for Billing: ";
                cin >> patientId;
                Billing().generateBill(patientId, appointments);
                break;
            }
            case 7:
                cout << "\nReturning to main menu...\n";
                break;
            default:
                cout << "\nInvalid choice! Try again.\n";
            }
        } while (choice != 7);
    }
};

// Main function
int main() {
    vector<Patient> patients;
    vector<Doctor> doctors = {Doctor("Dr. Smith", 1), Doctor("Dr. Jones", 2), Doctor("Dr. Kate", 3), Doctor("Dr. Helen", 4) };
    vector<Appointment> appointments;
    Admin admin;
    Ward ward(10);

    welcomeScreen();

    char choice;
    do {
        printHeader("Main Menu");
        cout << "A: Admin | W: Ward | Q: Quit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 'A':
        case 'a':
            admin.managePatients(patients, appointments, doctors);
            break;
        case 'W':
        case 'w': {
            int bedChoice, bedNumber;
            cout << "1. Admit | 2. Discharge | 3. View Beds\nEnter choice: ";
            cin >> bedChoice;
            if (bedChoice == 1) {
                cout << "Enter Bed Number: ";
                cin >> bedNumber;
                ward.admitPatient(bedNumber);
            } else if (bedChoice == 2) {
                cout << "Enter Bed Number: ";
                cin >> bedNumber;
                ward.dischargePatient(bedNumber);
            } else if (bedChoice == 3) {
                ward.viewBedStatus();
            } else {
                cout << "Invalid choice!\n";
            }
            break;
        }
        case 'Q':
        case 'q':
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 'Q' && choice != 'q');

    return 0;
}
