-- Swap the values in the 'sex' column to switch between 'm' and 'f'.
UPDATE salary
SET sex = 
    CASE 
        WHEN sex = 'm' THEN 'f'
        ELSE 'm'
    END;
