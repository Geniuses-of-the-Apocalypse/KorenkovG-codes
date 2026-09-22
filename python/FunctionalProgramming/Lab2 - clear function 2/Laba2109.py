import re
from typing import Optional
from collections import Counter

from fastapi import FastAPI
from pydantic import BaseModel, field_validator

# КОМАНДЫ и запросы:
# cd C:\Users\PythonOpenIDE\OpenIDEProjects\Laboratorki\Lb2 - выбор папки
# .venv\Scripts\activate - активирование виртуального окружения
# python -m uvicorn Laba2109:app --reload - запуск сервера
# deactivate
#
# http://127.0.0.1:8000/docs - сваггер
# http://127.0.0.1:8000/redoc - альтернатива
# http://127.0.0.1:8000/openapi.json - текст-код
#
#   "text": "Привет, текст тест полный.\nКу. Даров. Куку.\nТест, т, т, т, т, т, т, тест.\nКУРВАТИЛОБАВ\n\nТ Т Т Т Т Т Т Т"

app = FastAPI(title="Word Frequency API")

class TextRequest(BaseModel):
    text: str

    @field_validator("text")
    @classmethod
    def text_not_empty(cls, v: str) -> str:
        if not v.strip():
            raise ValueError(" Текст не может быть пустым или состоять только из пробелов ")
        return v

class TextResponse(BaseModel):
    words: list[str]
    frequencies: dict[str, int]
    top_word: Optional[str]
    top_word_count: int



def split_words(text: str) -> list[str]:
    return re.findall(r'[а-яё]+', text.lower())


def count_word_frequencies(words: list[str]) -> dict[str, int]:
    return dict(Counter(words))


def top_word(freq: dict[str, int]) -> Optional[str]:
    return max(freq, key=freq.get) if freq else None



@app.post("/analyze", response_model=TextResponse)
def analyze_text(request: TextRequest):

    words = split_words(request.text)

    freq = count_word_frequencies(words)

    top = top_word(freq)

    top_count = freq[top] if top else 0

    return TextResponse(
        words=words,
        frequencies=freq,
        top_word=top,
        top_word_count=top_count
    )
