
USE Arknights_Lore;

INSERT INTO Location (location_name, region_type, description) VALUES
('Rhodes Island', 'Mobile_City', 'Мобильный город-корабль фармацевтической компании Rhodes Island'),
('Lungmen', 'City', 'Крупный торговый город-государство, контролируется императором Вэй'),
('Chernobog', 'Ruins', 'Разрушенный город-государство Ursus после инцидента с Катастрофой'),
('Kazdel', 'Ruins', 'Историческая родина Sarkaz, ныне разрушенная территория'),
('Ursus', 'Nation', 'Крупная империя на севере Терры, известна суровым климатом'),
('Columbia', 'Nation', 'Технологически развитая нация на западе Терры');

INSERT INTO Race (race_name, origin_region) VALUES
('Cautus', 'Ursus'),
('Feline', 'Lungmen'),
('Sarkaz', 'Kazdel'),
('Liberi', 'Columbia'),
('Vulpo', 'Ursus'),
('Human', 'Unknown');

INSERT INTO Class (class_name, combat_type) VALUES
('Guard', 'Melee'),
('Caster', 'Ranged'),
('Medic', 'Support'),
('Defender', 'Melee'),
('Sniper', 'Ranged'),
('Vanguard', 'Melee'),
('Supporter', 'Ranged'),
('Specialist', 'Melee');

INSERT INTO Profession (profession_name, description) VALUES
('Operator', 'Боевой оператор, выполняющий миссии для Rhodes Island'),
('Leader', 'Руководитель организации или подразделения'),
('Researcher', 'Учёный, занимающийся исследованием Originium и Oripathy'),
('Mercenary', 'Наёмник, работающий за деньги'),
('Civilian', 'Гражданское лицо, не участвующее в боевых действиях');


INSERT INTO Status (status_name, description) VALUES
('Active', 'Активен, выполняет свои обязанности'),
('Deceased', 'Погиб или мёртв'),
('Missing', 'Пропал без вести'),
('Traitor', 'Предатель, перешёл на сторону врага'),
('Comatose', 'В коме или бессознательном состоянии');

INSERT INTO Department (department_name, description, location_id, is_active) VALUES
('Rhodes Island', 'Фармацевтическая компания, борющаяся с Oripathy', 1, TRUE),
('Reunion Movement', 'Движение заражённых Oripathy, борющееся за их права', 3, FALSE),
('Lungmen Guard Department', 'Полиция города Lungmen', 2, TRUE),
('Penguin Logistics', 'Курьерская служба и логистическая компания', 2, TRUE),
('Ursus Student Group', 'Студенческая самоуправляемая группа из Ursus', 5, TRUE);

INSERT INTO Characters (character_name, race_id, class_id, profession_id, status_id, current_location_id, birth_date) VALUES
('Doctor', 6, NULL, 2, 5, 1, '1990-05-15'),
('Amiya', 1, 2, 2, 1, 1, '2002-11-20'),
('Kal''tsit', 3, 3, 3, 1, 1, '1985-03-10'),
('Ch''en', 2, 1, 1, 1, 2, '1995-07-08'),
('W', 3, 2, 4, 4, 3, '1998-12-25'),
('Blaze', 2, 1, 1, 1, 1, '1996-09-14'),
('Exusiai', 4, 5, 1, 1, 2, '1999-01-30'),
('SilverAsh', 6, 1, 1, 1, 1, '1988-04-22'),
('Ifrit', 6, 2, 1, 1, 1, '2005-08-17'),
('Hoshiguma', 2, 4, 1, 1, 2, '1993-06-11');

INSERT INTO Character_Department (character_id, department_id, role_in_department, join_date, leave_date) VALUES
(1, 1, 'Strategic Advisor', '2019-01-01', NULL),
(2, 1, 'Leader', '2019-01-01', NULL),
(3, 1, 'Chief Researcher', '2019-01-01', NULL),
(4, 3, 'Chief Inspector', '2018-06-15', '2020-03-20'),
(4, 1, 'Special Operator', '2020-03-21', NULL),
(5, 2, 'Demolition Expert', '2017-05-10', '2019-11-30'),
(6, 1, 'Vanguard Operator', '2019-02-15', NULL),
(7, 4, 'Courier', '2018-09-01', NULL),
(8, 1, 'Guard Operator', '2019-04-10', NULL),
(9, 1, 'Caster Operator', '2019-07-22', NULL),
(10, 3, 'Defender Officer', '2017-08-05', '2020-03-20'),
(10, 1, 'Defender Operator', '2020-03-21', NULL);

INSERT INTO Relationship (character_1_id, character_2_id, relation_type, description) VALUES
(1, 2, 'Mentor', 'Доктор является наставником и стратегом для Амьи'),
(2, 3, 'Colleague', 'Амья и Кали''тсука работают вместе в Rhodes Island'),
(1, 3, 'Friend', 'Доктор и Кали''тсука имеют долгую общую историю'),
(4, 10, 'Friend', 'Чен и Хошигума - близкие друзья и коллеги'),
(5, 2, 'Enemy', 'W была членом Reunion и противостояла Амье'),
(6, 1, 'Colleague', 'Блейз работает под командованием Доктора'),
(7, 4, 'Friend', 'Эксия и Чен знакомы по работе в Lungmen'),
(8, 2, 'Mentor', 'СильверЭш был наставником Амьи в прошлом'),
(9, 3, 'Colleague', 'Ифрит находится под наблюдением Кали''тсуки');

INSERT INTO Event (event_name, location_id, start_date, end_date, description) VALUES
('Chernobog Incident', 3, '2019-10-15', '2019-11-30', 'Катастрофа в городе Chernobog, организованная Reunion Movement'),
('Lungmen Crisis', 2, '2020-01-10', '2020-03-20', 'Кризис в Lungmen, связанный с деятельностью Reunion'),
('Rhodes Island Foundation', 1, '2018-05-01', NULL, 'Основание организации Rhodes Island'),
('Kazdel War', 4, '2015-06-01', '2017-12-31', 'Военный конфликт в регионе Kazdel'),
('Catastrophe in Ursus', 5, '2020-09-15', '2020-10-01', 'Природная катастрофа в империи Ursus');

INSERT INTO Event_Participant (event_id, character_id, department_id, role_in_event) VALUES
(1, 2, 1, 'Defender'),
(1, 5, 2, 'Attacker'),
(1, 1, 1, 'Organizer'),
(2, 4, 3, 'Defender'),
(2, 10, 3, 'Defender'),
(2, 5, 2, 'Attacker'),
(2, 6, 1, 'Defender'),
(3, 1, 1, 'Organizer'),
(3, 2, 1, 'Organizer'),
(3, 3, 1, 'Organizer'),
(4, 8, NULL, 'Attacker'),
(5, 9, 1, 'Victim');