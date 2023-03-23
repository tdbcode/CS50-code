menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

print(menu)

running = True
while (running):
    try:
        choice = input("Please select a menu item. Press Ctrl + D to end choice.")
    except EOFError:
        print()
        running = False
        print(choice)

