SELECT UNIV_NAME AS "University", CITY AS "City"
FROM university
WHERE RATING >= (
    SELECT RATING 
    FROM university 
    WHERE UNIV_NAME = 'MGU'
);

SELECT S.NAME AS "Name", S.SURNAME AS "Surname"
FROM student S
JOIN exam_marks EM ON S.STUDENT_ID = EM.student_STUDENT_ID
WHERE EM.subjects_SUBJ_ID = 13
  AND EM.MARK > (
      SELECT AVG(MARK) 
      FROM exam_marks
  );
  
SELECT S.NAME AS "Name", S.SURNAME AS "Surname"
FROM student S
JOIN exam_marks EM ON S.STUDENT_ID = EM.student_STUDENT_ID
WHERE EM.subjects_SUBJ_ID = 13
  AND EM.MARK < (
      SELECT AVG(MARK) 
      FROM exam_marks
  );
  
SELECT S.STUDENT_ID AS "ID", S.NAME AS "Name", S.SURNAME AS "Surname",
COUNT(DISTINCT EM.subjects_SUBJ_ID) AS "Amount of subjects"
FROM student S
JOIN exam_marks EM ON S.STUDENT_ID = EM.student_STUDENT_ID
GROUP BY S.STUDENT_ID, S.NAME, S.SURNAME
HAVING COUNT(DISTINCT EM.subjects_SUBJ_ID) > 0;
------------------------------------------------
SELECT S.NAME AS "Name", S.STUDENT_ID AS "ID"
FROM student S
JOIN university U ON S.university_UNIV_ID = U.UNIV_ID
WHERE S.CITY <> U.CITY;
-----------------------------------------------
SELECT S.NAME AS "Name", S.STUDENT_ID AS "ID"
FROM student S
WHERE S.CITY <> (
    SELECT U.CITY
    FROM university U
    WHERE U.UNIV_ID = S.university_UNIV_ID
);

SELECT DISTINCT S.STUDENT_ID AS "ID", S.NAME AS "Name", S.SURNAME AS "Surname"
FROM student S
JOIN exam_marks EM ON S.STUDENT_ID = EM.student_STUDENT_ID
WHERE EM.MARK < 4
  AND S.STUDENT_ID IN (
      SELECT student_STUDENT_ID
      FROM exam_marks
      GROUP BY student_STUDENT_ID
      HAVING AVG(MARK) > 2
  );
  
SELECT S.NAME AS "Name", S.STUDENT_ID AS "ID", S.CITY AS "City", S.STIPEND AS "Stipend"
FROM student S
WHERE S.STIPEND = (
    SELECT MAX(S2.STIPEND)
    FROM student S2
    WHERE S2.CITY = S.CITY
);

SELECT S.STUDENT_ID AS "ID", S.NAME AS "Name", S.SURNAME AS "Surname", S.CITY AS "City"
FROM student S
WHERE EXISTS (
    SELECT 1
    FROM university U
    WHERE U.CITY = S.CITY
      AND U.UNIV_ID <> S.university_UNIV_ID
);

SELECT S.SURNAME AS "Surname", Sub.SUBJ_NAME AS "Subject"
FROM student S
JOIN exam_marks EM ON S.STUDENT_ID = EM.student_STUDENT_ID
JOIN subjects Sub ON EM.subjects_SUBJ_ID = Sub.SUBJ_ID;

SELECT S.SURNAME AS "Surname", Sub.SUBJ_NAME AS "Subject"
FROM student S
JOIN exam_marks EM ON S.STUDENT_ID = EM.student_STUDENT_ID
JOIN subjects Sub ON EM.subjects_SUBJ_ID = Sub.SUBJ_ID
WHERE EM.MARK IN (4, 5);

SELECT U.UNIV_NAME AS "University", MAX(S.STIPEND) AS "Max Stipend"
FROM university U
JOIN student S ON U.UNIV_ID = S.university_UNIV_ID
WHERE U.RATING > 30 AND U.RATING < 40
GROUP BY U.UNIV_NAME;