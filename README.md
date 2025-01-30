# movie-booking-web

This is a simple movie booking web application that allows users to book tickets for movies. The app provides a seat selection interface and displays the booking summary after the user completes the booking. It also tracks seat availability and shows booked seats dynamically.

## Features
- **Seat Selection**: Users can view available seats in a matrix layout and select their preferred seats.
- **Booking Summary**: After booking, users can view their seat selection and booking details.
- **Real-time Seat Availability**: The app dynamically shows which seats are already booked.

## Technologies Used
- **Node.js**: For backend server to handle requests.
- **Express.js**: Framework to set up the server and handle routing.
- **HTML, CSS, JavaScript**: For the frontend UI and functionality.
- **JSON**: To store the seat booking data (`seats.dat`).
- **GitHub**: For version control and hosting the codebase.

## How It Works
1. **Server**: The backend server (`server.js`) handles user requests, processes bookings, and stores booking data in a local file (`seats.dat`).
2. **Frontend**: The frontend (`public/index.html`, `public/style.css`, and `public/app.js`) displays the seat matrix and allows users to interact with the application.
3. **Seat Matrix**: The seat layout is displayed in a grid format, and users can select the seats they want to book. Booked seats are visually highlighted to indicate they are unavailable.
4. **Booking Process**: After selecting seats, users can submit the booking. The system updates the available seat matrix and displays a booking summary.

## How to Run
1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/swayam1238/movie-booking-web.git
   ```

2. Navigate to the project directory:
   ```bash
   cd movie-booking-web
   ```

3. Install the dependencies:
   ```bash
   npm install
   ```

4. Start the server:
   ```bash
   node server.js
   ```

5. Open your browser and visit `http://localhost:3000` to use the application.

## File Structure
- `server.js`: Backend server logic that handles bookings.
- `public/`:
  - `index.html`: Frontend HTML page displaying the seat selection and booking summary.
  - `style.css`: CSS styles for the seat layout and booking interface.
  - `app.js`: JavaScript to handle user interactions and seat bookings.
- `seats.dat`: A data file that stores booking information and seat status.

## Contributing
Feel free to fork the repository, make changes, and submit pull requests. Contributions are welcome!

## License
This project is open source and available under the [MIT License](LICENSE).
