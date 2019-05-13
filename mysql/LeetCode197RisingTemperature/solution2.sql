# Find the Ids of the samples where the temperature is greater than the temperature of the day before.
# Table Weather:
#   Columns: Id (INT), RecordDate (DATE), Temperature (INT)

# We do an inner join when dates differ by 1; this way we aren't explictly computing a column of yesterday dates
# so we can save space and time.

# Solution is much faster. Runs faster than 90% of all submissions.

SELECT today.Id
FROM weather as today
    INNER JOIN weather as yesterday
    ON DATEDIFF(today.RecordDate, yesterday.RecordDate) = 1
    WHERE today.Temperature > yesterday.Temperature
