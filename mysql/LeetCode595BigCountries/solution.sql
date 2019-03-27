-- Leetcode for some reason won't accept code with separate 'SET' statements. So we
-- define user variables in the Select statement.

SELECT name, population, area FROM World
    WHERE population > (@min_population := 25 * POWER(10, 6))
       OR area > (@min_area := 3 * POWER(10, 6));
