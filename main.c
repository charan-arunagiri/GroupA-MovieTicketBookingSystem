#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define NUM_MOVIES 3
#define NUM_SHOWTIMES 2
#define NUM_ROWS 5
#define NUM_COLS 10

// --- Data Structures ---
struct Seat {
    int booked;            // 0 = Free, 1 = Booked
    int customerType;      // 1 = Regular, 2 = Student, 3 = Senior
    char customerName[50];
    char bookingType[30];
    float pricePaid;
};

struct Showtime {
    char time[50];
    struct Seat seats[NUM_ROWS][NUM_COLS];
};

struct Movie {
    char title[50];
    struct Showtime showtimes[NUM_SHOWTIMES];
};

// Global Data
struct Movie movies[NUM_MOVIES];

// --- Function Prototypes ---
void displayMenu();
void initializeSystem();
int readInteger();
void readString(char *buffer, int size);
int parseSeat(const char* seatStr, int *row, int *col);
float calculatePrice(int row, int category, int numSeats);
int containsIgnoreCase(const char *haystack, const char *needle);

void viewMoviesAndShowtimes();
void viewSeatMap();
void bookATicket();
void cancelBooking();
void searchBooking();

// Stub for Wageesha's upcoming Revenue module
void showRevenue() { printf("\n[Revenue Report module coming next!]\n"); }

// --- Main Function ---
int main() {
    initializeSystem();

    int choice = 0;
    while (choice != 7) {
        displayMenu();
        choice = readInteger();

        switch (choice) {
            case 1:
                viewMoviesAndShowtimes();
                break;
            case 2:
                viewSeatMap();
                break;
            case 3:
                bookATicket();
                break;
            case 4:
                cancelBooking();
                break;
            case 5:
                searchBooking();
                break;
            case 6:
                showRevenue();
                break;
            case 7:
                printf("\nThank you for using Movie Ticket Booking System! Goodbye.\n");
                break;
            default:
                printf("Error: Invalid option. Please select 1-7 from the menu.\n");
                break;
        }
    }

    return 0;
}

// --- Menu Display ---
void displayMenu() {
    printf("\n");
    printf("=========================================\n");
    printf("        MOVIE TICKET BOOKING SYSTEM       \n");
    printf("=========================================\n");
    printf("1. View Showtimes\n");
    printf("2. View Seat Map\n");
    printf("3. Book a Seat\n");
    printf("4. Cancel Booking\n");
    printf("5. Search Booking\n");
    printf("6. Revenue Report\n");
    printf("7. Exit\n");
    printf("=========================================\n");
    printf("Enter your choice (1-7): ");
}

// --- Helper Functions ---
int readInteger() {
    int val;
    while (scanf("%d", &val) != 1) {
        while (getchar() != '\n'); // Clear invalid input
        printf("Invalid input. Enter a number: ");
    }
    while (getchar() != '\n'); // Clear newline
    return val;
}

void readString(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Strip trailing newline
}

int containsIgnoreCase(const char *haystack, const char *needle) {
    if (!*needle) return 1;
    for (; *haystack; ++haystack) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h = haystack + 1;
            const char *n = needle + 1;
            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                h++;
                n++;
            }
            if (!*n) return 1;
        }
    }
    return 0;
}

