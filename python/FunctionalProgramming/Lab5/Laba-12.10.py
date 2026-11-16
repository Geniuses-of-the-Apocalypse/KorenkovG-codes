#5698e9388d28c6e9d5cf0582bb98fa888b0a9a874984a364a051b5476682ea96

from functools import reduce

STUDENTS = tuple((
    {"name": "Анна", "age": 20, "grade": 4.5},
    {"name": "Борис", "age": 22, "grade": 3.8},
    {"name": "Виктор", "age": 19, "grade": 4.2},
    {"name": "Галина", "age": 21, "grade": 4.9},
    {"name": "Дмитрий", "age": 23, "grade": 3.5} ))

# 1
FORM_STUDENTS = tuple(map(lambda s: f"name: {s['name']}, mark: {s['grade']}",STUDENTS))

# 2
def top(students, min_grade=4.0):
    def is_top(student):               
        return student["grade"] > min_grade
    return tuple(filter(is_top, students))

TOP_STUDENTS = top(STUDENTS)

# TOP_STUDENTS = tuple(filter(lambda s: s['grade'] > 4.0,STUDENTS))

# 3
AGE, COUNT = reduce(lambda acc, student: (acc[0] + student["age"], acc[1] + 1), TOP_STUDENTS, (0, 0))



print("1-")
print(FORM_STUDENTS)

print("2-")
print(TOP_STUDENTS)

print("3-")
print(AGE / COUNT)
