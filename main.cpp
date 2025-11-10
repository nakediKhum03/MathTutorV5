/*
* Title:       Math Tutor V5
*Programer(s): Khumo Nakedi & Christopher Thomas
*Date:         10/29/2025
*Github URL:   https://github.com/nakediKhum03/MathTutorV4.git
*Description:  A simple math tutor designed to help students practice and improve their basic  math arithmetic skills.
*              This program randomly generates integer-based math problems—addition, subtraction, multiplication,
*              and division for the user to solve. The user's name is collected using getline, and they are then
*              presented with one randomized problem at a time.
*
*              After each question, the user has up to three attempts to input the correct answer. If the answer
*              is still incorrect after three attempts, the correct solution is will be displayed.
*              The program is then asked if the user would like to continue solving more problems.
*
*              Based on how good the user is, they will affect the difficulty progression:
*              answering three questions correctly in a row levels the user up, increasing the maximum random number
*              range by +10 to make problems even more challenging.
*              Inversely, answering three incorrectly in total will level the user down (unless already at the
*              lowest level), reducing the difficulty range by -10.
*
*              Each session is summarized at the end in a formatted summary report showing all problems attempted, the
*              user’s responses, the number of attempts, and whether the answers were correct or incorrect. The
*              report also displays the user’s total correct, total incorrect, and average score percentage.
*
*              This version serves as the foundation for a more advanced math tutor that will later feature progress
*              tracking, adaptive difficulty, and personalized feedback to help students strengthen their math skills
*              and confidence.
*/


#include <cstdlib>
#include <ctime>
#include <cctype>
#include<iomanip>
#include <vector>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
using namespace std;

void DisplayGameIntro ();
string GetUserName ();


