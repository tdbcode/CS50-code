class Jar:
    def __init__(self, capacity):
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return '🍪' * self.size

    def deposit(self, n):
        print("placeholder")

    def withdraw(self, n):
        print("placeholder")

    @property
    def capacity(self):
        return capacity

    @property
    def size(self):
        return size

def main():
    Jar jar = Jar(12)
    print(str(jar))

if __name__ == "__main__":
    main()


