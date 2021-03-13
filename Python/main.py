from threading import Thread,Semaphore
import random


class Coffee:
    """ Base class """

    def _init_(self, name, size):
        self.name = name
        self.size = size

    def get_name(self):
        """ Returns the coffee name """
        return self.name

    def get_size(self):
        """ Returns the coffee size """
        return self.size


class Espresso(Coffee):
    """ Espresso implementation """

    def __init__(self, size):
        Coffee._init_(self, "espresso", size)

    def get_message(self):
        """ Output message """
        return  " Espresso created"

class Americano(Coffee):
    """ Espresso implementation """

    def __init__(self, size):
        Coffee._init_(self, "americano", size)

    def get_message(self):
        """ Output message """
        return  " Americano created"

class Cappuccino(Coffee):
    """ Espresso implementation """

    def __init__(self, size):
        Coffee._init_(self, "capuccino", size)

    def get_message(self):
        """ Output message """
        return  "Capuccino created"

class Distributor:
    def __init__(self , size):
        self.coffees = []
        self.size = size
        self.semaphore1 = Semaphore(size)
        self.semaphore2 = Semaphore(0)
    
    def add_coffee(self , coffee):
        self.semaphore1.acquire()
        self.coffees.append(coffee)
        self.semaphore2.release()

    def take_coffee(self):
        self.semaphore2.acquire()
        coffee = self.coffees.pop()
        print(coffee.get_name() + ' consumed\n')
        self.semaphore1.release()

    def get_size(self):
        return self.size

class User(Thread):
    def __init__(self , distributor:Distributor):
        Thread.__init__(self)
        self.distributor = distributor
    def run(self):
        while(True):
            self.distributor.take_coffee()

class CoffeeFactory(Thread):
    def __init__(self , distributor:Distributor):
        Thread.__init__(self)
        self.distributor = distributor
    
    def run(self):
        while(True):
            coffeeType = random.randint(1 , 3)
            if coffeeType == 1:
                coffee = Espresso(3)
            elif coffeeType == 2 :
                coffee = Americano(5)
            else:
                coffee = Cappuccino(10)
            print(coffee.get_name() + ' created\n')
            self.distributor.add_coffee(coffee)


def main():
    distributor = Distributor(100)
    user = User(distributor)
    producer = CoffeeFactory(distributor)
    producer.start()
    user.start()

main()