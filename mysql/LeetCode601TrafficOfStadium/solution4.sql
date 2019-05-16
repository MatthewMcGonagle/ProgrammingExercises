# Use inner joins to find connected components, but don't construct new tables. Just put the
# people >= 100 condition in the ON part of the inner joins.

# Runs faster than 75% of all successful submissions.

SELECT DISTINCT t4.Id, t4.visit_date, t4.people
FROM (
    SELECT t1.Id
    FROM
        stadium t1
    INNER JOIN
        stadium t2
    ON 
        t1.people >= 100 and t2.people >= 100 and t1.Id = t2.Id - 1
    INNER JOIN
        stadium t3
    ON
        t3.people >= 100 and t2.Id = t3.Id - 1
    ) as connected,
    stadium t4
WHERE t4.Id = connected.Id or t4.Id = connected.Id + 1 or t4.Id = connected.Id + 2
