ORDERS = tuple((
    {"id": 1, "total": 1200, "status": "paid"},
    {"id": 2, "total": 350,  "status": "new"},
    {"id": 3, "total": 9990, "status": "new"}, ))

# 1
totals_sums = tuple(map(lambda x: x["total"], ORDERS))


# 2
class OptionalBox:
    def __init__(self, value): self.value = value
    def map(self, fn): return OptionalBox(None if self.value is None else fn(self.value))


# 3
def find_order(orders, order_id): return OptionalBox(next((x for x in orders if x["id"] == order_id), None))

#---вывод
print(totals_sums)
print(find_order(ORDERS, 2).map(lambda x: x["total"]).value)
print(find_order(ORDERS, 999).map(lambda x: x["total"]).value)
