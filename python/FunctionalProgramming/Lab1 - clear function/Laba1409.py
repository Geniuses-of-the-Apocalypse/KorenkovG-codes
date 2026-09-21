import csv
from typing import Optional


from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, field_validator

# КОМАНДЫ и запросы:
# cd C:\Users\PythonOpenIDE\OpenIDEProjects\Laboratorki - выбор папки
# .venv\Scripts\activate - активирование виртуального окружения
# python -m uvicorn Laba1409:app --reload - запуск сервера
# deactivate
# http://127.0.0.1:8000/docs - сваггер
# http://127.0.0.1:8000/redoc - альтернатива
# http://127.0.0.1:8000/openapi.json - текст-код
# "csv_data": "item,quantity,price\norange,11,1.7\nbanana,14,3\ntank,2,77\ntank,1,77\nbanana,1,3"

app = FastAPI(title="CSV Revenue API")
class RowModel(BaseModel):                       # строка CSV
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

class CSVRequest(BaseModel):
    csv_data: str                # тело запроса

    @field_validator("csv_data")
    @classmethod
    def csv_not_empty(cls, v: str) -> str:
        if not v.strip():
            raise ValueError(" CSV-строка не может быть пустой ")
        return v

class CSVResponse(BaseModel):          # ответ api
    rows: list[RowModel]
    revenue: float
    top_item: RowModel



def parse_csv(data: str) -> list[dict]:
    return list(csv.DictReader(data.splitlines()))


def compute_revenue(rows: list[dict]) -> float:
    return sum(float(x["quantity"]) * float(x["price"]) for x in rows)


def top_item(rows: list[dict]) -> Optional[dict]:
    return max(rows, key=lambda x: float(x["quantity"]) * float(x["price"]))



@app.post("/analyze", response_model=CSVResponse)
def analyze_csv(request: CSVRequest):          # принимает CSV строку и возвращает выручку, а также товар с макс выручкой
    raw_rows = parse_csv(request.csv_data)
    if not raw_rows:
        raise HTTPException(400, " CSV не содержит данных ")

    required = {"item", "quantity", "price"}       # проверка, что все нужные колонки на месте
    if missing := required - set(raw_rows[0].keys()):
        raise HTTPException(422, f" Не хватает колонок: {missing} ")

    validated_rows: list[RowModel] = []
    for i, row in enumerate(raw_rows, 2):          # валидируем каждую строку через Pydantic
        try:
            validated_rows.append(RowModel(**row))
        except Exception as e:
            raise HTTPException(422, f"Ошибка в строке {i}: {e}")

    # подсчёт метрик
    return CSVResponse(
        rows=validated_rows,
        revenue=compute_revenue(raw_rows),
        top_item=RowModel(**top_item(raw_rows)),
    )
