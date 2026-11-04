USE Arknights_Lore;

#1 commit
--
START TRANSACTION;

UPDATE Characters SET status_id = 4 WHERE character_id = 5;
UPDATE Characters SET current_location_id = 4 WHERE character_id = 5;
ROLLBACK;
COMMIT;
--
SELECT character_name, status_id, current_location_id FROM Characters WHERE character_name = 'W';

--
START TRANSACTION;
UPDATE Characters SET status_id = 4 WHERE character_id = 5;
UPDATE Characters SET current_location_id = 4 WHERE character_id = 5;
COMMIT;
--
SELECT character_name, status_id, current_location_id FROM Characters WHERE character_name = 'W';

#2 rollback
--
START TRANSACTION;
INSERT INTO Characters (character_name, race_id, profession_id, status_id, birth_date)
VALUES ('Liskarm', 2, 1, 1, '1994-08-12');
SAVEPOINT sp_liskarm_added;
INSERT INTO Character_Department (character_id, department_id, role_in_department, join_date)
VALUES (LAST_INSERT_ID(), 1, 'Security Guard', '2019-05-01');
SAVEPOINT sp_dept_added;
ROLLBACK TO SAVEPOINT sp_dept_added;
COMMIT;
--
SELECT c.character_name, cd.department_id, cd.role_in_department 
FROM Characters c
LEFT JOIN Character_Department cd ON c.character_id = cd.character_id
WHERE c.character_name = 'Liskarm';