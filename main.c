#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Movie movies[NUM_MOVIES];

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
