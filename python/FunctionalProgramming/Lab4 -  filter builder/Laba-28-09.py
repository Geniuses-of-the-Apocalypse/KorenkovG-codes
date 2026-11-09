from functools import partial

# d06e68b0b362a5f523f9fc3700d36840242d60e24459f7230eb2b3ebdd46bcfb

# 1
FILTER_BY = lambda key: lambda value: lambda items: tuple(item for item in items if item.get(key) == value)

TOOL = [
    {"name": "hammer", "category": "tools"},
    {"name": "pliers", "category": "tools"},
    {"name": "screwdriver", "category": "tools"},
]

# 2
#filter_by_category = filter_by("category")
#filter_tools = filter_by_category("tools")
print(((FILTER_BY("category"))("tools"))(TOOL))

# 3
#greater_than = lambda threshold: lambda x: x > threshold
print(tuple(filter((lambda threshold: lambda x: x > threshold)(5), [12, 6123, 8, 2, 1])))
