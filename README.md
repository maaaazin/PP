# Hospital Management System

The Hospital Management System is developed using C++ and implements Object-Oriented Programming (OOP) principles to automate and organize hospital tasks. Key OOP concepts such as inheritance, encapsulation, polymorphism, and abstraction are used to represent core hospital entities such as patients, doctors, appointments, billing, and wards.

This project was developed as a **CA3** assignment for the **PP** subject during **Semester 3**.

## 1. Classes and Structure

- **Person**: A base class representing shared attributes for patients and doctors (e.g., name, ID).
- **Patient**: Derived from `Person`, with additional attributes such as age, gender, and disease.
- **Doctor**: Derived from `Person`, with a specialization for representing doctors.
- **Appointment**: Handles scheduling and management of patient-doctor appointments.
- **Billing**: Calculates billing for patients based on their appointments.
- **Ward**: Manages hospital beds, including patient admissions and discharges.

## 2. Object-Oriented Concepts

- **Encapsulation**: Protects patient, doctor, and appointment information by providing access through public methods, ensuring data security.
- **Inheritance**: `Patient` and `Doctor` classes inherit from `Person`, reducing code redundancy and promoting reusability.
- **Polymorphism**: Enables handling different types of persons (patients and doctors) using a common interface, with specific behaviors for each.

## 3. Key Features

- **Disease Tracking**: Each patient's disease is stored and displayed alongside their details during appointments.
- **Appointment Management**: Administrators can schedule, view, and manage appointments for patients with available doctors.
- **Billing**: Automatically generates billing based on appointments.
- **Ward Management**: Admits or discharges patients to/from hospital beds and monitors the current bed status.

---

## Project Team

| Group Member Name | PRN              |
|-------------------|------------------|
| Kritika Nair      | 23070122118      |
| Madhura Panvelkar | 23070122127      |
| Harshada Mahakmali| 23070122103      |
| Maazin Kazi       | 23070122126      |

---
