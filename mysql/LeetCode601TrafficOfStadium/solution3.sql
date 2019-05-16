# BEST SOLUTION IS solution4.sql. See other solution.

# Runs faster than 55% of all successful submissions.

SELECT DISTINCT stadium.Id, stadium.visit_date, stadium.people
FROM (
    SELECT large_people.Id
    FROM
        (
        SELECT Id
        FROM stadium
        WHERE people >= 100
        ) as large_people
    INNER JOIN
        stadium t1
    ON large_people.Id = t1.Id - 1 and t1.people >= 100 # Picks out starts of consecutive pairs.
    INNER JOIN
        stadium t2
    ON large_people.Id = t2.Id - 2 and t2.people >= 100 # Picks out starts of triples.
    ) as t3, stadium
WHERE
    stadium.Id = t3.Id or stadium.Id = t3.Id + 1 or stadium.Id = t3.Id + 2
