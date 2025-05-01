import random
import time
import threading

# Customer Class
class Customer:
    orderNumberCounter = 0
    customers = {}

    def __init__(self):
        Customer.orderNumberCounter += 1
        self.id = Customer.orderNumberCounter
        self.order = self.get_random_order()
        self.time = time.time()
        self.money = random.uniform(0.00, 20.00)
        Customer.customers[self.id] = self

    def get_random_order(self):
        order_types = ['drink', 'chicken', 'fries']
        selected_orders = random.sample(order_types, 2)
        return selected_orders

    @staticmethod
    def get_all_customers():
        return Customer.customers

# Player Class
class Player:
    def __init__(self, name):
        self.name = name
        self.money = 0
        self.training = False

# Training Functions
def Training(player):
    completedTraining = set()
    while len(completedTraining) < 4:
        currentChoice = input("""Pick a station to train at:
            1. Grill Station
            2. Frying Station
            3. Drink Station
            4. Cashier Station
        """)
        currentChoice = int(currentChoice)

        if currentChoice not in completedTraining:
            if currentChoice == 1:
                GrillStationTraining()
            elif currentChoice == 2:
                FryingStationTraining()
            elif currentChoice == 3:
                DrinkStationTraining()
            elif currentChoice == 4:
                CashierStationTraining()
            completedTraining.add(currentChoice)
            print("Training completed!\n")
        else:
            print("You have already completed this training. Please choose another station.")

    player.training = True
    player.money += 50
    print(f"Update: {player.name} received $50 for completing training!")

# Individual Station Training Functions
def GrillStationTraining():
    print("Grill Station: Press enter to start the timer.")
    time_check(10, "Grill Station")

def FryingStationTraining():
    print("Frying Station: Press enter to start the timer.")
    time_check(5, "Frying Station")

def time_check(target_time, station_name):
    flag = False
    while not flag:
        input(f"Press enter to start the {station_name} timer.")
        start_time = time.time()
        input(f"Press enter again to stop {station_name} timer.")
        end_time = time.time()
        elapsed_time = end_time - start_time
        if abs(elapsed_time - target_time) <= 0.25:
            print(f"Good job! You timed: {elapsed_time}")
            flag = True
        else:
            print(f"Not quite. Try again.")

# Station Tasks
def GrillStation():
    print("Grilling chicken for customer!")
    time_check(10, "Grill Station")

def FryStation():
    print("Frying fries for customer!")
    time_check(5, "Fry Station")

def DrinkStation():
    print("Making a drink for the customer.")
    steps = ["Ice", "Soda", "Lid", "Straw"]
    for step in steps:
        user_input = input(f"Add {step}. Press 'Enter' to continue.")
    print("Drink complete!")

def CashierStation(total_money):
    print("Calculating total for customer.")
    while True:
        part1 = round(random.uniform(0, total_money), 2)
        part2 = round(total_money - part1, 2)
        print(f"Part 1: ${part1}, Part 2: ${part2}")
        user_answer = float(input("Enter the total amount: "))
        if abs(user_answer - total_money) <= 0.01:
            print("Correct! You've completed the order.")
            break

# Main Game Loop
def main_game(player):
    print("Game starting now!")
    while player.money < 200:
        print(f"Current Money: ${player.money}")
        new_customer = Customer()
        print(f"Customer {new_customer.id} has placed order: {new_customer.order}")

        for order in new_customer.order:
            if order == "drink":
                DrinkStation()
            elif order == "chicken":
                GrillStation()
            elif order == "fries":
                FryStation()

        CashierStation(new_customer.money)
        player.money += new_customer.money

    print(f"Congratulations {player.name}! You've earned ${player.money}. Time to go home!")

# Main Program Execution
print("Welcome to the McRonald's Simulator!")
player_name = input("Enter your name: ")
player = Player(player_name)

Training(player)
main_game(player)
