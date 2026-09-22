import re
from typing import Optional
from collections import Counter

CSV_TEXT = """\
Привет, текст  тест полный.
Ку. Даров. Куку.
Тест, т, т, т, т, т, т, тест.
КУРВАТИЛОБАВ

Т Т Т Т Т Т Т Т


"""


# 1
def split_words(text: str) -> list[str]:
    return \
        re.findall(r'[а-яё]+', text.lower())


# 2
def count_word_frequencies(words: list[str]) -> dict[str, int]:
    return \
        dict(Counter(words))


# 3
def top_word(freq: dict[str, int]) -> Optional[str]:
    return \
        max(freq, key=freq.get) if freq else None


print("Текст: ")
print(CSV_TEXT)

print(" \nСлова: ", split_words(CSV_TEXT))
print(" \nЧастоты слов: ", count_word_frequencies(split_words(CSV_TEXT)))
print(" \nСамое частое слово: ", top_word(count_word_frequencies(split_words(CSV_TEXT))))
print(f" Количество вхождений: {count_word_frequencies(split_words(CSV_TEXT))[top_word(count_word_frequencies(split_words(CSV_TEXT)))] if top_word(count_word_frequencies(split_words(CSV_TEXT))) else 0}")

# 4
#
# 1) Все функции чистые.
#
# 2) Все функции детерминированы.
#
# 3) Если входная строка будет пустая, то программа сработает, но значений
# и подсчёта не будет. А, ну и выведет None/
