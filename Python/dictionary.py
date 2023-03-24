pizzas = {
    "cheese": 9,
    "pepperoni": 10,
    "vegetable": 11,
    "buffalo chicken": 12
}

pizzas["cheese"] = 8

pizzas["bacon"] = 14

for pie, price in pizzas.items():
    print("A whole {} pizza costs ${}".format(pie,price))