int main() {
    const int MAX_ATTEMPTS = 3;
    const int LEVEL_CHANGE = 10; //How much to increase the range when leveling up and down

    enum MATH_TYPE { MT_ADD = 1, MT_SUB = 2, MT_MUL = 3, MT_DIV = 4 };
    MATH_TYPE mathType = MT_ADD;

    string userName;
    int userAnswer = 0;
    int leftNum = 0;
    int rightNum = 0;
    char mathOperator = '?';
    int totalNum = 0;
    int tempNum = 0;
    int totalCorrect = 0;
    int totalIncorrect = 0;
    int mathLevel = 1;
    int currentRange = LEVEL_CHANGE;
    int attempts = 0;

    vector<vector<int> > questions;

   string userInput = "?" ;

    DisplayGameIntro () ;
    userName = GetUserName ();


    do {
        srand(time(0)); // Randomizing numbers
        leftNum = rand() % (currentRange - 1) + 1;
        rightNum = rand() % (currentRange - 1) + 1;
        mathType = static_cast<MATH_TYPE>(rand() % 4 + 1);

        switch (mathType) {
            // logic behind generating problems based of the math type
            case MT_ADD:
                mathOperator = '+';
                totalNum = leftNum + rightNum; // answer for addition
                break;
            case MT_SUB:
                mathOperator = '-';
                if (rightNum > leftNum) {
                    // making sure that we won't get a negative number when subtracting
                    tempNum = leftNum;
                    leftNum = rightNum;
                    rightNum = tempNum;
                }
                totalNum = leftNum - rightNum; // answer for subtraction
                break;
            case MT_MUL:
                mathOperator = '*';
                totalNum = leftNum * rightNum; //answer for multiplication
                break;
            case MT_DIV:
                mathOperator = '/';
                totalNum = leftNum; // makes sure there is no fractions and correct answer
                leftNum = leftNum * rightNum; // makes sure there is no fractions
                break;
            default: // if math type is invalid and it ends the program
                cout << "invaild math type!" << endl;
                cout << "contact Ethan or Khumo for help" << endl;
                return -1;
        }

        cout << "[Level #" << mathLevel << "] " << userName << ", what is " << leftNum << " " << mathOperator << " " <<
                rightNum << " = " << "?" << endl; // displays the question

        vector<int> row = {mathLevel, leftNum, rightNum, static_cast<int>(mathOperator), totalNum};
        int attemptsUsed = 0; // 0 = user never got it correct within MAX_ATTEMPTS


        for (int i = 1; i <= MAX_ATTEMPTS; ++i) {
            // ... your input handling stays the same ...

            while (!(cin >> userAnswer)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\tInvalid input!\n\tPlease enter a number:" << endl;
            }


            if (userAnswer == totalNum) {
                cout << "Excellent Job Einstein!" << endl;
                totalCorrect++;
                attemptsUsed = i; // record how many tries it took
                break; // stop asking this question
            }

            if (i == MAX_ATTEMPTS) {
                cout << "Sorry, you're out of attempts. Correct answer: " << totalNum << endl;
                totalIncorrect++;
            } else {
                cout << (MAX_ATTEMPTS - i) << " attempt/s left." << endl;
                cout << "Try Again" << endl;
            }
        }


        row.push_back(attemptsUsed); // attemptsUsed == 0 means Incorrect in summary

        questions.push_back(row); // now the row has 6 fields as the summary expects


        if (attemptsUsed == 0) {
            cout << endl;
        }


        if (totalCorrect == 3) {
            // Level Up logic
            mathLevel++;
            totalCorrect = 0;
            totalIncorrect = 0;
            currentRange += LEVEL_CHANGE;
            cout << "You are currently on level " << mathLevel << endl;
            cout << "Your new range is now from 1 to " << currentRange << endl;
            cout << endl;
        } else if (totalIncorrect == 3 && mathLevel > 1) {
            // Level Down logic
            mathLevel--;
            totalCorrect = 0;
            totalIncorrect = 0;
            currentRange -= LEVEL_CHANGE;
            cout << "You are currently on level " << mathLevel << endl;
            cout << "Your range is now from 1 to " << currentRange << endl;
            cout << endl;
        } // end of if-else

        getline(cin, userInput);

        while (true) {
            cout << "Do you want to continue (y=yes || n=no)? " << endl;
            getline(cin, userInput);

            for (int i = 0; i < userInput.size(); i++) {
                userInput.at(i) = tolower(userInput.at(i));
            }

            if (userInput == "y" || userInput == "yes" ||
                userInput == "n" || userInput == "no") {
                break;
            } else {
                cout << "Invalid input, please try again..." << endl;
                cout << endl;
            }
        } // end of while true loop
    } while (userInput == "yes" || userInput == "y"); // end of do-while

    cout << "===================================" << endl;
    cout << "          Summary Report           " << endl;
    cout << "===================================" << endl;
    cout << "Level      Questions     Attempts  " << endl;
    cout << "----- ------------------ --------- " << endl;
    cout << endl;

    totalCorrect = 0;
    totalIncorrect = 0;

    for (int i = 0; i < static_cast<int>(questions.size()); ++i) {
        mathLevel = questions.at(i).at(0);
        leftNum = questions.at(i).at(1);
        rightNum = questions.at(i).at(2);


        int opCode = questions.at(i).at(3);
        switch (opCode) {
            case 1: mathOperator = '+';
                break; // MT_ADD
            case 2: mathOperator = '-';
                break; // MT_SUB
            case 3: mathOperator = '*';
                break; // MT_MUL
            case 4: mathOperator = '/';
                break; // MT_DIV
            case '+':
            case '-':
            case '*':
            case '/':
                mathOperator = static_cast<char>(opCode); // already ASCII
                break;
            default:
                mathOperator = '?';
                break;
        }


        totalNum = questions.at(i).at(4);
        attempts = questions.at(i).at(5);

        // Align columns cleanly
        cout << right << setw(5) << mathLevel << "   ";
        cout << left << setw(18)
                << (to_string(leftNum) + " " + mathOperator + " " + to_string(rightNum) + " = " + to_string(totalNum))
                << right;

        if (attempts != 0) {
            cout << setw(6) << attempts << endl;
            totalCorrect++;
        } else {
            cout << "Incorrect" << endl;
            totalIncorrect++;
        }
    } // end of for loop

    int totalQs = static_cast<int>(questions.size());
    int percent = (totalQs > 0) ? (totalCorrect * 100) / totalQs : 0;

    cout << endl;
    cout << "Total Correct:   " << totalCorrect << endl;
    cout << "Total Incorrect: " << totalIncorrect << endl;
    cout << "Average:         " << percent << "%" << endl; // displays grading

    cout << endl;
    cout << "That's all folks!" << endl;
    cout << "Come back for version four to see what is in store!" << endl;
    cout << "End of program" << endl; // end of program
    cout << endl;

    return 0;
}

/****************************************************
 * Displays Program header
 ***************************************************/

void DisplayGameIntro() {
    cout << "******************************************************************************************************" <<
            endl; // Simply a header stating what this program is.
    cout << "*                               Welcome to the Simply Silly Math Tutor                               *" <<
            endl;
    cout << "******************************************************************************************************" <<
            endl;
    cout << endl;

    cout << "Fun math facts:" << endl;

    cout << "    * 1000 is the only number with an {A} in it form one to one thousand" << endl;
    // listing a few math facts for the user's entertainment
    cout << "    * There is no Roman numeral for zero" << endl;
    cout << "    * The largest prime digit has over 24 million digits" << endl;
    cout << "    * In a room of 23 people, there is a greater than 50% chance that two will share the same birthday" <<
            endl;
    cout << endl; // formatting whitespace
    cout << "******************************************************************************************************" <<
            endl;
    cout << endl; // formatting whitespace


    return;
}

/*******************************************************************
 *Get user's name, welcome user, and return user name
 *******************************************************************/

 string GetUserName () {

    string userName = "?";

    cout << "What is your name?" << endl; // where the user puts there name
    getline(cin, userName); // gets the user's fullnames with getline
    cout << "Welcome, " << userName << ", to the Simply Silly Math Tutor!" << endl; // prints and welcomes the user

    return userName;
}