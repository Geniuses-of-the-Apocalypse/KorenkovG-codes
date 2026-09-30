SELECT DISTINCT Sub.SUBJ_NAME AS "Subject", EM.MARK AS "Mark"
FROM exam_marks EM
JOIN subjects Sub ON EM.subjects_SUBJ_ID = Sub.SUBJ_ID
WHERE EM.MARK > ANY (
    SELECT MARK FROM exam_marks WHERE subjects_SUBJ_ID = 13
);

SELECT Sub.SUBJ_NAME AS "Subject", COUNT(*) AS "Amount of marks"
FROM exam_marks EM
JOIN subjects Sub ON EM.subjects_SUBJ_ID = Sub.SUBJ_ID
GROUP BY Sub.SUBJ_NAME
HAVING COUNT(*) < (
    SELECT MAX(cnt) FROM (
        SELECT COUNT(*) AS cnt 
        FROM exam_marks 
        GROUP BY subjects_SUBJ_ID
    ) AS t
);

SELECT U1.UNIV_NAME AS "University 1", 
       U2.UNIV_NAME AS "University 2", 
       U1.CITY AS "City"
FROM university U1
JOIN university U2 
  ON U1.CITY = U2.CITY 
 AND U1.UNIV_ID < U2.UNIV_ID
ORDER BY U1.CITY;

SELECT S.NAME AS "Name", S.STUDENT_ID AS "ID", S.CITY AS "City", S.STIPEND AS "Stipend"
FROM student S
WHERE S.STIPEND = (
    SELECT MAX(S2.STIPEND)
    FROM student S2
    WHERE S2.CITY = S.CITY
);

SELECT S.NAME AS "Name", S.STUDENT_ID AS "ID", S.CITY AS "City"
FROM student S
WHERE NOT EXISTS (
    SELECT 1 FROM university U WHERE U.CITY = S.CITY
);