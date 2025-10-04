# Library-Management

A simple command-line Library Management application written in modern C++.

This is a small, self-contained project intended as a learning portfolio piece. It supports basic library operations such as managing books and users, borrowing and returning books, simple search/filtering, and logging of transactions and login events. Data is stored in CSV files in the `data/` directory so the program has persistent state between runs.

## Features
- Add, edit and search books
- Add and remove users (admin)
- Borrow and return books (members)
- Simple fine calculation for late returns
- Login with password hashing (SHA-256 via OpenSSL)
- Transaction and login logging (CSV)

## Repository layout

```
LICENSE
README.md
data/
  books.csv
  login_logs.csv
  transactions.csv
  users.csv
include/
  *.h
src/
  *.cpp
tests/
  (optional tests)
```

## Requirements
- A working C++ toolchain (g++ recommended)
- OpenSSL development libraries (for SHA-256)
- Make sure the compiler can find headers in `include/` (build command below uses `-Iinclude`).

On Windows, MSYS2 (UCRT64) is a convenient environment. If using MSYS2 you can install dependencies with pacman (example):

```
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-openssl
```

Adjust package names and instructions for your platform if needed.

## Build

You can build the project using the supplied build task or by calling g++ directly. Example Windows/MSYS2 (PowerShell) command used during development:

```powershell
C:\msys64\ucrt64\bin\g++.exe -Iinclude -fdiagnostics-color=always -g \
  src/main.cpp src/book.cpp src/library.cpp src/users.cpp src/utils.cpp src/logs.cpp src/auth.cpp \
  -o main.exe -lssl -lcrypto
```

There is also a VS Code task named "C/C++: Build All" in this workspace which runs a similar command.

## Run

Run the produced executable from the repository root in PowerShell:

```powershell
.\main.exe
```

The program reads and updates CSV files in `data/` (books/users/transactions/login_logs).

## Data formats

books.csv (header written by program):

```
Title,Author,Year,Units,Genres,BookId
```

Genres are stored as a `;`-separated list in the Genres field. Note: the CSV parser is simple and does not handle quoted commas — avoid using raw commas inside titles/authors.

users.csv (header written by program):

```
studentId,studentName,book1,book2,book3Id,book4,book5,role,hashedPassword
```

Each `bookN` column encodes `bookId;borrowDate;dueDate` or `0;0;0` if empty. The program currently stores exactly five borrowed-book slots per user in the CSV.

transactions.csv entries (appends): `userId, bookId, ACTION, YYYY-MM-DD HH:MM:SS`

login_logs.csv entries (appends): `ACTION, userId, userName, YYYY-MM-DD HH:MM:SS, status, message`

## Known issues & TODO (recommended before publishing)

These are small, non-blocking items but worth noting in the project README so visitors know the limits:

1. Recursive restart flow: `start()` → `UserLogin()` → `actions()` → calls `start()` on logout. This can grow the call stack after many login/logout cycles. Consider refactoring to a single top-level loop.
2. Empty-database guards: `addbook()` and `addUser()` assume there is at least one entry to derive a new ID (`books[books.size()-1]`). If a CSV is empty the program will crash. Add checks and start IDs at 1 when DB is empty.
3. CSV parsing is naive (split on commas). Fields containing commas will break parsing. For a robust solution use a CSV library or ensure fields are quoted/escaped consistently.
4. Password hashing uses raw SHA-256 without per-user salt — acceptable for a demo but not production-ready. Documented here for clarity.
5. Some headers use `using namespace std;` which is discouraged in headers.

## Suggestions for improvements
- Replace raw CSV parsing with a small CSV helper library if you expect complex fields.
- Add unit tests and a CI workflow (GitHub Actions) to build and run tests on push/PR.
- Add stronger password hashing (e.g., bcrypt/argon2) if this becomes more than a demo.

## Contributing

Feel free to open issues or PRs. Small improvements are welcome (README polish, bug fixes, tests, CI). If you plan to change CSV formats, please add a migration utility or clearly document the new format.

## License

This project is licensed under the terms in the `LICENSE` file.

---