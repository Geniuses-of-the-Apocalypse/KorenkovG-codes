import csv
from typing import Optional

CSV_DATA = """\
item,quantity,price
orange,11,1.7
banana,14,3
tank,2,77
tank,1,77
banana,1,3
"""

# 1
def parse_csv(data: str) -> list[dict]:
    return \
        list(csv.DictReader(data.splitlines()))


# 2
def compute_revenue(rows: list[dict]) -> float:
    return \
        sum(
        int(row["quantity"]) * float(row["price"])
        for row in rows
    )


# 3
def top_item(rows: list[dict]) -> Optional[dict]:
    return\
        max(
        rows,
        key=lambda row: int(row["quantity"]) * float(row["price"]),
        default=None
    )


#main
rows = parse_csv(CSV_DATA)

print("Данные: ")
print(rows)

print("\n Выручка: ", compute_revenue(rows))

print("\n Товар с максимальной выручкой: ")
print(top_item(rows))


# 4
#
# Все функции чистые. Побочных эффектов тоже нет.
#
# Если в данных окажется пустая строка, то программа отработает нормально, вне зависимости, пустая строка внутри данных, или как весь ввод.
#
# Функция parse_csv:
# Вход str, то есть любая строка. Выход list[dict] - список словарей, где ключи - название колонок, а значения, это строки.
# Функция compute_revenue:
# Вход домен list[dict], где каждый dict содержит ключи со строковыми числовыми значениями. Выход float - неотрицательное число.
# Функция top_item:
# Вход домен list[dict], где каждый dict содержит ключи со строковыми числовыми значениями. Выход Optional[dict] - либо словарь-строка с максимальной вырочкой, либо None, если список пуст.
#



