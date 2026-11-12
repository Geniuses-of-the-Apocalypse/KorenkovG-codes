-- 1
CALL IncreaseDepartmentBudget(1, 10.00, 3);
SELECT department_name, budget FROM Department WHERE department_id = 1;

-- 2
SET @count = 0;
CALL CountCharacterEvents(1, @count);
SELECT @count AS 'Количество событий';