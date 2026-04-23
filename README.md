# Mini-Project
# 🏦 Bank Management System (C Project)

A simple **Bank Management System implemented in C** that allows users to perform basic banking operations such as **account creation, login, deposits, withdrawals, transfers, and transaction history** using **CSV file storage**.

---

# 📌 Project Objective

The objective of this project is to build a **console-based banking application** that demonstrates:

* 📂 File handling in C
* 🗄️ Data storage using CSV files
* 🔐 User authentication
* 💰 Banking transaction simulation
* 🧠 Structured programming concepts

---

# 🛠️ Technologies Used

| Technology            | Purpose                          |
| --------------------- | -------------------------------- |
| 💻 C Programming      | Core implementation              |
| 📂 File Handling      | Data storage                     |
| 📑 CSV Files          | Simulated database               |
| 🧰 Standard Libraries | Input/output & string operations |

### Libraries Used

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
```

---

# 📁 Project File Structure

The system stores data in **two CSV files**.

## 1️⃣ accounts_master.csv

Stores account information.

| Field       | Description           |
| ----------- | --------------------- |
| AccountNo   | Unique account number |
| Name        | Customer name         |
| PIN         | Account security PIN  |
| AccountType | Savings / Current     |

Example:

```
AccountNo,Name,PIN,AccountType
1001,John,1234,Savings
```

---

## 2️⃣ transactions.csv

Stores transaction history.

| Field     | Description        |
| --------- | ------------------ |
| AccountNo | Account number     |
| Type      | Transaction type   |
| Amount    | Transaction amount |
| Balance   | Updated balance    |

Example:

```
AccountNo,Type,Amount,Balance
1001,DEPOSIT,2000,5000
```

---

# ⚙️ System Workflow

```
Start Program
      ↓
Initialize Files
      ↓
Main Menu
 ├── 🔐 Login
 │      ↓
 │   👤 User Menu
 │   ├ 💰 Check Balance
 │   ├ ➕ Deposit Money
 │   ├ ➖ Withdraw Money
 │   ├ 🔁 Transfer Money
 │   └ 📜 Transaction History
 │
 ├── 🆕 Create Account
 │
 └── ❌ Exit
```

---

# 🧩 Functional Modules

## 🆕 Account Creation

Allows a new user to create a bank account.

Steps:

1️⃣ Enter name
2️⃣ Select account type
3️⃣ Set 4-digit PIN
4️⃣ Enter initial deposit

Minimum deposit:

```
₹2000
```

---

## 🔐 Login System

Users log in using:

* Account Number
* 4-digit PIN

Security features:

* 🔒 Hidden PIN input
* 🚫 Maximum **3 login attempts**

---

## 💰 Check Balance

Displays the **latest balance** by reading the last transaction entry from the transaction file.

---

## ➕ Deposit Money

Allows users to deposit funds into their account.

Process:

```
Enter amount → Update balance → Save transaction
```

Transaction type recorded:

```
DEPOSIT
```

---

## ➖ Withdraw Money

Users can withdraw money with validation.

Rules:

* Amount must be positive
* Minimum balance must remain

Minimum balance requirement:

```
₹2000
```

---

## 🔁 Transfer Money

Allows transferring funds between accounts.

Steps:

1️⃣ Enter receiver account number
2️⃣ Enter transfer amount
3️⃣ Update both accounts

Transaction types recorded:

```
TRANSFER_OUT
TRANSFER_IN
```

---

## 📜 Transaction History

Displays all transactions for the user.

Example output:

```
Type            Amount        Balance
DEPOSIT         2000          5000
WITHDRAW        1000          4000
```

---

# 👤 User Menu

After login, users can perform the following operations:

```
1️⃣ Check Balance
2️⃣ Deposit Money
3️⃣ Withdraw Money
4️⃣ Transfer Money
5️⃣ View Transaction History
6️⃣ Logout
```

---

# ✨ Features

✅ Account creation
✅ Secure login system
✅ Hidden PIN entry
✅ Deposit and withdrawal system
✅ Fund transfer between accounts
✅ Transaction history tracking
✅ Minimum balance validation
✅ CSV-based data storage

---

# ⚠️ Limitations

* ❌ No graphical user interface
* ❌ PIN not encrypted
* ❌ No real database integration
* ❌ Single-user environment

---

# 🚀 Future Improvements

Possible upgrades:

* 🖥️ GUI using **C++ / Java / Python**
* 🗄️ Database integration (MySQL)
* 🏧 ATM simulation
* 👨‍💼 Admin dashboard
* 🔐 Password encryption
* 📊 Detailed account analytics

---

# 📚 Conclusion

The **Bank Management System in C** demonstrates how basic banking operations can be implemented using **file handling and structured programming**.

This project helps in understanding:

* 📂 Data storage using files
* 🔐 User authentication mechanisms
* 💰 Transaction processing logic

It serves as a **practical application of core C programming concepts** for building real-world systems.

---

# 👨‍💻 Author

**Piyush Harish Chaudhari**
BS (AI & DS)

