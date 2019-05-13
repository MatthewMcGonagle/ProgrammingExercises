/* Exchange pairs of seats. If there is an odd number of students, then don't move the last seat.
*/

SELECT 
    (CASE
        WHEN MOD(id, 2) = 1 AND id != seat_count THEN id + 1 -- Odd and not the last. Do switch.
        WHEN MOD(id, 2) = 1 AND id = seat_count THEN id -- Odd and the last seat. Don't switch.
        ELSE id - 1 -- Always switch even seats.
    END) AS id,
    student
FROM
    seat,
    (SELECT
        COUNT(*) AS seat_count
    FROM seat) AS seat_counts -- Total count of all seats.
ORDER BY id ASC;
