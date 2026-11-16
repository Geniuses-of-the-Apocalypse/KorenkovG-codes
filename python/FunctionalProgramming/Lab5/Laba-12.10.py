from functools import reduce

STUDENTS = [
    {"name": "Анна", "age": 20, "grade": 4.5},
    {"name": "Борис", "age": 22, "grade": 3.8},
    {"name": "Виктор", "age": 19, "grade": 4.2},
    {"name": "Галина", "age": 21, "grade": 4.9},
    {"name": "Дмитрий", "age": 23, "grade": 3.5},
]

# 1
FORM_STUDENTS = list(map(lambda s: f"name: {s['name']}, mark: {s['grade']}",STUDENTS))

# 2
TOP_STUDENTS = list(filter(lambda s: s['grade'] > 4.0,STUDENTS))

# 3
AGE, COUNT = reduce(lambda acc, student: (acc[0] + student["age"], acc[1] + 1), TOP_STUDENTS, (0, 0))



print("-")
print(FORM_STUDENTS)

print("-")
print(TOP_STUDENTS)

print("-")
print(AGE / COUNT)
