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
int parseSeat(const char* seatStr, int *row, int *col);
void viewMoviesAndShowtimes();
void viewSeatMap();

// Stubs for upcoming steps
void bookATicket() { printf("\n[Book Ticket module coming next!]\n"); }
void cancelBooking() { printf("\n[Cancel Booking module coming soon!]\n"); }
void searchBooking() { printf("\n[Search Booking module coming soon!]\n"); }
void showRevenue() { printf("\n[Revenue Report module coming soon!]\n"); }

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
        if (!isdigit(seatStr[i])) {
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
