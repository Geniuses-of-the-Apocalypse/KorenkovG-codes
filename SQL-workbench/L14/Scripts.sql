USE Arknights_Lore;

--
DELIMITER //
CREATE TRIGGER after_character_insert
AFTER INSERT ON Characters
FOR EACH ROW
BEGIN
    INSERT INTO Character_Department (character_id, department_id, role_in_department, join_date)
    VALUES (NEW.character_id, 1, 'Trainee', CURRENT_DATE);
END //
DELIMITER ;

INSERT INTO Characters (character_name, race_id, class_id, profession_id, status_id, current_location_id, birth_date)
VALUES ('Test_Trigger_1', 6, 1, 1, 1, 1, '2000-01-01');
SELECT * FROM Characters WHERE character_name = 'Test_Trigger_1';

SELECT cd.*, c.character_name 
FROM Character_Department cd
JOIN Characters c ON cd.character_id = c.character_id
WHERE c.character_name = 'Test_Trigger_1';
--

--
DELIMITER //
CREATE TRIGGER before_character_update
BEFORE UPDATE ON Characters
FOR EACH ROW
BEGIN
    IF NEW.status_id = 4 AND OLD.status_id != 4 THEN
        SET NEW.current_location_id = 4;
    END IF;
END //
DELIMITER ;

UPDATE Characters 
SET status_id = 1, current_location_id = 1 
WHERE character_name = 'W';

SELECT character_name, status_id, current_location_id 
FROM Characters 
WHERE character_name = 'W';

UPDATE Characters 
SET status_id = 4 
WHERE character_name = 'W';

SELECT character_name, status_id, current_location_id 
FROM Characters 
WHERE character_name = 'W';
--

-- SHOW TRIGGERS FROM Arknights_Lore;
-- DROP TRIGGER IF EXISTS after_character_insert;
-- DROP TRIGGER IF EXISTS before_character_update;
-- DELETE FROM Characters WHERE character_name = 'Test_Trigger_1';