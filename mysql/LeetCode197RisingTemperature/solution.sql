# Find the Ids of the samples where the temperature is greater than the temperature of the day before.
# Table Weather:
#   Columns: Id (INT), RecordDate (DATE), Temperature (INT)

# We find the date for yesterday and then do an inner join where the today temperature is
# greater than yesterday's temperature.

# Solution not very fast. Only runs faster than 13% of all submissions.

SELECT Id
FROM (SELECT Id, Temperature, RecordDate - interval 1 day as YesterdayDate
      FROM Weather) as today
      INNER JOIN (SELECT Temperature, RecordDate
                  FROM WEATHER) as yesterday
      ON today.YesterdayDate = yesterday.RecordDate
      WHERE today.Temperature > yesterday.Temperature
