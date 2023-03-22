class Jar:
    def __init__(self, capacity=12):
        self.capacity = capacity
        self.size = 0

    def __str__(self):
        ...

    def deposit(self, n):
        ...

    def withdraw(self, n):
        ...

    @property
    def capacity(self):
        return capacity

    @property
    def size(self):
        ...

def main():
    Jar jar = Jar()
    print(str(jar.capacity))

if __name__ == "__main__":
    main()


