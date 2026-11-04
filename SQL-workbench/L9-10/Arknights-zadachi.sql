-- ЗАДАНИЯ ЛАБОРАТОРНОЙ РАБОТЫ №9-10
USE Arknights_Lore;

-- ЗАДАНИЕ 1: Ввести ограничения CHECK
ALTER TABLE Event 
ADD COLUMN casualties INT;
ALTER TABLE Event 
ADD CONSTRAINT Event_Casualties_Check 
CHECK (casualties >= 0);
ALTER TABLE Department 
ADD COLUMN budget INT;
ALTER TABLE Department 
ADD CONSTRAINT Department_Budget_Check 
CHECK (budget >= 0);


-- ЗАДАНИЕ 2: Проследить за изменением ограничений
SHOW CREATE TABLE Character_Department;
SHOW CREATE TABLE Relationship;
SHOW CREATE TABLE Event_Participant;

ALTER TABLE Character_Department DROP FOREIGN KEY character_department_ibfk_1;
ALTER TABLE Relationship DROP FOREIGN KEY relationship_ibfk_1;
ALTER TABLE Relationship DROP FOREIGN KEY relationship_ibfk_2;
ALTER TABLE Event_Participant DROP FOREIGN KEY event_participant_ibfk_2;

ALTER TABLE Character_Department 
ADD CONSTRAINT CharDept_Char_Foreign 
FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE;
ALTER TABLE Relationship 
ADD CONSTRAINT Relationship_Char1_Foreign 
FOREIGN KEY (character_1_id) REFERENCES Characters(character_id) ON DELETE CASCADE;
ALTER TABLE Relationship 
ADD CONSTRAINT Relationship_Char2_Foreign 
FOREIGN KEY (character_2_id) REFERENCES Characters(character_id) ON DELETE CASCADE;
ALTER TABLE Event_Participant 
ADD CONSTRAINT EventPart_Char_Foreign 
FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE;

-- ЗАДАНИЕ 3: Отключить ограничения и ввести некорректные данные
SET FOREIGN_KEY_CHECKS = 0;
INSERT INTO Character_Department (character_id, department_id, role_in_department, join_date) 
VALUES (1, 999, 'Test Role', '2020-01-01');
SET FOREIGN_KEY_CHECKS = 1;
DELETE FROM Character_Department WHERE department_id = 999;
SET FOREIGN_KEY_CHECKS = 1;

-- ЗАДАНИЕ 4: Добавить и удалить столбец
ALTER TABLE Characters 
ADD nickname VARCHAR(50) DEFAULT 'Unknown';
SELECT character_name, nickname FROM Characters LIMIT 5;
ALTER TABLE Characters 
DROP COLUMN nickname;

-- ЗАДАНИЕ 5: Изменить длины полей
ALTER TABLE Characters 
MODIFY COLUMN character_name VARCHAR(150);
DESCRIBE Characters;

-- ЗАДАНИЕ 6: Переименовать таблицу
RENAME TABLE Event_Participant TO Event_Attendance;
RENAME TABLE Event_Attendance TO Event_Participant;