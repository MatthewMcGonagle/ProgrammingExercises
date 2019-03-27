-- Get movies with 
--    - odd numbered id
--    - description != boring
-- Order descending by rating.
SELECT * FROM cinema
    WHERE MOD(id, 2) = 1 AND
          description <> "boring"
    ORDER BY rating DESC;
