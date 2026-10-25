from functools import reduce

students = [
    {"name": "Анна", "age": 20, "grade": 4.5},
    {"name": "Борис", "age": 22, "grade": 3.8},
    {"name": "Виктор", "age": 19, "grade": 4.2},
    {"name": "Галина", "age": 21, "grade": 4.9},
    {"name": "Дмитрий", "age": 23, "grade": 3.5},
]

# 1
formatted_students = list(map(lambda s: f"Имя: {s['name']}, Оценка: {s['grade']}",students))

# 2
top_students = list(filter(lambda s: s['grade'] > 4.0,students))

# 3
sum_and_count = reduce(lambda acc, s: (acc[0] + s['age'], acc[1] + 1),top_students, (0, 0))
average_age = sum_and_count[0] / sum_and_count[1] if sum_and_count[1] else None

print("-")
for line in formatted_students: print(line)

print("-")
print([s['name'] for s in top_students])

print("-")
if average_age is not None: print(f"средний возраст: {average_age}")
else: print("нет студентов для счёта")
