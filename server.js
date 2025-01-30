const express = require("express");
const path = require("path");
const app = express();
const bodyParser = require('body-parser');

// Middleware to parse form data
app.use(bodyParser.urlencoded({ extended: false }));

// Serve static files (e.g., HTML, CSS, JS) from the "public" directory
app.use(express.static(path.join(__dirname, 'public')));

// Movie price details (similar to your C code)
const moviePrices = {
    "1": { name: "KGF 2", time: "1:00 PM", price: [350, 250, 180] },
    "2": { name: "Bahubali: The Conclusion", time: "5:00 PM", price: [350, 250, 180] },
    "3": { name: "Avatar: The Way of Water", time: "8:00 PM", price: [350, 250, 180] },
};

// Function to calculate the ticket price based on row
const getTicketPrice = (row) => {
    if (row === 1) return 350;
    if (row === 2 || row === 3) return 250;
    return 180;
};

// Display the booking page
app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Handle the form submission and book the seats
app.post("/book", (req, res) => {
    const { name, movie_num, seats } = req.body;
    const movie = moviePrices[movie_num];

    // Process the seat input (e.g., "2B, 3C" to ["2B", "3C"])
    const seatList = seats.split(",").map(seat => seat.trim());

    // Calculate total cost
    let totalCost = 0;
    let bookedSeats = [];
    seatList.forEach(seat => {
        const row = parseInt(seat[0]);  // First character is the row number
        const col = seat[1]; // The second character is the column (e.g., B, C, etc.)

        // Validate row and column
        if (row >= 1 && row <= 5 && col >= 'A' && col <= 'J') {
            bookedSeats.push(seat);
            totalCost += getTicketPrice(row); // Add ticket price based on row
        }
    });

    // Add GST and handling charges
    totalCost = totalCost + (0.18 * totalCost) + 15.00;

    // Generate booking summary
    const bookingSummary = `
        <h1>Booking Summary</h1>
        <p><strong>Customer Name:</strong> ${name}</p>
        <p><strong>Movie:</strong> ${movie.name} (${movie.time})</p>
        <p><strong>Seats Booked:</strong> ${seatList.join(", ")}</p>
        <p><strong>Total Cost:</strong> ₹${totalCost.toFixed(2)}</p>
    `;

    // Respond with the booking summary
    res.send(bookingSummary);
});

// Start the server
app.listen(3000, () => {
    console.log("Server running on http://localhost:3000");
});
