CREATE DATABASE IF NOT EXISTS Arknights_Lore;
USE Arknights_Lore;

-- 1. Таблица Локаций (Location)
CREATE TABLE Location (
    location_id INT AUTO_INCREMENT PRIMARY KEY,
    location_name VARCHAR(100) NOT NULL UNIQUE, 
    region_type ENUM('Nation', 'City', 'Ruins', 'Island', 'Mobile_City') NOT NULL,
    description TEXT
);

-- 2. Таблица Рас (Race)
CREATE TABLE Race (
    race_id INT AUTO_INCREMENT PRIMARY KEY,
    race_name VARCHAR(50) NOT NULL UNIQUE,
    origin_region VARCHAR(100)
);

-- 3. Таблица Классов (Class)
CREATE TABLE Class (
    class_id INT AUTO_INCREMENT PRIMARY KEY,
    class_name VARCHAR(50) NOT NULL UNIQUE, 
    combat_type ENUM('Melee', 'Ranged', 'Support') NOT NULL
);

-- 4. Таблица Родов деятельности (Profession)
CREATE TABLE Profession (
    profession_id INT AUTO_INCREMENT PRIMARY KEY,
    profession_name VARCHAR(50) NOT NULL UNIQUE, 
    description TEXT
);

-- 5. Таблица Статусов (Status)
CREATE TABLE Status (
    status_id INT AUTO_INCREMENT PRIMARY KEY,
    status_name VARCHAR(50) NOT NULL UNIQUE,
    description TEXT
);

-- 6. Таблица Отделов/Фракций (Department)
CREATE TABLE Department (
    department_id INT AUTO_INCREMENT PRIMARY KEY,
    department_name VARCHAR(100) NOT NULL UNIQUE, 
    description TEXT,
    location_id INT,
    is_active BOOLEAN DEFAULT TRUE,
    FOREIGN KEY (location_id) REFERENCES Location(location_id) ON DELETE SET NULL
);

-- 7. Таблица Персонажей (Characters)
CREATE TABLE Characters (
    character_id INT AUTO_INCREMENT PRIMARY KEY,
    character_name VARCHAR(100) NOT NULL,
    race_id INT NOT NULL,
    class_id INT,
    profession_id INT NOT NULL,
    status_id INT NOT NULL,
    current_location_id INT,
    birth_date DATE,
    
    FOREIGN KEY (race_id) REFERENCES Race(race_id) ON DELETE RESTRICT,
    FOREIGN KEY (class_id) REFERENCES Class(class_id) ON DELETE SET NULL,
    FOREIGN KEY (profession_id) REFERENCES Profession(profession_id) ON DELETE RESTRICT,
    FOREIGN KEY (status_id) REFERENCES Status(status_id) ON DELETE RESTRICT,
    FOREIGN KEY (current_location_id) REFERENCES Location(location_id) ON DELETE SET NULL
);

-- 8. Связующая таблица: История принадлежности к Отделам
CREATE TABLE Character_Department (
    character_id INT NOT NULL,
    department_id INT NOT NULL,
    role_in_department VARCHAR(100),
    join_date DATE NOT NULL,
    leave_date DATE,
    PRIMARY KEY (character_id, department_id, join_date),
    CHECK (leave_date IS NULL OR leave_date >= join_date),
    FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE,
    FOREIGN KEY (department_id) REFERENCES Department(department_id) ON DELETE CASCADE
);

-- 9. Таблица Отношений между персонажами
CREATE TABLE Relationship (
    relationship_id INT AUTO_INCREMENT PRIMARY KEY,
    character_1_id INT NOT NULL,
    character_2_id INT NOT NULL,
    relation_type ENUM('Friend', 'Enemy', 'Family', 'Mentor', 'Rival', 'Colleague') NOT NULL,
    description TEXT,
    FOREIGN KEY (character_1_id) REFERENCES Characters(character_id) ON DELETE CASCADE,
    FOREIGN KEY (character_2_id) REFERENCES Characters(character_id) ON DELETE CASCADE
);

-- 10. Таблица Событий (Event)
CREATE TABLE Event (
    event_id INT AUTO_INCREMENT PRIMARY KEY,
    event_name VARCHAR(150) NOT NULL, 
    location_id INT,
    start_date DATE NOT NULL,
    end_date DATE,
    description TEXT,
    CHECK (end_date IS NULL OR end_date >= start_date),
    FOREIGN KEY (location_id) REFERENCES Location(location_id) ON DELETE SET NULL
);

-- 11. Связующая таблица: Участники событий
CREATE TABLE Event_Participant (
    event_id INT NOT NULL,
    character_id INT NOT NULL,
    department_id INT,
    role_in_event ENUM('Attacker', 'Defender', 'Observer', 'Victim', 'Organizer') NOT NULL,
    PRIMARY KEY (event_id, character_id),
    FOREIGN KEY (event_id) REFERENCES Event(event_id) ON DELETE CASCADE,
    FOREIGN KEY (character_id) REFERENCES Characters(character_id) ON DELETE CASCADE,
    FOREIGN KEY (department_id) REFERENCES Department(department_id) ON DELETE SET NULL
);