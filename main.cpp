#include <iostream>
#include <string>
#include <vector>

using namespace std;

void welcomeScreen()
{
    cout << "\n======================================================\n";
    cout << "\t    HOSPITAL MANAGEMENT SYSTEM\n";
    cout << "======================================================\n";
    cout << "Loading";
    for (int i = 0; i < 3; ++i)
    {
        cout << ".";
    }
    cout << "\n\n";
}

void printHeader(string section)
{
    cout << "\n================ " << section << " ================\n";
}

class Person
{
protected:
    string name;
    int id;

public:
    Person(string name, int id)
    {
        this->name = name;
        this->id = id;
    }
    virtual void displayInfo()
    {
        cout << "\nName: " << name << "\nID: " << id << endl;
    }
    int getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }
};

class Patient : public Person
{
public:
    int age;
    string gender;
    string disease;

    Patient(string name, int age, string gender, string disease, int id) : Person(name, id)
    {
        this->age = age;
        this->gender = gender;
        this->disease = disease;
    }

    void displayInfo() override
    {
        Person::displayInfo();
        cout << "Age: " << age << "\nGender: " << gender << "\nDisease: " << disease << endl;
    }

    int getAge() { return age; }
    string getGender() { return gender; }
    string getDisease() { return disease; }
};

class Doctor : public Person
{
public:
    Doctor(string name, int id) : Person(name, id) {}

    void displayInfo() override
    {
        Person::displayInfo();
        cout << "Doctor name: " << name << "Doctor id: " << id << endl;
    }
};

class Appointment
{
public:
    int patientId;
    int doctorId;
    string date;
    string timeSlot;

    Appointment(int patientId, int doctorId, string date, string timeSlot)
    {
        this->patientId = patientId;
        this->doctorId = doctorId;
        this->date = date;
        this->timeSlot = timeSlot;
    }

