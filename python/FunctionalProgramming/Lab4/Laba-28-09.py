from functools import partial

# 1
filter_by = lambda key: lambda value: lambda items: [item for item in tool if item.get(key) == value]

tool = [
    {"name": "hammer", "category": "tools"},
    {"name": "pliers", "category": "tools"},
    {"name": "screwdriver", "category": "tools"},
]

# 2
filter_by_category = filter_by("category")
filter_tools = filter_by_category("tools")
print(filter_tools(tool))

# 3
greater_than = lambda threshold: lambda x: x > threshold
over_five = greater_than(5)
numbers = [12, 6123, 8, 2, 1]
print(list(filter(over_five, numbers)))
