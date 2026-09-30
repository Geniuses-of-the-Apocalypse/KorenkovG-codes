SELECT COUNT(*) AS "Amount of students"
FROM Student;

SELECT Subject AS "Subject", COUNT(*) AS "Amount of marks"
FROM Matks
GROUP BY Subject;

SELECT Subject AS "Subject", ROUND(AVG(Mark), 2) AS "GPA"
FROM Matks
GROUP BY Subject;

SELECT MAX(Mark) AS "Max point"
FROM Matks;

SELECT COUNT(*) AS "Student with 1 or more 'A' "
FROM Student
WHERE (LENGTH(Surname) - LENGTH(REPLACE(Surname, 'a', ''))) >= 1;