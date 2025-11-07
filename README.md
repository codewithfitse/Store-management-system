# 🏪 Store Management System (C++)

A simple **Store Management System** built in C++ for managing store inventory efficiently.  
It allows users to **add, view, search, update, and delete items** in a store, as well as **save and load data from a file**.  
This project was developed as part of a coursework requirement for **Deliverable I–III** (Document Analysis, Implementation I, and Implementation II).

---

## 📘 Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Deliverables Breakdown](#deliverables-breakdown)
- [System Requirements](#system-requirements)
- [How to Run](#how-to-run)
- [File Format](#file-format)
- [Sample Run](#sample-run)
- [Future Improvements](#future-improvements)
- [Author](#author)

---

## 💡 Project Overview

The **Store Management System** helps small retail shops automate basic store operations like:
- Tracking available items
- Managing stock quantity
- Updating prices
- Maintaining a digital record of inventory in a text file

This project replaces manual paper-based systems with a console-based program, reducing human error and saving time.

---

## 🚀 Features

✅ Add new items to the store inventory  
✅ Display all items neatly in a table  
✅ Search items by name  
✅ Update item details (quantity, price, supplier, etc.)  
✅ Delete an item using its ID  
✅ Save data to a text file (`inventory.txt`)  
✅ Load saved inventory from file automatically on startup  
✅ Simple and easy-to-navigate **menu system**  
✅ Input validation for integers and doubles  

---

## 🧩 Deliverables Breakdown

### **Deliverable I – Document Analysis**
Includes:
- Background Information & Problem Statement  
- Objectives  
- Requirement Collection (Interview & Document Analysis)  
- Functional Requirements  
- Real-world Entities  
- Variable Definitions  

### **Deliverable II – Implementation I**
Implementation of:
- A **menu-based program** using **functions** and **arrays**  
- Handles add, view, search, update, and delete operations

### **Deliverable III – Implementation II**
Enhancement of Deliverable II by:
- **Incorporating File Handling**  
- Saving and loading inventory data persistently from `inventory.txt`

---

## ⚙️ System Requirements

| Requirement | Description |
|--------------|-------------|
| **Language** | C++ (C++17 or higher recommended) |
| **Compiler** | GCC / G++ / Clang / MSVC |
| **Platform** | Windows, Linux, or macOS |
| **File I/O** | Uses `inventory.txt` for data persistence |

---

## 🧠 How to Run

### 1. **Clone or Copy the Project**
Download or copy the `store.cpp` file to your local system.

### 2. **Compile the Program**
Open terminal (or CMD) in the project directory and run:
```bash
g++ -std=c++17 store.cpp -o store
```
---
====== Store Management System ======
1. Add new item
2. Display all items
3. Search item by name
4. Update item (by ID)
5. Delete item (by ID)
6. Save inventory to file
7. Load inventory from file (overwrite current)
0. Exit
Choose an option: 1

Enter item name: Sugar
Enter category: Food
Enter quantity: 25
Enter unit price: 45.5
Enter supplier name: SweetCo
Item added (ID = 1).
---

### 👨‍💻 Author

Name: Fitsum Zerhun
University: Hope University
Department: Software Engineering
Course: Programming II (C++)
Project: Store Management System
