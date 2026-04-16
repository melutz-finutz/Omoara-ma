#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <thread>
#include <chrono>

using namespace std;

const string RESET      = "\033[0m";
const string BOLD       = "\033[1m";
const string RED        = "\033[31m";
const string GREEN      = "\033[32m";
const string YELLOW     = "\033[33m";
const string BLUE       = "\033[34m";
const string MAGENTA    = "\033[35m";
const string CYAN       = "\033[36m";
const string BG_BLUE    = "\033[44m";
const string BG_MAGENTA = "\033[45m";
const string BG_CYAN    = "\033[46m";

const int MAX_ATTEMPTS = 10;
const int LINE_WIDTH   = 72;

vector<string> hangmanStages = {
    "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n  ^   |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n ^ ^  |\n=========",
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n^ ^ ^ |\n=========",
    "  +---+\n  |   |\n [O] |\n /|\\  |\n / \\  |\n^ ^ ^ |\n========="
};

void clearScreen() {
    system("cls");
}

void pauseMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

string centeredText(const string& text, int width) {
    int padding = max(0, width - (int)text.size());
    int left = padding / 2;
    int right = padding - left;
    return string(left, ' ') + text + string(right, ' ');
}

void drawHeader() {
    cout << BG_CYAN << string(LINE_WIDTH, ' ') << RESET << '\n';
    cout << BG_CYAN << BOLD << centeredText("HANGMAN ARENA", LINE_WIDTH) << RESET << '\n';
    cout << BG_CYAN << centeredText("Ghiceste cuvantul inainte sa pierzi!", LINE_WIDTH) << RESET << '\n';
    cout << BG_CYAN << string(LINE_WIDTH, ' ') << RESET << "\n\n";
}

void drawBoxLine() {
    cout << MAGENTA << "+" << string(LINE_WIDTH - 2, '-') << "+" << RESET << '\n';
}

void showGameState(const string& guessedWord,
                   const vector<char>& guessedLetters,
                   int attempts,
                   int score)
{
    clearScreen();
    drawHeader();

    drawBoxLine();
    cout << MAGENTA << "| " << RESET << BOLD << "Score: " << GREEN << score << RESET;
    cout << MAGENTA << string(LINE_WIDTH - 12, ' ') << "|" << RESET << '\n';

    cout << MAGENTA << "| " << RESET << BOLD << "Incercari ramase: " << YELLOW << attempts << RESET;
    cout << MAGENTA << string(LINE_WIDTH - 24, ' ') << "|" << RESET << '\n';
    drawBoxLine();

    cout << CYAN << hangmanStages[min((int)hangmanStages.size() - 1, MAX_ATTEMPTS - attempts)] << RESET << '\n';
    drawBoxLine();

    cout << MAGENTA << "| " << RESET << BOLD << "Cuvant: ";
    for (char c : guessedWord) {
        cout << BLUE << c << ' ' << RESET;
    }
    int filled = 8 + (int)guessedWord.size() * 2;
    if (filled < LINE_WIDTH - 2) {
        cout << MAGENTA << string(LINE_WIDTH - 2 - filled, ' ') << RESET;
    }
    cout << MAGENTA << "|" << RESET << '\n';

    cout << MAGENTA << "| " << RESET << BOLD << "Litere incercate: " << RESET;
    for (char c : guessedLetters) {
        cout << YELLOW << c << ' ' << RESET;
    }
    int lettersWidth = 16 + (int)guessedLetters.size() * 2;
    if (lettersWidth < LINE_WIDTH - 2) {
        cout << MAGENTA << string(LINE_WIDTH - 2 - lettersWidth, ' ') << RESET;
    }
    cout << MAGENTA << "|" << RESET << '\n';
    drawBoxLine();
    cout << '\n';
}

void animateWrongGuess(int stageIndex) {
    for (int i = 0; i < 3; ++i) {
        clearScreen();
        drawHeader();
        cout << RED << BOLD << centeredText("LITERA NU SE AFLA IN CUVANT!", LINE_WIDTH) << RESET << "\n\n";
        cout << RED << hangmanStages[min((int)hangmanStages.size() - 1, stageIndex)] << RESET << '\n';
        pauseMs(180);
    }
}

