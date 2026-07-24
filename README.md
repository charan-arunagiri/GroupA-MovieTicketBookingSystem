# Movie Ticket Booking System (CSC 1031)

An in-memory command-line interface (CLI) application built in C for managing movie showtimes, interactive seat maps, dynamic ticket pricing, cancellations, and real-time revenue analytics.

---

##  Team Contributions

| Team Member | Module / Role | Key Implementation |
| :--- | :--- | :--- |
| **Charan** | Core Lead & Base Engine | System Architecture, Base Structures, Menu Navigation, Showtimes View (`viewMoviesAndShowtimes`), Interactive Seat Map (`viewSeatMap`), Booking Logic (`bookATicket`), Price Calculation (`calculatePrice`). |
| **Priyanka** | Booking Management | Ticket Cancellation & Refund Logic (`cancelBooking`), Search & Lookup Engine (`searchBooking`), String Helper (`containsIgnoreCase`). |
| **Wageesha** | Financial Analytics | Cinema Financial Analytics Engine & Detailed Revenue Report Generator (`showRevenue`). |

---

##  Features

*  **Movie Schedule Management:** View available movies and their screening times.
*  **Interactive Seat Map:** Visual 5x10 grid display showing real-time seat availability across tiers.
*  **Dynamic Tier Pricing & Discounts:**
  * **Regular Tier (Rows A–B):** Base pricing for standard seats.
  * **Premium Tier (Rows C–D):** Middle seating tier.
  * **VIP Tier (Row E):** Top-tier seating.
  * **Discounts:** Student (10%), Senior Citizen (20%), Group Discount (10% off base price when booking 4+ seats).
*  **Booking Cancellation:** Release booked seats dynamically and auto-calculate refund amounts.
*  **Search Engine:** Search active reservations by customer name or seat number.
*  **Revenue Reporting:** Breakdown of total tickets sold, revenue by movie, and overall earnings.

---

##  Data Architecture

```text
Movie (3 Movies)
 └── Showtime (2 Showtimes per Movie)
      └── Seat (5 Rows x 10 Columns = 50 Seats per Showtime)
           ├── Booked Status (0 = Free, 1 = Booked)
           ├── Customer Name
           ├── Customer Category (Regular, Student, Senior)
           ├── Ticket Type String
           └── Price Paid (float)
```

---

##  How to Compile & Run

###  Compilation (All Platforms)
```bash
gcc main.c -o booking
```

###  Execution
* **Linux / macOS (Terminal):**
  ```bash
  ./booking
  ```
* **Windows (Command Prompt / PowerShell):**
  ```cmd
  booking.exe
  ```

---

## 📜 Course Info
* **Course:** CSC 1031 - Computer Science Assignment
* **Language:** C (Standard C Library)
