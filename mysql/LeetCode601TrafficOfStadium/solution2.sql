# BEST SOLUTION IS solution4.sql. See other solution.

# Runs faster than 57% of all accepted solutions.

SELECT DISTINCT stadium.Id, stadium.visit_date, stadium.people
FROM
    (
    SELECT t1.Id
    FROM
        (SELECT stadium.Id
        FROM stadium
         WHERE people >= 100) as t1
    INNER JOIN
        (SELECT stadium.Id
        FROM stadium 
        WHERE people >= 100) as t2
    ON 
        t1.Id = t2.Id - 1
    INNER JOIN
        (SELECT stadium.Id
         FROM stadium
        WHERE people >= 100) as t3
    ON
        t1.Id = t3.Id - 2
    ) as t4, stadium
WHERE stadium.Id = t4.Id or stadium.Id = t4.Id + 1 or stadium.Id = t4.Id + 2
     
