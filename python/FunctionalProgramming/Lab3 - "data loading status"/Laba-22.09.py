from enum import Enum
from dataclasses import dataclass
from typing import TypeVar, Generic, Union


# 1
class LoadState(Enum):
    LOADING = "LOADING"
    SUCCESS = "SUCCESS"
    ERROR = "ERROR"


# 2
@dataclass(frozen=True)
class User:
    name: str
    age: int
    email: str


# 3
T = TypeVar('T')
E = TypeVar('E')

@dataclass(frozen=True)  # успех и ошибка (типы-обертки)
class Success(Generic[T]):
    value: T

@dataclass(frozen=True)
class Failure(Generic[E]):
    error: E


type Result[T, E] = Union[Success[T], Failure[E]]

def load_users() -> Result[list[User], str]:
    users_data = [
        User(name="Ann", age=18, email="bytigirl@example.com"),
        User(name="Takemi", age=25, email="doctor@gmail.com"),
        User(name="Daniya", age=20, email="persona3lover@gmail.com"),
    ]

    if not users_data:
        return Failure(error="0ши6л4 -> пу3т0т4")  # failure (левая/правая ветка суммы)

    return Success(value=users_data) # success

# тест-пример
result = load_users()
if isinstance(result, Failure):
    print(f"Ошибка: {result.error}")
else:
    print(f"Успех, пользователей: {len(result.value)}")

# 4

# 1) Мощность = 3.
# 2) Result[list[User], str]. Его мощность будет -> " |list[User]| + |str| ".