    void displayAppointment(Patient patient, Doctor doctor)
    {
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

class Billing
{
public:
    void generateBill(int patientId, vector<Appointment> appointments)
    {
        int total = 0;
        for (int i = 0; i < appointments.size(); i++)
        {
            if (appointments[i].patientId == patientId)
            {
                total += 500;
            }
        }
        cout << "\nTotal Bill for Patient ID " << patientId << ": " << total << " Rupees\n";
    }
};

class Ward
{
public:
    vector<int> beds;
    vector<int> patientToBed; 
    int totalBeds;

    Ward(int totalBeds) : totalBeds(totalBeds)
    {
        beds.resize(totalBeds, 0);
        patientToBed.resize(totalBeds, -1); 
    }

    bool isPatientAlreadyAdmitted(int patientId)
    {
        for (int i = 0; i < totalBeds; i++)
        {
            if (patientToBed[i] == patientId)
            {
                return true;
            }
        }
        return false;
    }

    void admitPatient(int patientId, int bedNumber)
    {
        if (isPatientAlreadyAdmitted(patientId))
        {
            cout << "\nError: Patient ID " << patientId << " is already occupying a bed.\n";
            return;
        }

        if (bedNumber >= 0 && bedNumber < totalBeds && beds[bedNumber] == 0)
        {
            beds[bedNumber] = 1;
            patientToBed[bedNumber] = patientId;
            cout << "\nPatient ID " << patientId << " admitted to bed " << bedNumber << endl;
        }
        else
        {
            cout << "\nInvalid or occupied bed!" << endl;
        }
    }

    void dischargePatient(int patientId, int bedNumber)
    {
        if (bedNumber >= 0 && bedNumber < totalBeds && beds[bedNumber] == 1 &&
            patientToBed[bedNumber] == patientId)
        {
            beds[bedNumber] = 0;
            patientToBed[bedNumber] = -1;
            cout << "\nPatient ID " << patientId << " discharged from bed " << bedNumber << endl;
        }
        else
        {
            cout << "\nInvalid bed or patient not found in the specified bed!" << endl;
        }
    }

    void viewBedStatus()
    {
        printHeader("Bed Status");
        for (int i = 0; i < totalBeds; i++)
        {
            cout << "Bed " << i << ": ";
            if (beds[i] == 0)
            {
                cout << "Free" << endl;
            }
            else
            {
                cout << "Occupied by Patient: " << patientToBed[i] << endl;
            }
        }
    }
};

class Admin
{
public:
    void managePatients(vector<Patient> &patients, vector<Appointment> &appointments, vector<Doctor> &doctors)
    {
        int choice;
        do
        {
            printHeader("Manage Patients");
            cout << "1. Add Patient\n2. Delete Patient\n3. View Patients\n4. View Appointments\n5. Book Appointment\n6. View Billing\n7. Go Back\n\nEnter choice: ";
            cin >> choice;

            if (choice == 1)
            {
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

            else if (choice == 2)
            {
                int id;
                cout << "Enter Patient ID to delete: ";
                cin >> id;
                for (int i = 0; i < patients.size(); i++)
                {
                    if (patients[i].getId() == id)
                    {
                        patients.erase(patients.begin() + i);
                        cout << "\nPatient deleted successfully!\n";
                        break;
                    }
                }
            }

            else if (choice == 3)
            {
                for (int i = 0; i < patients.size(); i++)
                {
                    patients[i].displayInfo();
                }
            }

            else if (choice == 4)
            {
                for (int i = 0; i < appointments.size(); i++)
                {
                    Patient patient = patients[appointments[i].patientId - 1];
                    Doctor doctor = doctors[appointments[i].doctorId - 1];
                    appointments[i].displayAppointment(patient, doctor);
                }
            }

            else if (choice == 5)
            {
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

                bool appointmentExists = false;

                for (int i = 0; i < appointments.size(); i++)
                {
                    if (appointments[i].doctorId == doctorId &&
                        appointments[i].date == date &&
                        appointments[i].timeSlot == timeSlot)
                    {
                        appointmentExists = true;
                        break;
                    }
                }

                if (appointmentExists)
                {
                    cout << "\nError: Appointment already exists for the same doctor, date, and time.\n";
                }
                else
                {
                    appointments.push_back(Appointment(patientId, doctorId, date, timeSlot));
                    cout << "\nAppointment booked successfully!\n";
                }
            }

            else if (choice == 6)
            {
                int patientId;
                cout << "Enter Patient ID for Billing: ";
                cin >> patientId;
                Billing().generateBill(patientId, appointments);
            }
        } while (choice != 7);
    }
};

class Ambulance
{
public:
    bool isAvailable;

    Ambulance()
    {
        isAvailable = true;
    }

    void bookAmbulance()
    {
        if (isAvailable)
        {
            isAvailable = false;
            cout << "\nAmbulance booked successfully!\n";
        }
        else
        {
            cout << "\nNo ambulance available right now!\n";
        }
    }

    void releaseAmbulance()
    {
        isAvailable = true;
        cout << "\nAmbulance is now available.\n";
    }
};

class EmergencyWard : public Ward
{
public:
    EmergencyWard(int totalBeds) : Ward(totalBeds) {}

    void admitEmergencyPatient(int patientId, int bedNumber, Ward &generalWard)
    {
        if (generalWard.isPatientAlreadyAdmitted(patientId))
        {
            cout << "\nError: Patient ID " << patientId << " is already admitted in the General Ward.\n";
            return;
        }

        if (beds[bedNumber] == 0)
        {
            beds[bedNumber] = 1;
            cout << "\nEmergency patient admitted to bed " << bedNumber << endl;
        }
        else
        {
            cout << "\nBed " << bedNumber << " is occupied. Please choose another bed!\n";
        }
    }
};

int main()
{
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
    do
    {
        printHeader("Main Menu");
        cout << "A: Admin | W: Ward | E: Emergency Ward | M: Ambulance | Q: Quit\nEnter your choice: ";
        cin >> choice;

        if (choice == 'A' || choice == 'a')
        {
            admin.managePatients(patients, appointments, doctors);
        }
        else if (choice == 'W' || choice == 'w')
        {
            int bedChoice, bedNumber, patientId;
            cout << "1. Admit | 2. Discharge | 3. View Beds\nEnter choice: ";
            cin >> bedChoice;

            if (bedChoice == 1)
            { // Admit Patient
                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Bed Number: ";
                cin >> bedNumber;
                ward.admitPatient(patientId, bedNumber);
            }
            else if (bedChoice == 2)
            { 
                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Bed Number: ";
                cin >> bedNumber;
                ward.dischargePatient(patientId, bedNumber);
            }
            else if (bedChoice == 3)
            {
                ward.viewBedStatus();
            }
        }
        else if (choice == 'E' || choice == 'e')
        {
            int emergencyChoice, bedNumber, patientId;
            cout << "1. Admit Emergency Patient | 2. Discharge Patient | 3. View Beds\nEnter choice: ";
            cin >> emergencyChoice;

            if (emergencyChoice == 1)
            { 
                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Bed Number: ";
                cin >> bedNumber;
                emergencyWard.admitEmergencyPatient(patientId, bedNumber, ward);
            }
            else if (emergencyChoice == 2)
            { 
                cout << "Enter Patient ID: ";
                cin >> patientId;
                cout << "Enter Bed Number: ";
                cin >> bedNumber;
                emergencyWard.dischargePatient(patientId, bedNumber); 
            }
            else if (emergencyChoice == 3)
            {                                  
                emergencyWard.viewBedStatus(); 
            }
        }

        else if (choice == 'M' || choice == 'm')
        {
            int ambulanceChoice;
            cout << "1. Book Ambulance | 2. Release Ambulance\nEnter choice: ";
            cin >> ambulanceChoice;
            if (ambulanceChoice == 1)
            {
                ambulance.bookAmbulance();
            }
            else if (ambulanceChoice == 2)
            {
                ambulance.releaseAmbulance();
            }
        }
    } while (choice != 'Q' && choice != 'q');

    return 0;
}
