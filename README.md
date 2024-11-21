# Database-Engine

---

A lightweight, console-based database program written in C++ that allows users to create, manage, and manipulate simple records stored in a CSV file.  

---

## **Features**

- **Insert Records**: Add records with automatically generated IDs.  
- **Display Records**: View all stored records in a tabular format.  
- **Delete Records**: Remove records by their unique ID.  
- **CSV File Storage**: Data is saved persistently in a CSV file for future use.  

---

## **Installation**

Follow these steps to set up and run the program:

1. **Clone the Repository**  
   ```bash
   git clone https://github.com/<your-username>/<repository-name>.git
   cd <repository-name>
   ```

2. **Compile the Program**  
   Use the following command to compile the source code:  
   ```bash
   g++ -std=c++17 simple_database.cpp -o simple_database
   ```

3. **Run the Program**  
   Execute the compiled program with:  
   ```bash
   ./simple_database
   ```

---

## **Usage**

### **Workflow**

1. **Enter Database Filename**  
   When prompted, enter the name of the database file (without the `.csv` extension).  

2. **Main Menu Options**  
   - **`1`: Insert Record**  
     - Adds a new record by prompting for `Name`, `Age`, and `City`.  
   - **`2`: Display All Records**  
     - Displays all existing records.  
   - **`3`: Delete Record**  
     - Deletes a record by entering its unique ID.  
   - **`4`: Exit Program**  
     - Exits the program and saves changes.

---

### **Example Interaction**

```plaintext
Enter database filename (without .csv): users

--- Simple Database Menu ---
1. Insert Record
2. Display All Records
3. Delete Record
4. Exit
Enter your choice: 1

Enter name: John Doe
Enter age: 30
Enter city: New York
Record added successfully!

--- Simple Database Menu ---
1. Insert Record
2. Display All Records
3. Delete Record
4. Exit
Enter your choice: 2

--- Records ---
ID    Name       Age    City
1     John Doe   30     New York
```

---
