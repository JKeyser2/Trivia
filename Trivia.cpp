/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE);
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia();
  // Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename);
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu();
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects();
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
 // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject();
  // Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject);
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject();
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject);
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle();
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};


template <class T>
Trivia<T>::Trivia(string filename){

    //cout << "SIZE MQUESTIONS: " << m_questions->GetSize() << endl;

    //cout << "SIZE MSUBJECTS: " << m_subjects.size() << endl;

    DisplayTitle();

    LoadQuestions(filename);

    MainMenu();
}

template <class T>
Trivia<T>::~Trivia(){
    // Loops throught vector
    for(unsigned int i = 0; i < m_subjects.size(); i++){
        // Clears the string
        m_subjects.at(i) = "";
    }

    // Runs clear to deallocate
    //m_questions->Clear();

    for(int i = 0; i < m_questions->GetSize(); i++){
         delete m_questions->At(i);
    }

    delete m_questions;
    m_questions = nullptr;
}

template <class T>
bool Trivia<T>::LoadQuestions(string filename){

    // Retrieves the file
    ifstream infile(filename);


    // If file is opened
    if(infile.is_open()){

        m_questions = new Lqueue<Question<T>*>();

        // Declare and initialize string variables for storing data that will be parsed from the given text file
        string subject = "";
        string question = "";
        string datatype = "";
        string difficulty = "";
        // Declares and itializes a template variable for storing the data type for answer variable
        T answer;

        // Declares and initializes an int variable. 
        int counter = 0;

        // Reads through all the lines of the txt file, storing into appropriate variables
        while(getline(infile, subject, DELIMITER) && getline(infile, question, DELIMITER) &&
        getline(infile, datatype, DELIMITER) && getline(infile, difficulty, DELIMITER) && (infile>>answer)){
            // infle>>answer change answer to T

            //cout << "QUESTION: " << question << endl;
            //cout << "DATATYPE: " << datatype << endl;
            //cout << "DIFFICULTY: " << difficulty << endl;
            //cout << "ANSWER: " << answer << endl;

            // If not the first line
            if(counter > 0){
               // Remove the newline from the subject variable
               subject.erase(subject.begin()); 
            }

            // Increment counter to keep track of the current line
            counter++;

             //cout << "SUBJECT: " << subject << endl;

            // Converts string to an integer for difficulty
            int intDifficulty = stoi(difficulty);


            Question<T>* newQuestion = new Question<T>(subject, question, datatype, intDifficulty, answer);
            m_questions->Push(newQuestion);

            //m_questions->Display();


            // Runs function to see if the subject is in the vector at least once already
            // If not, adds the vector to the vector
            AddSubject(subject);

        }
         //cout << m_questions->GetSize() << endl;

        // for(int i = 0; i < m_questions->GetSize(); i++){
          //   cout << *m_questions->At(i) << endl;
        // }


        //DisplaySubjects();
        // Closes the file
        infile.close();


        return true;
    // If file cannot be opened
    }else{
        cout << "This file was unable to be opened!" << endl;

        return false;
    }
}

template <class T>
void Trivia<T>::MainMenu(){
    //cout << "MainMenu" << endl;

    // Declares and initializes an int variable for storing the user's input
    int userInput = 0;
    // Declares and intializs a boolean variable for whether or not the user wants to end the game
    bool endGame = false;

    // Runs the MainMenu
    do{
       cout << "Choose an option" << endl;
        cout << "1. Display Subjects" << endl;
        cout << "2. Start Subject" << endl;
        cout << "3. Quit" << endl; 
        cin >> userInput;

        // If user gives a choice that is not within the list given
        while(userInput > 3 || userInput < 1){
            cout << "That is not a possible choice. (1-3)" << endl;
            cout << "1. Display Subjects" << endl;
            cout << "2. Start Subject" << endl;
            cout << "3. Quit" << endl;
            cin >> userInput;
        }

        if(userInput == 1){
            DisplaySubjects();
        }else if(userInput == 2){
            StartSubject();
        }else if(userInput == 3){
            // Sets boolean to true to end the game
            endGame = true;
        }
    // While the user does not wish to end the game
    }while(endGame != true);


}

