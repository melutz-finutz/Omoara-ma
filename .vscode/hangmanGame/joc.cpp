#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

// Hangman stages (simple ASCII art)
vector<string> hangmanStages = {
    "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
};

int main() {
    // List of words
    vector<string> words = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape", "honeydew", "kiwi", "lemon"};
    
    // Seed random number generator
    srand(time(0));
    
    // Pick a random word
    string originalWord = words[rand() % words.size()];
    string word = originalWord;
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    
    // Initialize game state
    string guessedWord(originalWord.length(), '_');
    vector<char> guessedLetters;
    int attempts = 10;
    
    cout << GREEN << "Welcome to Hangman!" << RESET << endl;
    cout << "Guess the word: " << guessedWord << endl;
    
    while (attempts > 0 && guessedWord != originalWord) {
        char guess;
        cout << MAGENTA << "Enter a letter: " << RESET;
        cin >> guess;
        guess = tolower(guess);
        
        // Check if letter was already guessed
        bool alreadyGuessed = false;
        for (char c : guessedLetters) {
            if (c == guess) {
                alreadyGuessed = true;
                break;
            }
        }
        
        if (alreadyGuessed) {
            cout << RED << "You already guessed that letter!" << RESET << endl;
            system("pause");
            continue;
        }
        
        guessedLetters.push_back(guess);
        
        // Check if guess is in the word
        bool found = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess) {
                guessedWord[i] = originalWord[i];
                found = true;
            }
        }
        
        if (!found) {
            attempts--;
            cout << RED << "Wrong guess!" << RESET << endl;
        } else {
            cout << GREEN << "Good guess!" << RESET << endl;
        }
        
        system("pause");
    }
    
    // Clear screen for final
    system("cls");
    
    // Display final hangman stage
    cout << RED << hangmanStages[6 - attempts] << RESET << endl;
    
    if (guessedWord == originalWord) {
        cout << GREEN << "Congratulations! You won!" << RESET << endl;
    } else {
        cout << RED << "Game over! The word was: " << originalWord << RESET << endl;
    }
    
    return 0;
}