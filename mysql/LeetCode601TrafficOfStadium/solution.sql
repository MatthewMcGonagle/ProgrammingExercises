# BEST SOLUTION IS solution4.sql. See other solution.

# Find the information for the visit days that are part of a triple of consecutive
# days with more than 100 people visiting (inclusive).
# Table stadium:
#   Columns: id, visit_date, people  

# We start by finding consecutive pairs of dates with more than 100 people. Then we
# find those pairs with start matching end.
# Then we select distinct values from those occurring within 3 places of these triplet
# starts.

# The performance isn't terribly good: around faster than 30% of successful submissions.

SELECT DISTINCT t4.Id, t4.visit_date, t4.people
FROM (
    SELECT connected.start
    FROM 
        (SELECT t1.Id as start, t2.Id as end
         FROM stadium t1, stadium t2
         WHERE t1.people >= 100 and t2.people >= 100 and t1.Id = t2.Id - 1) as connected
         INNER JOIN
         stadium t3
         ON connected.end = t3.Id - 1
    WHERE t3.people >= 100) as triples
    INNER JOIN
    stadium t4
    ON t4.Id = triples.start or t4.Id = triples.start + 1 or t4.Id = triples.start + 2