void animateWin() {
    vector<string> colors = {GREEN, YELLOW, CYAN, MAGENTA, BLUE};
    vector<string> messages = {
        "FELICITARI! AI CASTIGAT!",
        "VICTORIE SPECTACULOASA!",
        "AI GHICIT CUVANTUL!",
        "BRAVO! ESTI CAMPIONUL!",
        "WINNER! WINNER!"
    };
    for (int frame = 0; frame < 10; ++frame) {
        clearScreen();
        drawHeader();
        string color = colors[frame % colors.size()];
        string message = messages[frame % messages.size()];
        cout << color << BOLD << centeredText(message, LINE_WIDTH) << RESET << "\n\n";
        // Simple confetti effect
        for (int i = 0; i < 5; ++i) {
            cout << string(rand() % LINE_WIDTH, ' ') << color << "*" << RESET << "\n";
        }
        pauseMs(150);
    }
}

void animateLose(const string& word) {
    vector<string> colors = {RED, YELLOW, MAGENTA};
    vector<string> messages = {
        "AI PIERDUT!",
        "GAME OVER!",
        "INCERCAREA TA S-A TERMINAT!",
        "NU AI GHICIT CUVANTUL!",
        "LOSE! LOSE!"
    };
    for (int frame = 0; frame < 8; ++frame) {
        clearScreen();
        drawHeader();
        string color = colors[frame % colors.size()];
        string message = messages[frame % messages.size()];
        cout << color << BOLD << centeredText(message, LINE_WIDTH) << RESET << "\n";
        cout << YELLOW << centeredText("Cuvantul era: " + word, LINE_WIDTH) << RESET << "\n\n";
        // Dramatic effect
        for (int i = 0; i < 3; ++i) {
            cout << string(rand() % LINE_WIDTH, ' ') << color << "X" << RESET << "\n";
        }
        pauseMs(200);
    }
}

bool isLetter(char c) {
    return isalpha(static_cast<unsigned char>(c));
}

int main() {
    vector<string> words = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon",
        "mango", "orange", "papaya", "raspberry", "strawberry"
    };

    srand(static_cast<unsigned int>(time(nullptr)));
    int score = 0;

    string originalWord = words[rand() % words.size()];
    string word = originalWord;
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    string guessedWord(originalWord.size(), '_');
    vector<char> guessedLetters;
    int attempts = MAX_ATTEMPTS;

    showGameState(guessedWord, guessedLetters, attempts, score);

    while (attempts > 0 && guessedWord != originalWord) {
        char guess;
        cout << CYAN << BOLD << "Introdu o litera: " << RESET;
        cin >> guess;
        guess = static_cast<char>(tolower(static_cast<unsigned char>(guess)));

        if (!isLetter(guess)) {
            cout << RED << "Te rog introdu o litera valida!" << RESET << "\n";
            pauseMs(1000);
            showGameState(guessedWord, guessedLetters, attempts, score);
            continue;
        }

        bool alreadyGuessed = find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end();
        if (alreadyGuessed) {
            cout << YELLOW << "Ai introdus deja aceasta litera!" << RESET << "\n";
            pauseMs(1000);
            showGameState(guessedWord, guessedLetters, attempts, score);
            continue;
        }

        guessedLetters.push_back(guess);
        bool found = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessedWord[i] = originalWord[i];
                found = true;
            }
        }

        if (!found) {
            attempts--;
            score = max(0, score - 1);
            animateWrongGuess(MAX_ATTEMPTS - attempts);
            showGameState(guessedWord, guessedLetters, attempts, score);
        } else {
            score += 2;
            cout << GREEN << "Bravo! Litera se afla in cuvant." << RESET << "\n";
            pauseMs(800);
            showGameState(guessedWord, guessedLetters, attempts, score);
        }
    }

    if (guessedWord == originalWord) {
        animateWin();
        showGameState(guessedWord, guessedLetters, attempts, score);
        cout << GREEN << BOLD << "Ai castigat! Cuvantul era: " << originalWord << RESET << "\n";
    } else {
        animateLose(originalWord);
    }

    cout << CYAN << "\nMultumim ca ai jucat! Scor final: " << GREEN << score << RESET << "\n";
    return 0;
}
