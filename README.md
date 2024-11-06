# Healthcare Management System

## Project Description

This project is a simple Healthcare Management System developed in C++ for managing doctors and their appointments. The system allows an administrator to perform key operations related to doctor and appointment records, including adding, updating, deleting, and searching for records. Additionally, it supports query-based searches for doctors and appointments based on various attributes.

### Features

- **Doctor Management**: The administrator can add new doctors, delete existing doctors, and update doctor details such as name and address.
- **Appointment Management**: The administrator can add appointments for specific doctors, delete appointments, and update appointment dates.
- **Search and Query System**: 
  - The system allows efficient searching of records through primary and secondary indexes.
  - Supported queries include:
    - Finding all appointments for a specific doctor.
    - Retrieving specific doctor information based on Doctor ID.
    - Accessing appointments associated with a specific Doctor ID.
  - Queries utilize keywords such as `Select`, `From`, and `Where` for ease of use.

### Data Storage Format

Data for doctors and appointments is stored in text files with specific formatting:
- **Delimited fields** with **length indicators** to facilitate record storage and retrieval.
- **Doctor Records**:
  - Doctor ID (15 characters) - Primary Key
  - Doctor Name (30 characters)
  - Address (30 characters)
- **Appointment Records**:
  - Appointment ID (15 characters) - Primary Key
  - Appointment Date (30 characters)
  - Doctor ID (15 characters) - Secondary Key

### Indexing Structure

To support efficient operations, the system maintains the following indexes:
- **Primary Indexes**:
  - Doctor ID for quick access to doctor records.
  - Appointment ID for direct access to appointments.
- **Secondary Indexes**:
  - Doctor ID in the Appointments data file.
  - Doctor Name in the Doctors data file.
- **Index Characteristics**:
  - All indexes are sorted in ascending order.
  - Binary search is used for index lookups.
  - Secondary indexes are implemented using a linked list structure, ensuring that all secondary indexes are bound to the primary index.

### Functionality Details

- **Add, Update, and Delete**:
  - When adding a new record, the system checks an `AVAIL LIST` for available slots, reusing space when possible.
  - If a record already exists, it is not added again to prevent duplication.
  - Records marked for deletion are not physically removed but are flagged with a `*` marker. This flag allows the system to manage record availability without modifying the underlying data files.
- **Search Operations**:
  - Searches are based on either primary or secondary indexes, ensuring quick access to records.
  - All secondary indexes are connected to the primary indexes without direct address binding.
  
### Supported User Queries

The system accepts queries in the following format:
- `Select all from Doctors where Doctor ID=’xxx’`: Retrieves a doctor’s details using the primary index.
- `Select all from Appointments where Doctor ID=’xxx’`: Retrieves appointments for a doctor using the secondary index.
- `Select Doctor Name from Doctors where Doctor ID=’xxx’`: Uses the secondary index to get a doctor’s name based on Doctor ID.

### Main Menu Options

Upon running the program, the following options are available to the administrator:

- Add New Doctor
- Add New Appointment
- Update Doctor Name (Doctor ID)
- Update Appointment Date (Appointment ID)
- Delete Appointment (Appointment ID)
- Delete Doctor (Doctor ID)
- Print Doctor Info (Doctor ID)
- Print Appointment Info (Appointment ID)
- Write Query
- Exit

> **Note**: User Interface and Input Validation are not included in this project. The focus is on implementing the backend functionality for data management and processing.

---

This Healthcare Management System provides a foundational framework for managing doctor and appointment records, with built-in support for efficient record storage, retrieval, and querying.
