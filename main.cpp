#include <iostream>
#include <string>
#include <vector>

using namespace std;

void welcomeScreen() {
    cout << "\n======================================================\n";
    cout << "\t    HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "======================================================\n";
    cout << "Loading";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
    }
    cout << "\n\n";
}

void printHeader(string section) {
    cout << "\n================ " << section << " ================\n";
}

class Person {
protected:
    string name;
    int id;

public:
    Person(string name, int id) {
        this->name = name;
        this->id = id;
    }
    virtual void displayInfo() {  
        cout << "\nName: " << name << "\nID: " << id << endl;
    }
    int getId() { 
        return id; 
    }
    string getName() { 
        return name; 
    }
};

class Patient : public Person {
public:
    int age;
    string gender;
    string disease; 

    Patient(string name, int age, string gender, string disease, int id): Person(name, id) {
        this->age = age;
        this->gender = gender;
        this->disease = disease;
    }

    void displayInfo() override {  
        Person::displayInfo();
        cout << "Age: " << age << "\nGender: " << gender << "\nDisease: " << disease << endl; 
    }

    int getAge() { return age; }
    string getGender() { return gender; }
    string getDisease() { return disease; } 
};

class Doctor : public Person {
public:
    Doctor(string name, int id): Person(name, id) {}

    void displayInfo() override {  
        Person::displayInfo();
        cout << "Doctor name: "<< name << "Doctor id: "<< id << endl;
    }
};

class Appointment {
public:
    int patientId;
    int doctorId;
    string date;
    string timeSlot;

    Appointment(int patientId, int doctorId, string date, string timeSlot) {
        this->patientId = patientId;
        this->doctorId = doctorId;
        this->date = date;
        this->timeSlot = timeSlot;
    }

    void displayAppointment(Patient patient, Doctor doctor) {
        cout << "Patient ID: " << patient.getId()
             << " || Name: " << patient.getName()
             << " || Age: " << patient.getAge()
             << " || Gender: " << patient.getGender()
             << " || Disease: " << patient.getDisease() << endl; 

        cout << "Doctor ID: " << doctor.getId()
             << " || Name: " << doctor.getName() << endl;

        cout << "Date: " << date << " || Time Slot: " << timeSlot << "\n";
        cout << "---------------------------------------------------\n";
    }
};

class Billing {
public:
    void generateBill(int patientId, vector<Appointment> appointments) {
        int total = 0;
        for (int i = 0; i < appointments.size(); i++) {
            if (appointments[i].patientId == patientId) {
                total += 500;  
            }
        }
        cout << "\nTotal Bill for Patient ID " << patientId << ": " << total << " units\n";
    }
};

class Ward {
protected:
    vector<pair<int, int>> beds; 
    int totalBeds;

public:
    Ward(int totalBeds) {
        this->totalBeds = totalBeds;
        beds.resize(totalBeds, make_pair(0, -1)); // 0 = free, 1 = occupied, -1 = no patient
    }

    virtual bool admitPatient(int bedNumber, int patientId) {
        if (bedNumber >= 0 && bedNumber < totalBeds && beds[bedNumber].first == 0) {
            beds[bedNumber] = make_pair(1, patientId);
            cout << "\nPatient " << patientId << " admitted to bed " << bedNumber << endl;
            return true;
        } 
        else {
            cout << "\nInvalid or occupied bed!" << endl;
            return false;
        }
    }

    virtual bool dischargePatient(int patientId) {
        for (int i = 0; i < totalBeds; i++) {
            if (beds[i].second == patientId) {
                beds[i] = make_pair(0, -1);
                cout << "\nPatient " << patientId << " discharged from bed " << i << endl;
                return true;
            }
        }
        cout << "\nPatient not found in any bed!" << endl;
        return false;
    }

    void viewBedStatus() {
        printHeader("Bed Status");
        for (int i = 0; i < totalBeds; i++) {
            cout << "Bed " << i << ": ";
            if (beds[i].first == 0) {
                cout << "Free" << endl;
            } 
            else {
                cout << "Occupied by Patient ID: " << beds[i].second << endl;
            }
        }
    }

    int findPatientBed(int patientId) {
        for (int i = 0; i < totalBeds; i++) {
            if (beds[i].second == patientId) {
                return i;
            }
        }
        return -1;
    }
};

class EmergencyWard : public Ward {
public:
    EmergencyWard(int totalBeds): Ward(totalBeds) {}

    bool admitEmergencyPatient(int bedNumber, int patientId) {
        return admitPatient(bedNumber, patientId);
    }
};

