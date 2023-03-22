import sys

class Jar:
    def __init__(self, capacity):
        try:
            if capacity < 1:
                raise ValueError
            self._capacity = capacity
            self._size = 0
        except ValueError:
            print("You must entered an integer larger than 0")
            sys.exit(1)

    def __str__(self):
        return '🍪' * self.size

    def deposit(self, n):
        print("placeholder")

    def withdraw(self, n):
        print("placeholder")

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

def main():
    try:
        size = int(input("Enter size of cookie jar:"))
    except ValueError:
        print("Positive integer expected")
        sys.exit(1)

    jar = Jar(size)
    print(str(jar.capacity))
    print(str(jar))

if __name__ == "__main__":
    main()