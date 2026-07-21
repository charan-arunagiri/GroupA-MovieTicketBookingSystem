# Movie Ticket Booking System (CSC 1031)

## Overview
The Movie Ticket Booking System is an in-memory command-line interface (CLI) application built in C. It manages movie showtimes, seat reservations, pricing tiers, and revenue tracking across dynamic seating layouts.

## Features
- **Movie Schedule Management:** Displays movies and associated showtimes.
- **Interactive Seat Map:** Displays real-time 5x10 grid seat availability.
- **Dynamic Tier Pricing:**
  - Regular Tier (Rows A–B): Rs. 500
  - Premium Tier (Rows C–D): Rs. 750
  - VIP Tier (Row E): Rs. 1000
- **Automated Discounts:**
  - Student Discount: 10%
  - Senior Citizen Discount: 20%
  - Group Discount: 10% off base price when booking 4 or more seats.
- **Booking & Cancellation:** Reserves and releases seat coordinates dynamically.
- **Search System:** Search active reservations by customer name or seat number.
- **Revenue Reporting:** Summarizes tickets sold and total earnings.

## How to Compile & Run
```bash
gcc main.c -o booking
./booking
```
