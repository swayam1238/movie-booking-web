#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROWS 5
#define NUM_COLS 10
#define FILENAME "seats.dat"

typedef struct {
    char name[100];
    int movie_num;
    int seats_booked;
    char booked_seats[50];  // Store seat numbers as a string (e.g., "2B, 3C")
    float total_cost;
} Customer;

// Global seating chart (default: all seats available)
bool seats[NUM_ROWS][NUM_COLS] = {0};

// Function to load seat bookings from file
void load_seating_chart() {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        fread(seats, sizeof(seats), 1, file);
        fclose(file);
    }
}

// Function to save seat bookings to file
void save_seating_chart() {
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(seats, sizeof(seats), 1, file);
        fclose(file);
    }
}

// Function to display the seating chart
void display_seating_chart() {
    printf("\n   A B C D E F G H I J\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < NUM_COLS; j++) {
            printf("%c ", seats[i][j] ? 'X' : '_');  // 'X' for booked, '_' for available
        }
        printf("\n");
    }
}

// Function to calculate ticket price based on row
float get_ticket_price(int row) {
    if (row == 1) return 350.00; // Premium seats
    if (row == 2 || row == 3) return 250.00; // Standard
    return 180.00; // Back rows
}

// Function to book seats
// Function to book seats
void book_seats(Customer *customer) {
    int num_seats;
    printf("How many seats would you like to book? ");
    scanf("%d", &num_seats);
    customer->seats_booked = num_seats;
    customer->booked_seats[0] = '\0';  // Clear previous seat list

    float total_cost = 0;

    for (int i = 0; i < num_seats; i++) {
        int row, col;
        char col_letter, seat_str[5];

        while (1) {
            display_seating_chart();
            
            printf("Enter row number (1-5) for seat %d: ", i + 1);
            scanf("%d", &row);
            row--; // Convert to zero-based index

            printf("Enter column letter (A-J) for seat %d: ", i + 1);
            scanf(" %c", &col_letter);  // Space before %c prevents newline issue
            col = col_letter - 'A'; // Convert 'A' to 0, 'B' to 1, ..., 'J' to 9

            // Validate input range
            if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS) {
                printf("Invalid seat selection. Please try again.\n");
                continue;
            }

            // Check if seat is already taken
            if (seats[row][col]) {
                printf("Sorry, that seat is already taken. Choose another.\n");
                continue; // Stay in loop until an available seat is chosen
            }

            // Book the seat
            seats[row][col] = true;
            total_cost += get_ticket_price(row + 1); // Use 1-based row for pricing

            // Store seat in booking summary (e.g., "2B, 3C")
            sprintf(seat_str, "%d%c, ", row + 1, col_letter);
            strcat(customer->booked_seats, seat_str);

            break; // Seat successfully booked, break the loop
        }

        // Update seating chart after each seat is booked
        display_seating_chart();
    }

    // Remove trailing comma and space from seat list
    int len = strlen(customer->booked_seats);
    if (len > 2) customer->booked_seats[len - 2] = '\0';

    // Calculate total with GST and handling charges
    customer->total_cost = total_cost + (0.18 * total_cost) + 15.00;
    save_seating_chart();
}

// Function to display booking summary
void print_booking_summary(Customer customer) {
    printf("\n========= BOOKING SUMMARY =========\n");
    printf("Customer Name: %s\n", customer.name);
    printf("Movie Number: %d\n", customer.movie_num);
    printf("Seats Booked: %d\n", customer.seats_booked);
    printf("Booked Seats: %s\n", customer.booked_seats);
    printf("Total Cost: ₹%.2f\n", customer.total_cost);
    printf("===================================\n");
}

int main() {
    Customer customer;
    load_seating_chart();

    printf("Movie options:\n");
    printf("1. KGF 2----------------------1:00 PM\n");
    printf("2. Bahubali: The Conclusion---5:00 PM\n");
    printf("3. Avatar: The Way of Water---8:00 PM\n");

    printf("Enter your name: ");
    scanf("%s", customer.name);

    printf("Enter the movie number (1-3): ");
    scanf("%d", &customer.movie_num);

    book_seats(&customer);
    print_booking_summary(customer);

    return 0;
}
