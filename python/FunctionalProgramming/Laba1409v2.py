import csv
from typing import Optional

from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, field_validator, model_validator

# КОМАНДЫ и запросы:
# cd C:\Users\PythonOpenIDE\OpenIDEProjects\Laboratorki - выбор папки
# .venv\Scripts\activate - активирование виртуального окружения
# python -m uvicorn Laba1409v2:app --reload - запуск сервера
# deactivate
# http://127.0.0.1:8000/docs - сваггер
# http://127.0.0.1:8000/redoc - альтернатива
# http://127.0.0.1:8000/openapi.json - текст-код
# "csv_data": "item,quantity,price\norange,11,1.7\nbanana,14,3\ntank,2,77\ntank,1,77\nbanana,1,3"

app = FastAPI(title="CSV Revenue API (recursive)")
class RowModel(BaseModel):                        # строка CSV
    item: str
    quantity: int
    price: float

    @field_validator("item")
    @classmethod
    def item_not_empty(cls, v: str) -> str:
        if not v.strip():
            raise ValueError(" Название товара не может быть пустым ") # проверка
        return v.strip()

    @field_validator("quantity")
    @classmethod
    def quantity_positive(cls, v: int) -> int:
        if v <= 0:
            raise ValueError(" Количество должно быть > 0 ") # проверка
        return v

    @field_validator("price")
    @classmethod
    def price_positive(cls, v: float) -> float:
        if v <= 0:
            raise ValueError(" Цена должна быть > 0 ") # проверка
        return v

class CSVRequest(BaseModel): # тело запроса
    csv_data: str

    @field_validator("csv_data")
    @classmethod
    def csv_not_empty(cls, v: str) -> str:
        if not v.strip():
            raise ValueError(" CSV-строка не может быть пустой ")
        return v

class CSVResponse(BaseModel): # ответ api
    rows: list[RowModel]
    revenue: float
    top_item: RowModel



def parse_csv(data: str) -> list[dict]:
    return list(csv.DictReader(data.splitlines()))


def row_revenue(row: dict) -> float:
    return int(row["quantity"]) * float(row["price"])


def compute_revenue(rows: list[dict]) -> float:  # через рекурсию
    if not rows:
        return 0.0
    return row_revenue(rows[0]) + compute_revenue(rows[1:])


def top_item(rows: list[dict]) -> Optional[dict]:  # рекурсивный поиск товара с максимальной выручкой
    if not rows:
        return None
    if len(rows) == 1:
        return rows[0]

    best_of_rest = top_item(rows[1:])
    return rows[0] if row_revenue(rows[0]) > row_revenue(best_of_rest) else best_of_rest



@app.post("/analyze", response_model=CSVResponse)
def analyze_csv(request: CSVRequest):             # принимает CSV строку и возвращает выручку, а также товар с макс выручкой
    raw_rows = parse_csv(request.csv_data)
    if not raw_rows:
        raise HTTPException(status_code=400, detail=" CSV не содержит данных ")

    required = {"item", "quantity", "price"}    # проверка, что все нужные колонки на месте
    actual = set(raw_rows[0].keys())
    if not required.issubset(actual):
        missing = required - actual
        raise HTTPException(
            status_code=422,
            detail=f" Не хватает колонок: {missing} ",
        )

    validated_rows: list[RowModel] = []
    for i, row in enumerate(raw_rows, start=2):  # валидируем каждую строку через Pydantic
        try:
            validated_rows.append(RowModel(**row))
        except Exception as e:
            raise HTTPException(
                status_code=422,
                detail=f"Ошибка в строке {i}: {e}",
            )

    revenue = compute_revenue(raw_rows) # подсчёт метрик
    top = top_item(raw_rows)

    return CSVResponse(
        rows=validated_rows,
        revenue=revenue,
        top_item=RowModel(**top),
    )
