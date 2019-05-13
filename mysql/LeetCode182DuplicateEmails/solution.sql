# Select the emails that are listed more than once, i.e. are duplicate emails.

SELECT Email
FROM ( 
    SELECT Email, COUNT(Id) as count
    FROM Person
    GROUP BY Email
    ORDER BY Email 
    ) email_counts
WHERE count > 1
