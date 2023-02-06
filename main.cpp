#include <iostream>
#include <stack>
#include <string>

using namespace std;

/*
 * Public:
 *      Expression():
 *          Determine the type of expression.
 *              direction = 1 => infix
 *              direction = 2 => postfix
 *
 *      inToPost():
 *          Converts infix to postfix expression.
 *          Returns: Postfix expression as a String
 *
 *      postToIn():
 *          Converts postfix to infix expression.
 *          Returns: Infix expression as a String
 *
 *      Evaluate():
 *          Evaluates postfix expressions.
 *          Returns: The sum of the postfix expression as a Double
 *
 * Private:
 *      getPriority():
 *          Evaluates and manage operator priority.
 *          Params: char c => operator to evaluate
 *          Returns: int value of the priority
 *              0: not supported
 *              1: lowest
 *              2: highest
 *
 *      isOperator():
 *          Check if a given character is an operator.
 *          Params: Character to be evaluated
 *          Returns:
 *              True => is an operator
 *              False => not an operator
 */
class Expression {
private:
    string infix;
    string postfix;

    // Determine the priority of an operator
    static int getPriority(char c) {
        if (c == '+' || c == '-') {
            return 1;
        } else if (c == '*' || c == '/') {
            return 2;
        } else {
            return 0;
        }
    }

    // Check if a character is an operator
    static bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

public:

    Expression(const string& input, int direction) {
        if (direction == 1) {
            infix = input;
        } else if (direction == 2) {
            postfix = input;
        }
    }

    // Convert infix to postfix
    string inToPost() {
        stack<char> operatorStack;
        string _postfix;

        for (char i : infix) {
            if (isdigit(i)) {
                _postfix += i;
                _postfix += " ";
            } else if (isOperator(i)) {
                while (!operatorStack.empty() && getPriority(operatorStack.top()) >= getPriority(i)) {
                    _postfix += operatorStack.top();
                    _postfix += " "; // Add a space between operands
                    operatorStack.pop();
                }
                operatorStack.push(i);
            }
        }

        while (!operatorStack.empty()) {
            _postfix += operatorStack.top();
            _postfix += " ";    // Insert spaces between operands
            operatorStack.pop();
        }

        this->postfix = _postfix;
        return _postfix;
    }

    // Convert postfix to infix
    string postToIn() {
        stack<string> operandStack;
        string _infix;

        if (postfix.empty()) {
            throw "No expression provided.";
        }
        for (int i = 0; i < postfix.length(); i++) {
            if (isdigit(postfix[i])) {
                string operand;
                while (i < postfix.length() && isdigit(postfix[i])) {
                    operand += postfix[i];
                    i++;
                }
                operandStack.push(operand);
                i--;
            } else if (isOperator(postfix[i])) {
                try {
                    string operand1 = operandStack.top();
                    operandStack.pop();
                    if (operandStack.empty()) {
                        throw "Invalid expression. try adding a space between operands";
                    } else {
                        string operand2 = operandStack.top();
                        operandStack.pop();
                        string newOperand = "(" + operand2 + postfix[i] + operand1 + ")";
                        operandStack.push(newOperand);
                    }

                } catch (const char* msg) {
                    cerr << msg << endl;
                    exit(1);
                }
            }
        }

        _infix = operandStack.top();
        this->infix = _infix;
        return _infix;
    }

    // Evaluate postfix expression
    double evaluate() {
        stack<double> operandStack;

        for (int i = 0; i < postfix.length(); i++) {
            if (isdigit(postfix[i])) {
                string operand;
                while (i < postfix.length() && isdigit(postfix[i])) {
                    operand += postfix[i];
                    i++;
                }
                operandStack.push(stod(operand));
                i--;
            } else if (isOperator(postfix[i])) {
                double operand1 = operandStack.top();
                operandStack.pop();
                double operand2 = operandStack.top();
                operandStack.pop();
                double result;
                switch (postfix[i]) {
                    case '+':
                        result = operand2 + operand1;
                        break;
                    case '-':
                        result = operand2 - operand1;
                        break;
                    case '*':
                        result = operand2 * operand1;
                        break;
                    case '/':
                        result = operand2 / operand1;
                        break;
                }
                operandStack.push(result);
            }
        }

        return operandStack.top();
    }
};

/*
 * Displays header for the program
 */
void printHeader() {
    cout << "---------------------------------" << endl;
    cout << "Expression Evaluator" << endl;
    cout << endl;
    cout << "Author: Frederik Blais" << endl;
    cout << "ID: 002-34-2775" << endl;
    cout << "---------------------------------" << endl;
}

/*
 * Displays the main menu of the program
 */
