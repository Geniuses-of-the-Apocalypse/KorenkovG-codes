-- ПРИМЕРЫ ЛАБОРАТОРНОЙ РАБОТЫ №9-10


USE Arknights_Lore;

-- ==========================================
-- ПРИМЕР 1: Добавление ограничения CHECK
-- ==========================================
-- Задача: Ввести ограничение на столбец base_hp в таблице Characters, 
-- полагая, что значение этого атрибута должно превышать 100.

ALTER TABLE Characters 
ADD CONSTRAINT Characters_HP_Check 
CHECK (base_hp > 100);

-- Примечание: При попытке вставить персонажа с HP <= 100, 
-- система сгенерирует ошибку.

-- ==========================================
-- ПРИМЕР 2: Добавление FOREIGN KEY с ON DELETE CASCADE
-- ==========================================
-- Задача: Ввести ограничения FOREIGN KEY для таблицы Character_Department 
-- таким образом, чтобы при удалении из таблицы Characters записей о персонаже, 
-- были бы удалены и соответствующие записи из таблицы Character_Department.

ALTER TABLE Character_Department 
ADD CONSTRAINT CharDept_Char_Foreign 
FOREIGN KEY (character_id) 
REFERENCES Characters(character_id) 
ON DELETE CASCADE;

-- ==========================================
-- ПРИМЕР 3: Удаление ограничения
-- ==========================================
-- Задача: Удалить ограничение FOREIGN KEY CharDept_Char_Foreign 
-- на атрибуте character_id в таблице Character_Department.

-- Сначала выясним имя ограничения (если не знаем):
-- EXEC SP_HELP Character_Department; -- для SQL Server
-- В MySQL можно посмотреть через:
SHOW CREATE TABLE Character_Department;

-- Удаляем ограничение:
ALTER TABLE Character_Department 
DROP FOREIGN KEY CharDept_Char_Foreign;

-- ==========================================
-- ПРИМЕР 4: Добавление столбца
-- ==========================================
-- Задача: Добавить столбец join_year (год вступления в отдел) 
-- в таблицу Character_Department, задав тип данных INT.

ALTER TABLE Character_Department 
ADD join_year INT;

-- ==========================================
-- ПРИМЕР 5: Модификация столбца
-- ==========================================
-- Задача: Изменить тип столбца join_year с INT на YEAR.

ALTER TABLE Character_Department 
MODIFY COLUMN join_year YEAR;

-- ==========================================
-- ПРИМЕР 6: Удаление столбца
-- ==========================================
-- Задача: Удалить столбец join_year из таблицы Character_Department.

ALTER TABLE Character_Department 
DROP COLUMN join_year;

-- ==========================================
-- ПРИМЕР 7: Отключение и подключение ограничений
-- ==========================================
-- Задача: Отключить ограничения внешнего ключа в таблице Character_Department.

-- В MySQL синтаксис отличается от SQL Server:
-- Отключаем проверку внешних ключей:
SET FOREIGN_KEY_CHECKS = 0;

-- Теперь можно вставить данные, нарушающие целостность:
INSERT INTO Character_Department (character_id, department_id, role_in_department, join_date) 
VALUES (999, 1, 'Test', '2020-01-01'); -- character_id = 999 не существует

-- Подключаем проверку обратно:
SET FOREIGN_KEY_CHECKS = 1;

-- ==========================================
-- ПРИМЕР 8: Переименование таблицы
-- ==========================================
-- Задача: Переименовать таблицу Character_Department в Character_Dept_History.

RENAME TABLE Character_Department TO Character_Dept_History;

-- Переименовываем обратно:
RENAME TABLE Character_Dept_History TO Character_Department;