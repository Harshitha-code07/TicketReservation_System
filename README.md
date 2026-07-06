# TicketReservation_System
A ticket reservation system with seat booking, cancellation, waiting list, and priority confirmation.

## Files
- `TicketReservation_System.cpp` — ticket reservation and waiting list program.
- `README.md` — this file.

## Prerequisites

- A C++ compiler such as g++, clang++, or MSVC.
- On Windows, install MinGW-w64, Visual Studio, or use the MSVC Developer Command Prompt.

## Compile

### Ticket Reservation System

Using g++:

```bash
g++ TicketReservation_System.cpp -o TicketReservation_System.exe
```

Using MSVC (Developer Command Prompt):

```bash
cl /EHsc TicketReservation_System.cpp
```

## Run

### Ticket Reservation System

On Windows (MinGW):

```bash
./TicketReservation_System.exe
```

With MSVC:

```bash
TicketReservation_System.exe
```

## Program Summaries

### Ticket Reservation System

- Books up to 5 confirmed seats initially.
- Places additional passengers on a waiting list.
- Automatically confirms up to 3 waiting passengers when the system reaches full capacity.
- Uses priority rules for disabled and senior passengers.
- Supports ticket cancellation and reassigns seats from the waiting list.

## Notes

- If compilation fails with header-related errors, ensure you are compiling as C++ and not plain C.
- For best results, use a modern C++ compiler that supports standard library headers like `<iostream>`, `<vector>`, and `<string>`.
- If you want to modify either program, keep source filenames consistent with the commands above.