void printMenu() {
    cout << endl;
    cout << "Select an option:" << endl;
    cout << endl;
    cout << "1. Infix to Postfix" << endl;
    cout << "2. Postfix to Infix" << endl;
    cout << "3. Evaluate Expression" << endl;
    cout << endl;
    cout << "4. Documentation" << endl;
    cout << "5. Quit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

/*
 * Displays Documentation to the user
 */
void printDocMenu() {
    cout << endl;
    cout << "|---------------------------------|" << endl;
    cout << "| ********** Doc menu *********** |" << endl;
    cout << "|--------------------------------------------------------------------------------------------|" << endl;
    cout << "| 1. Infix to Postfix: Enter an infix expression and the program will convert it to postfix. |" << endl;
    cout << "|    -> Expression should be in the following formats: 2+3, 2+3*4, (2+3)*4, etc.             |" << endl;
    cout << endl;
    cout << "| 2. Postfix to Infix: Enter a postfix expression and the program will convert it to infix.  |" << endl;
    cout << "|    -> Expression should be in the following formats: 2 3 +, 2 2+, 2 3*, 2 3 4 / 5 * 3 etc. |" << endl;
    cout << "|    -> Note that the expressions must be space separated.                                   |" << endl;
    cout << endl;
    cout << "| 3. Evaluate Expression: Enter a postfix expression and the program will evaluate it.       |" << endl;
    cout << "|    -> Expression should be in the following formats: 2 3 +, 2 2+, 2 3*, 2 3 4 / 5 * 3 etc. |" << endl;
    cout << "|--------------------------------------------------------------------------------------------|" << endl;

    // wait for user to press enter to continue
    cout << endl;
    cout << "Press enter to continue..." << endl;
    cout << "*** In some cases, you may need to press enter twice... ***";
    cin.ignore();
    cin.get();

    // relaunch program
}

/*
 * Terminate the program
 */
void quit() {
    cout << endl;
    cout << "|---------------------------------|" << endl;
    cout << "| ******** Goodbye! ************* |" << endl;
    cout << "|---------------------------------|" << endl;
    ::exit(0);
}

/*
 * Validates the user's choice
 *
 * Params: int choice
 */
bool isValidChoice(int choice) {
    if (choice < 1 || choice > 5 || cin.fail()) {
        cout << endl;
        cout << "|---------------------------------|" << endl;
        cout << "| ******* Invalid choice ******** |" << endl;
        cout << "|---------------------------------|" << endl;
        return false;
    } else if (choice == 4) {
        printDocMenu();
        return false;
    } else if (choice == 5) {
        quit();
    }

    return true;
}

// Manage user input in main menu
int handleInput(const string& input, int choice) {

    int direction;

    if (choice == 1)
        direction = 1;
    else if (choice == 2 || choice == 3)
        direction = 2;
    else
        direction = 0;

    Expression expression(input, direction);

    switch (choice) {
        case 1:
            cout << "The postfix expression is: " << expression.inToPost() << endl;
            break;
        case 2:
            cout << "The infix expression is: " << expression.postToIn() << endl;
            cout << endl;
            break;
        case 3:
            cout << "The result is: " << expression.evaluate() << endl;
        case 4:
            break;
        case 5:
            cout << "Goodbye!" << endl;
            return 1;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
    return 0;
}

/*
 * Expression Evaluator
 * By: Frederik Blais 002-34-2775
 *
 * Can evaluate single digit numbers
 *  ex: 2+2 -> 2 2 +
 *      2 2 + -> (2+2)
 *
 * Supports parentheses for infix format (both as an input and as an output)
 *
 * Implemented a Documentation option for the user since they cannot see the code
 *
 * Error handling for bad input
 *  ex: evaluate 22+ => there's no spaces between the 2's, the program treats it as 22 + null, should be 2 2 +
 */
int main() {
  string input;
    int choice;

    // Program title
    printHeader();

    // Loop until user enters 1,2,3
    // If user enters 4, display help menu
    // If user enters 5, exit program
    for(;;) {
        // Print menu
        printMenu();

        // Get user input
        cin >> choice;

        // Handle user input
        if (isValidChoice(choice))
            break;
    }

    // Get user's expression to evaluate or convert
    cout << "Enter an expression: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    // Handle user input
    handleInput(input, choice);

    return 0;
}

// Issue tracker ----------------------------------
// [Done] issues with evaluating postfix expression
// [Done] issues with converting postfix to infix
// [Done] issues with converting infix to postfix
// [Done] Complete help menu

// TODO: Document code
// TODO: Git repo
// TODO: Error Handling
// TODO: Type checking
// TODO: Not let user input an infix expression in "evaluate" mode
// TODO: Infix to postfix: add spaces between operands and operators ex: 234*+ -> 2 3 4 * +
// TODO: Support for multi digit numbers
