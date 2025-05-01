# A program to reverse the letters of a word

from SimpleStack import *

stack = Stack(100)                      # Create a stack to hold letters

word = input("Word to reverse: ")

for letter in word:                     # Loop over letters in word
    if not stack.isFull():              # Push letters on stack if not full
        stack.push(letter)


reverse = ''                            # Build the reversed version
while not stack.isEmpty():              # by popping the stack until empty
    reverse += stack.pop()


# Check if the word is a palindrome
checkPhrase = 'A man, a plan, a canal, Panama.'
print("Result of Palindrome check:",stack.test_palindrome(checkPhrase))
