import tkinter as tk
from tkinter import messagebox
import random
import json

# Load the list of words from the JSON file
def load_words():
    with open("list_of_words.json", "r") as file:
        data = json.load(file)  # Load the list of dictionaries
        return [entry["word"] for entry in data] 


class Wordle:
    def __init__(self, root):
        self.root = root
        self.root.title("Wordle Game")
        
        self.words = load_words()  # Load words from the file
        self.secret_word = random.choice(self.words).upper()  # Select random word
        self.guesses = 6
        self.word_length = 5

        self.create_widgets()

    def create_widgets(self):
        # Title Label
        self.title_label = tk.Label(self.root, text="Wordle Game", font=("Times New Roman", 18, "bold"))
        self.title_label.pack(pady=10)

        # Instructions Label
        self.instruction_label = tk.Label(self.root, text="Guess the 5-letter word in 6 tries!", font=("Times New Roman", 14))
        self.instruction_label.pack(pady=5)

        # Guess Frame
        self.guess_frame = tk.Frame(self.root)
        self.guess_frame.pack(pady=10)

        # Input and Submit Button
        self.input_label = tk.Label(self.guess_frame, text="Enter your guess:", font=("Times New Roman", 14))
        self.input_label.grid(row=0, column=0, padx=5)
        self.input_entry = tk.Entry(self.guess_frame, font=("Times New Roman", 14), width=10)
        self.input_entry.grid(row=0, column=1, padx=5)
        self.submit_button = tk.Button(self.guess_frame, text="Submit", command=self.process_guess, font=("Times New Roman", 14))
        self.submit_button.grid(row=0, column=2, padx=5)

        # Results Frame
        self.results_frame = tk.Frame(self.root)
        self.results_frame.pack(pady=10)

        # Exit Button
        self.exit_button = tk.Button(self.root, text="Exit", command=self.root.destroy, font=("Times New Roman", 14))
        self.exit_button.pack(pady=10)

        # Initialize Guess Display
        self.guess_labels = []
        for i in range(self.guesses):
            row = []
            for j in range(self.word_length):
                label = tk.Label(self.results_frame, text="", font=("Times New Roman", 16), width=2, relief="groove", bg="light gray")
                label.grid(row=i, column=j, padx=2, pady=2)
                row.append(label)
            self.guess_labels.append(row)

    def process_guess(self):
        guess = self.input_entry.get().strip().upper()

        # Validate input
        if len(guess) != self.word_length or not guess.isalpha():
            messagebox.showerror("Error", f"Please enter a valid {self.word_length}-letter word.")
            return

        # Show the current guess
        self.display_guess(guess)

        # Check if the guess is correct
        if guess == self.secret_word:
            messagebox.showinfo("Congratulations", "You guessed the word!")
            self.ask_play_again()
            return

        # Reduce remaining guesses
        self.guesses -= 1

        if self.guesses == 0:
            messagebox.showinfo("Game Over", f"You've run out of guesses! The word was {self.secret_word}.")
            self.ask_play_again()

    def display_guess(self, guess):
        for i, letter in enumerate(guess):
            label = self.guess_labels[6 - self.guesses][i]
            label.config(text=letter)

            # Determine letter color
            if letter == self.secret_word[i]:
                label.config(bg="light green")  # Correct position
            elif letter in self.secret_word:
                label.config(bg="yellow")  # Correct letter, wrong position
            else:
                label.config(bg="red")  # Incorrect letter

    def ask_play_again(self):
        if messagebox.askyesno("Play Again", "Would you like to play again?"):
            self.reset_game()
        else:
            self.root.destroy()

    def reset_game(self):
        self.secret_word = random.choice(self.words).upper()
        self.guesses = 6

        # Clear guess labels
        for row in self.guess_labels:
            for label in row:
                label.config(text="", bg="light gray")

        # Clear input field
        self.input_entry.delete(0, tk.END)


# Main Application Entry Point
if __name__ == "__main__":
    # Ensure list_of_words.json exists
    try:
        words = load_words()
        #print(words)
    except Exception as e:
        print("Error loading words:", e)
        exit()
        

    # Initialize GUI
    root = tk.Tk()
    game = Wordle(root)
    root.mainloop()