template <class T>
void Trivia<T>::DisplaySubjects(){
    // If no subjects
    if(m_subjects.size() == 0){
        cout << "There are no subjects" << endl;
    // If at least 1 subject
    }else{
        // Loops through
        for (unsigned int i = 0; i < m_subjects.size(); i++){
            // Prints out subject
            cout << i+1 << ". " << m_subjects.at(i) << endl;
        }
    }
}

template <class T>
void Trivia<T>::StartSubject(){
    // Keeps track of the question number
    int questionNumber = 1;
    // Stores user response
    T userResponse;

    // Gets index of subject we want
    int subjectIndex = ChooseSubject();

    // Gets the string for the subject out of vector
    string theSubject = m_subjects[subjectIndex];

    // Gets the amount of questions for that subject
    int amountOfQuestions = QuestionsPerSubject(theSubject);

    // Switches from int to double for division
    double amountOfQuestionsDouble = amountOfQuestions;
    double amountCorrect = 0;
    double amountIncorrect = 0;

    // If the subject has already been used
    if(amountOfQuestions == 0){
        cout << "There are no more questions for this topic" << endl;
    // If the subject has not already been used
    }else{

        cout << "There are " << amountOfQuestions << " for this subject." << endl;

        // Loops through the questions linked list
        for(int i = 0; i < m_questions->GetSize(); i++){
            // If the question is of the subject we want
            if(m_questions->At(i)->m_subject == theSubject){
                // Lets the user know the question and what type the response should be
                //cout << questionNumber << ". Question: " << m_questions->At(i)->m_question << endl;
                //cout << "Please enter with a(n) " << m_questions->At(i)->m_datatype << endl;
                cout << *m_questions->At(i);
                cin >> userResponse;

                // If user is correct
                if(userResponse == m_questions->At(i)->m_answer){
                    cout << "Correct!" << endl;
                    amountCorrect++;
                // If user is incorrect
                }else{
                    cout << "Incorrect!" << endl;
                    amountIncorrect++;
                }
                questionNumber++;

                // Changes the boolean to to true as the question has now been answered
                m_questions->At(i)->m_isAnswered = true;
            }
        }
        // Gets the perecent the user got correct
        double percentCorrect = 100 * (amountCorrect/amountOfQuestionsDouble);

        cout << "You got " << amountCorrect << " answers correct." << endl;
        cout << "You got " << amountIncorrect << " answers incorrect" << endl;
        cout << "Which is " << percentCorrect << "%." << endl;
        }
}

template <class T>
void Trivia<T>::AddSubject(string subject){
    // Declares and initializes a boolean variable for whether or not the subject is already there
    bool subjectAlreadyThere = false;

    // If no subjects currently
    if(m_subjects.size() == 0){
        // Adds the subject to the vector
        m_subjects.push_back(subject);
    // If there are subjects
    }else{
        // Loops through all subjects
        for(unsigned int i = 0; i < m_subjects.size(); i++){
            // If the subject is already in the vector, sets boolean to true
            if(m_subjects.at(i) == subject){
                subjectAlreadyThere = true;
            }
        }
        // After the loop is ran. If the subject is not there, add it to the vector
        if(subjectAlreadyThere == false){
            m_subjects.push_back(subject);
        }

    }
}

template <class T>
int Trivia<T>::ChooseSubject(){
    // Declares and initializes an int variable for storing what subject the user wants to play
    int subjectPosition = 0;

    cout << "What subject would you like to attempt?" << endl;
    cout << "Possible subjects" << endl;
    DisplaySubjects();
    cin >> subjectPosition;

    while(subjectPosition < 1 || subjectPosition > int(m_subjects.size())){
        cout << "You are out of range. Try agian." << endl;
        cin >> subjectPosition;
    }

    // Subtracts 1 from the subject position to get the index
    subjectPosition = subjectPosition - 1;

    return subjectPosition;
}

template <class T>
int Trivia<T>::QuestionsPerSubject(string subject){
    // Declares and initializes an int variable for keeping track the number of questions of a certain subject
    int counter = 0;

    // Loops through all of the questions
    for(int i = 0; i < m_questions->GetSize();i++){
            // If the question is of the subject we are looking for
            if((m_questions->At(i)->m_subject) == subject){
                // If the question is yet to be asked
                if((m_questions->At(i)->m_isAnswered) == false){
                    // Increments the counter
                    counter++;
                }
            }
        }
        return counter;
    
}

template <class T>
void Trivia<T>::DisplayTitle(){
    cout << "Welcome to UMBC Trivia!" << endl;
}

#endif