class Admin {
private:
    bool isDoctorAvailable(int doctorId, string date, string timeSlot, vector<Appointment>& appointments) {
        for (const Appointment& apt : appointments) {
            if (apt.doctorId == doctorId && apt.date == date && apt.timeSlot == timeSlot) {
                return false;
            }
        }
        return true;
    }

public:
    void managePatients(vector<Patient>& patients, vector<Appointment>& appointments, 
                       vector<Doctor>& doctors, Ward& generalWard, EmergencyWard& emergencyWard) {
        int choice;
        do {
            printHeader("Manage Patients");
            cout << "1. Add Patient\n2. Delete Patient\n3. View Patients\n"
                 << "4. View Appointments\n5. Book Appointment\n6. View Billing\n"
                 << "7. Transfer Patient\n8. Go Back\n\nEnter choice: ";
            cin >> choice;

            if (choice == 1) {
                string name, gender, disease;
                int age;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cin.ignore();
                cout << "Enter Gender: ";
                getline(cin, gender);
                cout << "Enter Disease: "; 
                getline(cin, disease);
                int id = patients.size() + 1;
                patients.push_back(Patient(name, age, gender, disease, id)); 
                cout << "\nPatient added successfully!\n";
            } 
            else if (choice == 2) {
                int id;
                cout << "Enter Patient ID to delete: ";
                cin >> id;
                for (int i = 0; i < patients.size(); i++) {
                    if (patients[i].getId() == id) {
                        patients.erase(patients.begin() + i);
                        cout << "\nPatient deleted successfully!\n";
                        break;
                    }
                }
            } 
            else if (choice == 3) {
                for (int i = 0; i < patients.size(); i++) {
                    patients[i].displayInfo();
                }
            } 
            else if (choice == 4) {
                for (int i = 0; i < appointments.size(); i++) {
                    Patient patient = patients[appointments[i].patientId - 1];
                    Doctor doctor = doctors[appointments[i].doctorId - 1];
                    appointments[i].displayAppointment(patient, doctor);
                }
            } 
            else if (choice == 5) {
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

                if (isDoctorAvailable(doctorId, date, timeSlot, appointments)) {
                    appointments.push_back(Appointment(patientId, doctorId, date, timeSlot));
                    cout << "\nAppointment booked successfully!\n";
                }
                else {
                    cout << "\nDoctor is not available at this time slot. Please choose another time.\n";
                }
            } 
            else if (choice == 6) {
                 int patientId;
                cout << "Enter Patient ID for Billing: ";
                cin >> patientId;
                Billing().generateBill(patientId, appointments);
            }
            else if (choice == 7) {
                int patientId, choice;
                cout << "Enter Patient ID to transfer: ";
                cin >> patientId;
                cout << "1. General to Emergency\n2. Emergency to General\nEnter choice: ";
                cin >> choice;

                if (choice == 1) {
                    int generalBed = generalWard.findPatientBed(patientId);
                    if (generalBed != -1) {
                        cout << "Enter Emergency Bed Number: ";
                        int emergencyBed;
                        cin >> emergencyBed;
                        if (emergencyWard.admitPatient(emergencyBed, patientId)) {
                            generalWard.dischargePatient(patientId);
                        }
                    }
                    else {
                        cout << "Patient not found in general ward!\n";
                    }
                }
                else if (choice == 2) {
                    int emergencyBed = emergencyWard.findPatientBed(patientId);
                    if (emergencyBed != -1) {
                        cout << "Enter General Ward Bed Number: ";
                        int generalBed;
                        cin >> generalBed;
                        if (generalWard.admitPatient(generalBed, patientId)) {
                            emergencyWard.dischargePatient(patientId);
                        }
                    }
                    else {
                        cout << "Patient not found in emergency ward!\n";
                    }
                }
            }
        } 
        while (choice != 8);
    }
};

class Ambulance {
public:
    bool isAvailable;

    Ambulance() {
        isAvailable = true;
    }

    void bookAmbulance() {
        if (isAvailable) {
            isAvailable = false;
            cout << "\nAmbulance booked successfully!\n";
        } 
        else {
            cout << "\nNo ambulance available right now!\n";
        }
    }

    void releaseAmbulance() {
        isAvailable = true;
        cout << "\nAmbulance is now available.\n";
    }
};

int main() {
    vector<Patient> patients;
    vector<Doctor> doctors;
    doctors.push_back(Doctor("Dr. Smith", 1));
    doctors.push_back(Doctor("Dr. Jones", 2));
    doctors.push_back(Doctor("Dr. Kate", 3));
    doctors.push_back(Doctor("Dr. Helen", 4));
    vector<Appointment> appointments;
    Admin admin;
    Ward ward(10);  
    EmergencyWard emergencyWard(5); 
    Ambulance ambulance;  

    welcomeScreen();

    char choice;
     do {
        printHeader("Main Menu");
        cout << "A: Admin | W: Ward | E: Emergency Ward | M: Ambulance | Q: Quit\nEnter your choice: ";
        cin >> choice;

        if (choice == 'A' || choice == 'a') {
            admin.managePatients(patients, appointments, doctors, ward, emergencyWard);
        } 
        else if (choice == 'W' || choice == 'w') {
            int bedChoice, bedNumber, patientId;
            cout << "1. Admit | 2. Discharge | 3. View Beds\nEnter choice: ";
            cin >> bedChoice;
            if (bedChoice == 1) {
                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Bed Number: ";
                cin >> bedNumber;
                ward.admitPatient(bedNumber, patientId);
            } 
            else if (bedChoice == 2) {
                cout << "Enter Patient ID: ";
                cin >> patientId;
                ward.dischargePatient(patientId);
            } 
            else if (bedChoice == 3) {
                ward.viewBedStatus();
            }
        } 
        else if (choice == 'E' || choice == 'e') {
            int emergencyChoice, bedNumber, patientId;
            cout << "1. Admit Emergency Patient | 2. View Beds\nEnter choice: ";
            cin >> emergencyChoice;
            if (emergencyChoice == 1) {
                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Emergency Bed Number: ";
                cin >> bedNumber;
                emergencyWard.admitEmergencyPatient(bedNumber, patientId);
            } 
            else if (emergencyChoice == 2) {
                emergencyWard.viewBedStatus();
            }
        } 
        else if (choice == 'M' || choice == 'm') {
            int ambulanceChoice;
            cout << "1. Book Ambulance | 2. Release Ambulance\nEnter choice: ";
            cin >> ambulanceChoice;
            if (ambulanceChoice == 1) {
                ambulance.bookAmbulance();
            } 
            else if (ambulanceChoice == 2) {
                ambulance.releaseAmbulance();
            }
        }

    } while (choice != 'Q' && choice != 'q');

    return 0;
}
