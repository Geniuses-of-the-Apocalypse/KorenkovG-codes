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
    return list(csv.DictReader(data.splitlines()))


# 2
def compute_revenue(rows: list[dict]) -> float:
    return sum(map(lambda x: int(x["quantity"]) * float(x["price"]), rows))


# 3
def top_item(rows: list[dict]) -> Optional[dict]:
    if not rows:
        return None
    try:
        return max(rows, key=lambda x: int(x["quantity"]) * float(x["price"]))
    except (ValueError, TypeError, KeyError):
        return None


# main
rows = parse_csv(CSV_DATA)

print("Данные: ")
print(rows)

print("\n Выручка: ", compute_revenue(rows))

print("\n Товар с максимальной выручкой: ")
print(top_item(rows))


# 4
#
# 1) Все функции чистые. И они детерминированы.
#
#
# 2) Касаемо пробелов, если список пуст, top_item вернёт None, а если в
# строке окажутся не числа, а пустые значения или лишние пробелы try/except перехватит ValueError/TypeError
# и top_item тоже вернёт None, без выдачи ошибок.
# Если пробел вокруг числа, для item пробелы допустимы и не ломают логику, так как это поле не приводится к числам.
# Для quantity и price лишние пробелы внутри тоже не будут проблемой.
# А вот полностью пустые поля вызовут ValueError.
#
#
# 3) Функция parse_csv:
# Вход str. Выход: list[dict] — список словарей, где ключи — названия колонок, а значения — строки.
#
# Функция compute_revenue:
# Вход list[dict]. Выход float — суммарная выручка по всем строкам.
#
# Функция top_item:
# Вход list[dict]. Выход Optional[dict] — словарь с максимальной выручкой, либо None, если список пуст или данные невалидны.
#



