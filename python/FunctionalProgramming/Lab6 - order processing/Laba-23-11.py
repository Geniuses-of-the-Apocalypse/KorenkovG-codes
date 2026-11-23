#a5f8190aed61f5f33ddcde85b4d05b05a7f5d5a0518595d5e17b259c8fb2a4e9


from typing import Any, Callable

# 1
def total():
    def run(orders):
        return tuple(map(lambda x: x["total"], orders))
    return run


# 2
class OptionalBox:
    def __init__(self, v): self.v = v
    def map(self, f): return OptionalBox(f(self.v)) if self.v is not None else OptionalBox(None)
    def val(self): return self.v


# 3
def find_order(orders_iter, order_id):
    def matches(order):
        return order["id"] == order_id
    def search():
        return next(filter(matches, orders_iter), None)
    return OptionalBox(search())

#---вывод

data =[{"id": 1, "total": 1200, "status": "paid"}, {"id": 2, "total": 322,  "status": "new"}, {"id": 3, "total": 9990, "status": "new"}]

get_totals = total()

print(get_totals(data))
print(find_order(data, 2).map(lambda x: x["total"]).val())
print(find_order(data, 999).map(lambda x: x["total"]).val())
