# C++ Projects

A collection of three C++ projects built during my first year at Universiti Sains Malaysia (USM), each demonstrating different aspects of object-oriented programming and data structures in C++.

---

## Projects

| Project | File | Key Concepts |
|---|---|---|
| Banking System | `banking_system.cpp` | Operator overloading, file persistence, STL map, exception handling |
| Paddy Revenue Management | `paddy_system.cpp` | Inheritance, composition, friend functions, input validation |
| Text Encryption and Decryption | `encryption_system.cpp` | Custom Stack and Queue from scratch, templates, inheritance |

---

## 1. Banking System

A console-based banking application that simulates real bank account operations with persistent data storage. Account records survive between program runs using file I/O.

### Features
- Open a new bank account with auto-incremented account number
- Deposit and withdraw funds with minimum balance enforcement (RM 500)
- Balance enquiry by account number
- Close an account and remove it from the system
- View all accounts and their balances
- Data persistence: all accounts are saved to Bank.data and loaded automatically on the next startup so no data is ever lost

### Key C++ Concepts

**Operator Overloading** — Three operators are overloaded for the Account class. ofstream<< serializes an account to a file. ifstream>> deserializes an account from a file. ostream<< formats account details for console output. This makes file I/O and display seamlessly integrated with the class itself.

**File Persistence** — The Bank constructor opens Bank.data on startup and loads all stored accounts into a map. Every account creation, update, or deletion rewrites the file. The destructor also saves on program exit so nothing is lost.

**STL map** — Accounts are stored in map<long, Account> keyed by account number, giving O(log n) lookup for every operation.

**Static Member Variable** — Account::NextAccountNumber tracks the last assigned account number at class level and is restored from the file on startup so account numbers never repeat across sessions.

**Custom Exception Class** — InsufficientFunds is thrown when a withdrawal would drop the balance below the minimum, demonstrating C++ exception handling with a user-defined exception type.

### Class Structure
```
Account
  - accountNumber (long, static auto-increment)
  - firstName, lastName (string)
  - balance (float)
  + Deposit(), Withdraw()
  + operator<< overloaded for ofstream, ifstream, and ostream

Bank
  - accounts: map<long, Account>
  + OpenAccount(), Deposit(), Withdraw()
  + BalanceEnquiry(), CloseAccount(), ShowAllAccounts()
  Constructor loads from file, Destructor saves to file
```

### How to Run
```bash
g++ banking_system.cpp -o banking_system
./banking_system
```

---

## 2. Paddy Revenue Management System

A console-based system for calculating and managing paddy farm revenue. Demonstrates inheritance and composition in a real-world agricultural domain.

### Features
- Input paddy base information: price per ton, subsidy per ton, planting cost per relong
- Input farmer sales information: name, ID, field size, paddy weight, deduction percentage
- Calculate net weight after deduction, total paddy price, subsidy, gross revenue, and net income
- Determine productivity rate: high, moderate, or low based on yield per relong
- Calculate incentive of RM 200 per relong for high-productivity farmers
- Display full revenue breakdown and farmer productivity list
- Input validation throughout including field size enforced as multiples of 0.25 relong using fmod

### Key C++ Concepts

**Inheritance** — paddySalesInfo inherits from farmerInfo, extending farmer identity data with field size, paddy weight, and deduction percentage in a clean class hierarchy.

**Composition** — paddyRevenue holds instances of both PaddyBaseInfo and paddySalesInfo as member variables, combining all data needed for calculation in one orchestrating class.

**Friend Functions** — userInputPaddybaseInfo() and userInputPaddySales() are declared as friend functions of paddyRevenue, allowing clean separation of input logic while still accessing private setters.

**Overloaded Constructors with Default Parameters** — Both PaddyBaseInfo and farmerInfo use a single constructor with default parameter values serving as both default and parameterized constructor.

**fmod Validation** — Field size is validated using fmod(fsize, 0.25) to ensure values are always valid multiples of 0.25 relong, reflecting real measurement conventions.

### Class Structure
```
PaddyBaseInfo
  - basePricePerTon, subsidyPerTon, plantingCostPerRelong

farmerInfo
  - name, farmerID

paddySalesInfo : public farmerInfo
  - fieldSizeInRelong, paddyWeight, weightDeductionPercentage
  + calculateNetWeight()

paddyRevenue (uses composition)
  - baseInfo: PaddyBaseInfo
  - salesInfo: paddySalesInfo
  - TotalPaddyPrice, totalSubsidy, incentive, grossRevenue, NetIncome
  + calculateTotalPaddyPrice(), calculateIncentive()
  + DetermineProductivityRate(), CalculateNetIncome()
  + DisplayPaddySalesInfo(), DisplayPadyyRevenueInformation()
  friend: userInputPaddybaseInfo(), userInputPaddySales()
```

### How to Run
```bash
g++ paddy_system.cpp -o paddy_system
./paddy_system
```

---

## 3. Text Encryption and Decryption System

A console-based text encryption tool that reads plaintext from a file, encrypts it using a two-step process, and can decrypt it back to the original. Built entirely using custom data structures with no STL stack or queue.

### How Encryption Works
1. Reverse the input text by pushing every character onto a custom Stack and popping them off
2. Substitute vowels with symbols: a to *, e to @, i to #, o to $, u to &

Decryption applies both steps in reverse order to recover the original text.

### Features
- Read input text from any file path
- Encrypt and display the encrypted result in the console
- Decrypt an encrypted file and display the original text
- Input validation for menu choices and file reading errors

### Key C++ Concepts

**Custom Stack from Scratch** — A templated linked-list Stack is implemented without any STL container. It supports push(), pop(), isEmpty(), and proper memory cleanup in the destructor using manual pointer management with new and delete.

**Custom Queue from Scratch** — A templated linked-list Queue is implemented with enqueue(), dequeue(), and isEmpty(), maintaining both front and back pointers for O(1) operations at both ends.

**Template Classes** — All four core classes (Stack<T>, Queue<T>, FileHandler<T>, TextManipulator<T>) are fully templated, making them reusable with any data type.

**Inheritance** — Encryption<T> and Decryption<T> both extend TextManipulator<T>, inheriting the reversal and vowel substitution logic and adding their specific encrypt and decrypt methods.

**File I/O** — FileHandler<T> reads from and writes to files using ifstream and ofstream with istreambuf_iterator for full content extraction in a single line.

### Class Structure
```
Stack<T>
  - linked-list node with push, pop, isEmpty, destructor

Queue<T>
  - linked-list node with enqueue, dequeue, isEmpty, destructor

FileHandler<T>
  + readFromFile(), writeToFile()

TextManipulator<T>
  + reverseCharacters() using Stack<char>
  + replaceVowels() with vowel to symbol substitution

Encryption<T> : public TextManipulator<T>
  + encrypt() — reverse then replace vowels

Decryption<T> : public TextManipulator<T>
  + decrypt() — reverse then revert vowel symbols

UserInterface
  + displayMenu(), getInput() with validation
```

### How to Run
```bash
g++ encryption_system.cpp -o encryption_system
./encryption_system
```

Create a plain text file such as input.txt, then enter the filename when prompted by the menu.

---

## Prerequisites

- C++ compiler: g++ or MSVC
- C++11 or above recommended

```bash
g++ <filename>.cpp -o <output_name>
./output_name
```
