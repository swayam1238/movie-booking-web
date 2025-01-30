document.getElementById('bookingForm').addEventListener('submit', function(event) {
    event.preventDefault();

    const name = document.getElementById('name').value;
    const movie_num = document.getElementById('movie').value;
    const seats_booked = document.getElementById('seats').value;

    fetch('/book-seats', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ name, movie_num, seats_booked })
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('bookingSummary').classList.remove('hidden');
        document.getElementById('summaryName').textContent = `Name: ${data.name}`;
        document.getElementById('summaryMovie').textContent = `Movie Number: ${data.movie_num}`;
        document.getElementById('summarySeats').textContent = `Seats: ${data.booked_seats.join(', ')}`;
        document.getElementById('summaryCost').textContent = `Total Cost: ₹${data.total_cost.toFixed(2)}`;
    })
    .catch(error => {
        alert('Error: ' + error.message);
    });
});
