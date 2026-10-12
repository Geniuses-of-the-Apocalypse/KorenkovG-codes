def x_a(a):
    def y_b(b):
        def z_c(c):
            def range(y_min, y_max):
                if y_min > y_max:
                    return []
                def search(y, acc):
                    if y > y_max:
                        return acc
                    num = c - b * y
                    if num % a == 0:
                        acc.append((num // a, y))
                    return search(y + 1, acc)
                return search(y_min, [])
            return range
        return z_c
    return y_b


print(x_a(5)(3)(11)(-20,100 ))
