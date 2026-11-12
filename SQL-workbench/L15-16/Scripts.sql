USE Arknights_Lore;

DELIMITER //

CREATE PROCEDURE IncreaseDepartmentBudget(
    IN p_department_id INT,
    IN p_percent DECIMAL(5,2),
    IN p_min_operators INT
)
BEGIN -- проверка условий и обновление данных
    IF (
        SELECT COUNT(*) 
        FROM Character_Department cd
        JOIN Characters c ON cd.character_id = c.character_id
        WHERE cd.department_id = p_department_id 
        AND cd.leave_date IS NULL
        AND c.status_id = 1
    ) >= p_min_operators THEN
        
        UPDATE Department 
        SET budget = budget * (1 + p_percent / 100)
        WHERE department_id = p_department_id;
        
        SELECT 'Бюджет увеличен' AS Result;
    ELSE
        SELECT 'Недостаточно операторов' AS Result;
    END IF;
END //

DELIMITER ;

-- =======================================================

DELIMITER //

CREATE PROCEDURE CountCharacterEvents(
    IN p_character_id INT,
    OUT p_event_count INT
)
BEGIN     -- подсчёт записей
    SELECT COUNT(*) 
    INTO p_event_count
    FROM Event_Participant
    WHERE character_id = p_character_id;
END //

DELIMITER ;


-- SHOW PROCEDURE STATUS WHERE Db = 'Arknights_Lore';
-- SHOW PROCEDURE STATUS;
-- DROP PROCEDURE IF EXISTS IncreaseDepartmentBudget;
-- DROP PROCEDURE IF EXISTS CountCharacterEvents;