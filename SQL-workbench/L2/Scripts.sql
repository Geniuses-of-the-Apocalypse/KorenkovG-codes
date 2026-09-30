USE phpmyadmin;

SELECT * FROM Student;

SELECT Surname, Tel FROM Student;

SELECT * FROM Student WHERE Tel IS NULL;

SELECT S.Surname, M.Subject, M.Mark
FROM Student S
JOIN Matks M ON S.idStudent = M.Student_idStudent;

SELECT S.Surname, S.Name
FROM Student S
JOIN Matks M ON S.idStudent = M.Student_idStudent
WHERE M.Subject = 'Math' AND M.Mark = 3;

SELECT CONCAT(Surname, ' ', LEFT(Name, 1)) AS Info
FROM Student
WHERE Surname LIKE 'K%';

SELECT Surname, Tel
FROM Student
WHERE Tel REGEXP '^[2-57]+$';

SELECT Surname
FROM Student
WHERE Address LIKE '%dikovo%' OR Address LIKE '%kizminki%';

SELECT * FROM Student
WHERE Surname IN ('Drag');

SELECT Surname FROM Student
WHERE Surname BETWEEN 'Kro' AND 'Uvar'
ORDER BY Surname;

SELECT DISTINCT S.Surname
FROM Student S
JOIN Matks M ON S.idStudent = M.Student_idStudent
WHERE M.Subject = 'Math' AND M.Mark >= 3;

SELECT DISTINCT Mark AS "5-points", (Mark * 20) AS "100-points"
FROM Matks;



