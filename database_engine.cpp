#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <algorithm>
#include <limits>

class SimpleDB {
private:
    std::string table_name;
    std::string file_path;
    std::vector<std::string> schema;
    std::vector<std::unordered_map<std::string, std::string>> data;
    int next_id = 1;

    void saveToFile() {
        std::ofstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error opening file for writing\n";
            return;
        }

        // Write headers
        for (size_t i = 0; i < schema.size(); ++i) {
            file << schema[i];
            if (i < schema.size() - 1) file << ",";
        }
        file << std::endl;

        // Write data
        for (const auto& row : data) {
            for (size_t i = 0; i < schema.size(); ++i) {
                file << row.at(schema[i]);
                if (i < schema.size() - 1) file << ",";
            }
            file << std::endl;
        }
        file.close();
    }

    void loadFromFile() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error opening file for reading\n";
            return;
        }

        data.clear();
        std::string line;
        
        // Read headers
        if (std::getline(file, line)) {
            std::stringstream header_ss(line);
            std::string header;
            schema.clear();
            while (std::getline(header_ss, header, ',')) {
                schema.push_back(header);
            }
        }

        // Read data
        while (std::getline(file, line)) {
            std::unordered_map<std::string, std::string> row;
            std::stringstream ss(line);
            std::string value;
            size_t col = 0;

            while (std::getline(ss, value, ',') && col < schema.size()) {
                row[schema[col]] = value;
                ++col;
            }
            
            // Update next_id to be larger than existing IDs
            int current_id = std::stoi(row["id"]);
            next_id = std::max(next_id, current_id + 1);
            
            data.push_back(row);
        }
        file.close();
    }

public:
    SimpleDB(const std::string& name) : table_name(name), file_path(name + ".csv") {
        // Create table with predefined schema
        schema = {"id", "name", "age", "city"};
        
        // Load existing data if file exists
        if (std::filesystem::exists(file_path)) {
            loadFromFile();
        }
    }

    void insert() {
        std::unordered_map<std::string, std::string> record;
        
        // Automatically assign incremental ID
        record["id"] = std::to_string(next_id++);

        // Prompt for name
        std::string name;
        std::cout << "Enter name: ";
        std::getline(std::cin, name);
        record["name"] = name;

        // Prompt for age
        std::string age;
        while (true) {
            std::cout << "Enter age: ";
            std::getline(std::cin, age);
            
            // Validate age is a number
            try {
                std::stoi(age);
                break;
            } catch (...) {
                std::cout << "Invalid age. Please enter a number.\n";
            }
        }
        record["age"] = age;

        // Prompt for city
        std::string city;
        std::cout << "Enter city: ";
        std::getline(std::cin, city);
        record["city"] = city;

        // Insert record
        data.push_back(record);
        saveToFile();
        std::cout << "Record inserted successfully with ID " << record["id"] << std::endl;
    }

    void displayAll() {
        std::cout << "\nAll Records:\n";
        for (const auto& row : data) {
            for (const auto& [key, val] : row) {
                std::cout << key << ": " << val << " ";
            }
            std::cout << std::endl;
        }
    }

    void deleteRecord() {
        std::string id_to_delete;
        std::cout << "Enter ID to delete: ";
        std::getline(std::cin, id_to_delete);

        auto it = std::remove_if(data.begin(), data.end(), 
            [&id_to_delete](const auto& row) { 
                return row.at("id") == id_to_delete; 
            });

        if (it != data.end()) {
            data.erase(it, data.end());
            saveToFile();
            std::cout << "Record with ID " << id_to_delete << " deleted successfully.\n";
        } else {
            std::cout << "No record found with ID " << id_to_delete << std::endl;
        }
    }

    void menu() {
        while (true) {
            std::cout << "\n--- Simple Database Menu ---\n";
            std::cout << "1. Insert Record\n";
            std::cout << "2. Display All Records\n";
            std::cout << "3. Delete Record\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter your choice: ";

            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "1") {
                insert();
            } else if (choice == "2") {
                displayAll();
            } else if (choice == "3") {
                deleteRecord();
            } else if (choice == "4") {
                break;
            } else {
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    std::string filename;
    std::cout << "Enter database filename (without .csv): ";
    std::getline(std::cin, filename);

    SimpleDB db(filename);
    db.menu();

    return 0;
}