
USE Arknights_Lore;

ALTER TABLE Event ADD COLUMN casualties INT;
ALTER TABLE Department ADD COLUMN budget INT;

#1
INSERT INTO Characters (character_name, race_id, class_id, profession_id, status_id, current_location_id, birth_date)
VALUES ('Lappland', 3, 1, 1, 1, 1, '1997-04-10');

INSERT INTO Location (location_name, region_type, description)
VALUES 
('Siesta', 'City', 'Курортный город-государство'),
('Kjerag', 'Nation', 'Изолированная горная страна'),
('Higashi', 'Nation', 'Островное государство самураев');

INSERT IGNORE INTO Race (race_name, origin_region)
VALUES ('Feline', 'Lungmen'); 

#2
UPDATE Department 
SET budget = budget * 1.15 
WHERE department_name = 'Rhodes Island';


#3
DELETE FROM Relationship 
WHERE character_1_id = 5 AND relation_type = 'Enemy';

DELETE FROM Character_Department 
WHERE character_id = 4 
ORDER BY join_date ASC 
LIMIT 1;

#4
#TRUNCATE TABLE Relationship;