// --- System Initialization ---
void initializeSystem() {
    strcpy(movies[0].title, "Inception");
    strcpy(movies[0].showtimes[0].time, "10:00 AM");
    strcpy(movies[0].showtimes[1].time, "3:00 PM");

    strcpy(movies[1].title, "Interstellar");
    strcpy(movies[1].showtimes[0].time, "11:00 AM");
    strcpy(movies[1].showtimes[1].time, "6:00 PM");

    strcpy(movies[2].title, "The Dark Knight");
    strcpy(movies[2].showtimes[0].time, "1:00 PM");
    strcpy(movies[2].showtimes[1].time, "8:00 PM");

    for (int m = 0; m < NUM_MOVIES; m++) {
        for (int s = 0; s < NUM_SHOWTIMES; s++) {
            for (int r = 0; r < NUM_ROWS; r++) {
                for (int c = 0; c < NUM_COLS; c++) {
                    movies[m].showtimes[s].seats[r][c].booked = 0;
                    strcpy(movies[m].showtimes[s].seats[r][c].customerName, "");
                    movies[m].showtimes[s].seats[r][c].pricePaid = 0.0f;
                    movies[m].showtimes[s].seats[r][c].customerType = 0;
                    strcpy(movies[m].showtimes[s].seats[r][c].bookingType, "");
                }
            }
        }
    }
}

// --- Seat Parsing ---
int parseSeat(const char* seatStr, int *row, int *col) {
    if (strlen(seatStr) < 2 || strlen(seatStr) > 3) {
        return 0;
    }

    char rowLetter = seatStr[0];
    if (rowLetter >= 'a' && rowLetter <= 'e') {
        rowLetter = rowLetter - 'a' + 'A';
    }

    if (rowLetter < 'A' || rowLetter > 'E') {
        return 0;
    }

    for (int i = 1; seatStr[i] != '\0'; i++) {
        if (!isdigit((unsigned char)seatStr[i])) {
            return 0;
        }
    }

    int seatNumber = atoi(seatStr + 1);
    if (seatNumber < 1 || seatNumber > 10) {
        return 0;
    }

    *row = rowLetter - 'A';
    *col = seatNumber - 1;
    return 1;
}

// --- Dynamic Price Calculator ---
float calculatePrice(int row, int category, int numSeats) {
    float basePrice = 1000.0f;

    if (row == 4) basePrice = 1800.0f;       // VIP (Row E)
    else if (row >= 2) basePrice = 1400.0f;  // Premium (Rows C, D)
    else basePrice = 1000.0f;               // Regular (Rows A, B)

    float discountPercent = 0.0f;
    if (category == 2) discountPercent += 0.10f;      // Student 10%
    else if (category == 3) discountPercent += 0.20f; // Senior Citizen 20%

    if (numSeats >= 4) discountPercent += 0.10f;      // Group Discount 10%

    return basePrice * (1.0f - discountPercent);
}

// --- View Option 1: Movie Catalog ---
void viewMoviesAndShowtimes() {
    printf("\n=============================================\n");
    printf("           AVAILABLE MOVIES & SHOWTIMES       \n");
    printf("=============================================\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("%d. %s\n", i + 1, movies[i].title);
        printf("   Showtimes: ");
        for (int j = 0; j < NUM_SHOWTIMES; j++) {
            printf("[%s] ", movies[i].showtimes[j].time);
        }
        printf("\n---------------------------------------------\n");
    }
}

