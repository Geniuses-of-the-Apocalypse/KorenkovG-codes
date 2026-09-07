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
# Программа выдаёт ошибку, если добавить пробел, в виде: " , , " (пробел,пробел,пробел) в строку зачений константы, где используются числа (по другому, где есть float).
# Но, если добавлять пробел, где есть уже значения, или, добавлять " , , , , , ......" в конец.
# Сколько угодно раз, после трух констант, то ошибки не будет. Во-первых, потому что, после трёх первых переменых константы, программе уже всё равно.
# Во-вторых, программе не важно, сколько пробелов внутри, когда есть значения, программа его просто не учитывает их.
# В-третьих, у переменной item, в связи с тем, что это некая информация (date), можно спокойно оставлять пробел, без вставления чего либо и программа будет работать.
#
# Функция parse_csv:
# Вход str, то есть любая строка. Выход list[dict] - список словарей, где ключи - название колонок, а значения, это строки.
# Функция compute_revenue:
# Вход домен list[dict], где каждый dict содержит ключи со строковыми числовыми значениями. Выход float - неотрицательное число.
# Функция top_item:
# Вход домен list[dict], где каждый dict содержит ключи со строковыми числовыми значениями. Выход Optional[dict] - либо словарь-строка с максимальной вырочкой, либо None, если список пуст.
#



