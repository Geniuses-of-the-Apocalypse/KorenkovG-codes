from functools import partial

# 1
filter_by = lambda key: lambda value: lambda items: tuple(item for item in items if item.get(key) == value)

TOOL = [
    {"name": "hammer", "category": "tools"},
    {"name": "pliers", "category": "tools"},
    {"name": "screwdriver", "category": "tools"},
]

# 2
#filter_by_category = filter_by("category")
#filter_tools = filter_by_category("tools")
print(((filter_by("category"))("tools"))(TOOL))

# 3
#greater_than = lambda threshold: lambda x: x > threshold
print(tuple(filter((lambda threshold: lambda x: x > threshold)(5), [12, 6123, 8, 2, 1])))