// --- View Option 2: Interactive Seat Map ---
void viewSeatMap() {
    int movieChoice, showChoice;
    printf("\n--- Select Movie for Seat Map ---\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("%d. %s\n", i + 1, movies[i].title);
    }
    printf("Choose Movie (1-3): ");
    movieChoice = readInteger();

    if (movieChoice < 1 || movieChoice > 3) {
        printf("Error: Invalid movie selection.\n");
        return;
    }

    printf("\n--- Select Showtime ---\n");
    for (int j = 0; j < NUM_SHOWTIMES; j++) {
        printf("%d. %s\n", j + 1, movies[movieChoice - 1].showtimes[j].time);
    }
    printf("Choose Showtime (1-2): ");
    showChoice = readInteger();

    if (showChoice < 1 || showChoice > 2) {
        printf("Error: Invalid showtime selection.\n");
        return;
    }

    int mIdx = movieChoice - 1;
    int sIdx = showChoice - 1;

    printf("\n^^^^^^^^^^^^^^^^^^^^^^^^^^ SCREEN ^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    printf("                  ");
    for (int col = 0; col < NUM_COLS; col++) printf("%2d ", col + 1);
    printf("\n");

    for (int r = 0; r < NUM_ROWS; r++) {
        char rowLetter = 'A' + r;
        if (rowLetter == 'E') printf("[VIP]     Row %c: ", rowLetter);
        else if (rowLetter == 'C' || rowLetter == 'D') printf("[PREMIUM] Row %c: ", rowLetter);
        else printf("[REGULAR] Row %c: ", rowLetter);

        for (int c = 0; c < NUM_COLS; c++) {
            if (movies[mIdx].showtimes[sIdx].seats[r][c].booked) {
                printf(" [X]");
            } else {
                printf(" [.]");
            }
        }
        printf("\n");
    }
    printf("\n============================================================\n");
    printf(" LEGEND: [.] = Free | [X] = Booked\n");
    printf("============================================================\n");
}

// --- Menu Option 3: Book a Ticket ---
void bookATicket() {
    int movieChoice, showChoice, category, numSeats;
    char custName[50];

    printf("\n--- Select Movie ---\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("%d. %s\n", i + 1, movies[i].title);
    }
    printf("Choose Movie (1-3): ");
    movieChoice = readInteger();
    if (movieChoice < 1 || movieChoice > 3) {
        printf("Error: Invalid movie choice.\n");
        return;
    }

    printf("\n--- Select Showtime ---\n");
    for (int j = 0; j < NUM_SHOWTIMES; j++) {
        printf("%d. %s\n", j + 1, movies[movieChoice - 1].showtimes[j].time);
    }
    printf("Choose Showtime (1-2): ");
    showChoice = readInteger();
    if (showChoice < 1 || showChoice > 2) {
        printf("Error: Invalid showtime choice.\n");
        return;
    }

    int mIdx = movieChoice - 1;
    int sIdx = showChoice - 1;

    printf("\nEnter Customer Name: ");
    readString(custName, 50);

    printf("\n--- Choose Customer Category ---\n");
    printf("1. Regular\n");
    printf("2. Student (10%% Discount)\n");
    printf("3. Senior Citizen (20%% Discount)\n");
    printf("Choose Category (1-3): ");
    category = readInteger();
    if (category < 1 || category > 3) {
        printf("Error: Invalid category. Defaulting to Regular.\n");
        category = 1;
    }

    printf("\nEnter number of seats to book: ");
    numSeats = readInteger();
    if (numSeats < 1) {
        printf("Error: You must book at least 1 seat.\n");
        return;
    }

    int availableSeats = 0;
    for (int r = 0; r < NUM_ROWS; r++) {
        for (int c = 0; c < NUM_COLS; c++) {
            if (!movies[mIdx].showtimes[sIdx].seats[r][c].booked) {
                availableSeats++;
            }
        }
    }

    if (numSeats > availableSeats) {
        printf("Error: Only %d seats are left in this show.\n", availableSeats);
        return;
    }

    int selectedRows[50];
    int selectedCols[50];
    char seatInput[10];

    printf("\n--- Seat Selection ---\n");
    printf("(10%% extra discount applies for Group bookings of 4 or more tickets!)\n");

    for (int i = 0; i < numSeats; i++) {
        int validSeat = 0;
        int row = -1, col = -1;

        while (!validSeat) {
            printf("Enter Seat Code for ticket #%d (e.g. A3, E10): ", i + 1);
            readString(seatInput, 10);

            if (!parseSeat(seatInput, &row, &col)) {
                printf("Error: Invalid seat code. Please use A-E for row and 1-10 for column.\n");
                continue;
            }

            if (movies[mIdx].showtimes[sIdx].seats[row][col].booked) {
                printf("Error: Seat %s has already been ticketed. Choose another seat.\n", seatInput);
                continue;
            }

            int repeated = 0;
            for (int k = 0; k < i; k++) {
                if (selectedRows[k] == row && selectedCols[k] == col) {
                    repeated = 1;
                    break;
                }
            }
            if (repeated) {
                printf("Error: You already entered seat %s in this transaction!\n", seatInput);
                continue;
            }

            selectedRows[i] = row;
            selectedCols[i] = col;
            validSeat = 1;
        }
    }

    char discountStr[30];
    if (category == 2) {
        strcpy(discountStr, numSeats >= 4 ? "Student (Group)" : "Student");
    } else if (category == 3) {
        strcpy(discountStr, numSeats >= 4 ? "Senior Citizen (Group)" : "Senior Citizen");
    } else {
        strcpy(discountStr, numSeats >= 4 ? "Regular (Group)" : "Regular");
    }

    float transactionTotal = 0.0f;
    printf("\n============================================\n");
    printf("               BOOKING SUMMARY              \n");
    printf("============================================\n");
    printf("Customer Name: %s\n", custName);
    printf("Movie:         %s\n", movies[mIdx].title);
    printf("Showtime:      %s\n", movies[mIdx].showtimes[sIdx].time);
    printf("Category:      %s\n", discountStr);
    printf("--------------------------------------------\n");

    for (int i = 0; i < numSeats; i++) {
        int r = selectedRows[i];
        int c = selectedCols[i];

        float finalPrice = calculatePrice(r, category, numSeats);

        movies[mIdx].showtimes[sIdx].seats[r][c].booked = 1;
        strcpy(movies[mIdx].showtimes[sIdx].seats[r][c].customerName, custName);
        movies[mIdx].showtimes[sIdx].seats[r][c].pricePaid = finalPrice;
        movies[mIdx].showtimes[sIdx].seats[r][c].customerType = category;
        strcpy(movies[mIdx].showtimes[sIdx].seats[r][c].bookingType, discountStr);

        printf("Seat %c%d: Rs. %.2f\n", 'A' + r, c + 1, finalPrice);
        transactionTotal += finalPrice;
    }

    printf("--------------------------------------------\n");
    printf("Total Cost:  Rs. %.2f\n", transactionTotal);
    printf("============================================\n");
    printf("Booking successful!\n");
}

// --- Menu Option 4: Cancel Booking ---
void cancelBooking() {
    int movieChoice, showChoice, row = -1, col = -1;
    char seatInput[10];

    printf("\n--- Select Movie for Cancellation ---\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("%d. %s\n", i + 1, movies[i].title);
    }
    printf("Choose Movie (1-3): ");
    movieChoice = readInteger();
    if (movieChoice < 1 || movieChoice > 3) {
        printf("Error: Invalid movie choice.\n");
        return;
    }

    printf("\n--- Select Showtime ---\n");
    for (int j = 0; j < NUM_SHOWTIMES; j++) {
        printf("%d. %s\n", j + 1, movies[movieChoice - 1].showtimes[j].time);
    }
    printf("Choose Showtime (1-2): ");
    showChoice = readInteger();
    if (showChoice < 1 || showChoice > 2) {
        printf("Error: Invalid showtime choice.\n");
        return;
    }

    int mIdx = movieChoice - 1;
    int sIdx = showChoice - 1;

    printf("\nEnter Seat Code to Cancel (e.g. A3, E10): ");
    readString(seatInput, 10);

    if (!parseSeat(seatInput, &row, &col)) {
        printf("Error: Invalid seat code format.\n");
        return;
    }

    if (!movies[mIdx].showtimes[sIdx].seats[row][col].booked) {
        printf("Notice: Seat %c%d is currently empty. Nothing to cancel.\n", 'A' + row, col + 1);
        return;
    }

    float refund = movies[mIdx].showtimes[sIdx].seats[row][col].pricePaid;
    char custName[50];
    strcpy(custName, movies[mIdx].showtimes[sIdx].seats[row][col].customerName);

    // Reset seat properties
    movies[mIdx].showtimes[sIdx].seats[row][col].booked = 0;
    strcpy(movies[mIdx].showtimes[sIdx].seats[row][col].customerName, "");
    movies[mIdx].showtimes[sIdx].seats[row][col].pricePaid = 0.0f;
    movies[mIdx].showtimes[sIdx].seats[row][col].customerType = 0;
    strcpy(movies[mIdx].showtimes[sIdx].seats[row][col].bookingType, "");

    printf("\n============================================\n");
    printf("            CANCELLATION CONFIRMED          \n");
    printf("============================================\n");
    printf("Customer Name: %s\n", custName);
    printf("Cancelled Seat:%c%d\n", 'A' + row, col + 1);
    printf("Refund Amount: Rs. %.2f\n", refund);
    printf("============================================\n");
}

// --- Menu Option 5: Search Booking ---
void searchBooking() {
    int searchChoice;
    printf("\n--- Search Reservation ---\n");
    printf("1. Search by Customer Name\n");
    printf("2. Search by Seat Code\n");
    printf("Choose Option (1-2): ");
    searchChoice = readInteger();

    if (searchChoice == 1) {
        char nameQuery[50];
        printf("\nEnter Customer Name (or part of name): ");
        readString(nameQuery, 50);

        int found = 0;
        printf("\n========================================================================\n");
        printf("                           SEARCH RESULTS                               \n");
        printf("========================================================================\n");

        for (int m = 0; m < NUM_MOVIES; m++) {
            for (int s = 0; s < NUM_SHOWTIMES; s++) {
                for (int r = 0; r < NUM_ROWS; r++) {
                    for (int c = 0; c < NUM_COLS; c++) {
                        if (movies[m].showtimes[s].seats[r][c].booked) {
                            if (containsIgnoreCase(movies[m].showtimes[s].seats[r][c].customerName, nameQuery)) {
                                printf("Customer: %-20s | Movie: %-15s | Time: %-8s | Seat: %c%-2d | Type: %s | Paid: Rs. %.2f\n",
                                       movies[m].showtimes[s].seats[r][c].customerName,
                                       movies[m].title,
                                       movies[m].showtimes[s].time,
                                       'A' + r, c + 1,
                                       movies[m].showtimes[s].seats[r][c].bookingType,
                                       movies[m].showtimes[s].seats[r][c].pricePaid);
                                found = 1;
                            }
                        }
                    }
                }
            }
        }
        if (!found) {
            printf("No active reservations found for query: '%s'\n", nameQuery);
        }
        printf("========================================================================\n");

    } else if (searchChoice == 2) {
        char seatInput[10];
        int row = -1, col = -1;
        printf("\nEnter Seat Code (e.g. A3, E10): ");
        readString(seatInput, 10);

        if (!parseSeat(seatInput, &row, &col)) {
            printf("Error: Invalid seat code format.\n");
            return;
        }

        int found = 0;
        printf("\n========================================================================\n");
        printf("                     SEAT STATUS FOR %c%d                                \n", 'A' + row, col + 1);
        printf("========================================================================\n");

        for (int m = 0; m < NUM_MOVIES; m++) {
            for (int s = 0; s < NUM_SHOWTIMES; s++) {
                if (movies[m].showtimes[s].seats[row][col].booked) {
                    printf("Movie: %-15s | Time: %-8s | Booked by: %-18s | Type: %s | Paid: Rs. %.2f\n",
                           movies[m].title,
                           movies[m].showtimes[s].time,
                           movies[m].showtimes[s].seats[row][col].customerName,
                           movies[m].showtimes[s].seats[row][col].bookingType,
                           movies[m].showtimes[s].seats[row][col].pricePaid);
                    found = 1;
                } else {
                    printf("Movie: %-15s | Time: %-8s | Status: [AVAILABLE]\n",
                           movies[m].title,
                           movies[m].showtimes[s].time);
                }
            }
        }
        printf("========================================================================\n");
    } else {
        printf("Error: Invalid choice.\n");
    }
}
