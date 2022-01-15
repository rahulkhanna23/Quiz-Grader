//
//  main.cpp
//  Project2
//
// Name: Rahul Khanna Gopikannan


// Program to check Answer file and compare it with contestant file and output a report


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

// this function will compare the answer file with contestant file

void answercheck(fstream &ansFile, fstream &contFile) {
   
    // initializing answerFileCount to 0 which will count the number of answers/questions in the file
    
    int answerFileCount=0;
    char answerData;
    while (ansFile >> answerData) {
        answerFileCount++;
    }
    
    // clearing and moving the pointer back to the top to read again
    
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // created a new dynamic allocated array to store in the answer key data into answer array
    
    char *answer = nullptr;
    answer = new char [answerFileCount];
    for (int i=0; i<answerFileCount; i++) {
        ansFile >> *(answer+i);
    }
    
    // contCounter will count the number of students while dataContFile is the string that holds line by line
    
    string dataContFile;
    int contCounter = 0;
    while (getline(contFile, dataContFile)) {
        contCounter++;
    }
    
    // clearing and moving pointer back to beginning
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    //splitting the contestant array
    string Contline;
    string finalLine;
    string name;
    
    // creating multiple new arrays
    
    // contestant array will hold the value of the contestant
    char *contestant = nullptr;
    contestant = new char [answerFileCount];
    
    // questions that were wrongly answered
    int *wrongNumber = nullptr;
    wrongNumber = new int [answerFileCount];
    
    // correct answer array
    char *correctAns = nullptr;
    correctAns = new char [answerFileCount];
    
    // user answer for that wrong question
    char *userAnswer = nullptr;
    userAnswer = new char [answerFileCount];
   
    // get line by line from contestant to split them into ID and Answers
    
    while (getline(contFile, Contline)) {
        name = Contline.substr(0, 10);
        finalLine = Contline.substr(11, answerFileCount+answerFileCount-1);
        
        // calculate the length of the answer substr
        long long length = finalLine.length();
        
        // this for loop is intended to exclude the whitespaces and add the data into contestant array
        
        int x=0;
        for (int i=0; i<length; i++) {
            if (!(finalLine.at(i) == ' ')) {
                
                *(contestant+x) = finalLine.at(i);
                x++;
            }
        }
        
        
        
        int correctAnswer=0;
    
        int wrongNumberIndex=0;
        int userAnswerIndex=0;
        int correctAnswerIndex=0;
        
        // for loop to compare cont ans and correct ans, if they match we increment correctAnswer
        
        for (int i=0; i<answerFileCount; i++) {
        
            if (*(answer+i) == *(contestant+i))
                correctAnswer++;
            
            // else wrong answer
            else {
                
                //assigns the index of wrong ans to wrongNumber and increment wrongnumIndex

                *(wrongNumber+wrongNumberIndex)=i+1;
                wrongNumberIndex++;
                
               
                //assigns wrongly answered to userAns
                
                *(userAnswer+userAnswerIndex)= *(contestant+i);
                userAnswerIndex++;
                
                //assigns the correct answer
                
                *(correctAns+correctAnswerIndex) = *(answer+i);
                correctAnswerIndex++;
                
            }
        }
      
        // calculating score here with number of correct answers
        
        double score = (correctAnswer*100.00) / answerFileCount;
        
        // printing them out in correct order
        cout << name << " - " << fixed << setprecision(2) << score << endl;
        
        // printing the wrong numbers if score is less than 100
        
        if ((score != 100)) {
            for(int i=0; i<wrongNumberIndex; i++) {
                if (i == wrongNumberIndex-1)
                    cout << *(wrongNumber+i);
                else
                    cout << *(wrongNumber+i) << " ";
                
            }
            
            cout << endl;
            
            // printing user answers
            
            for(int i=0; i<userAnswerIndex; i++) {
                if (i == userAnswerIndex-1) {
                    if ((*(wrongNumber+i) < 10))
                        cout << *(userAnswer+i);
                    else if (*(wrongNumber+i) < 100)
                        cout << " " << *(userAnswer+i);
                    else
                        cout << "  " << *(userAnswer+i);
                }
                else {
                    if ((*(wrongNumber+i) < 10))
                        cout << *(userAnswer+i) << " ";
                    else if (*(wrongNumber+i) < 100)
                        cout << " " << *(userAnswer+i) << " ";
                    else
                        cout << "  " << *(userAnswer+i) << " ";
                }
            }
            cout << endl;
            
            // printing correct answers for those missed questions
            
            for(int i=0; i<correctAnswerIndex; i++) {
                if (i == correctAnswerIndex-1) {
                    if (*(wrongNumber+i) < 10)
                        cout << *(correctAns+i);
                    else if (*(wrongNumber+i) < 100)
                        cout << " " << *(correctAns+i);
                    else
                        cout << "  " << *(correctAns+i);
                    
                }
                else {
                    if (*(wrongNumber+i) < 10)
                        cout << *(correctAns+i) << " ";
                    else if (*(wrongNumber+i) < 100)
                        cout << " " << *(correctAns+i) << " ";
                    else
                        cout << "  " << *(correctAns+i) << " ";
                }
            }
            cout << endl;
            
        }
        cout << endl;
        
    }
    
    // deleting all the dynamically created arrays
       delete[] answer;
       delete[] contestant;
       delete[] wrongNumber;
       delete[] correctAns;
       delete[] userAnswer;
    
}


// this function will calculate the mean from the calculated score

void meanFunction(fstream &ansFile, fstream &contFile) {
    
    // clearing and moving pointer back to top
    
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    
    // again doing the same process from previous function
    // counting answer key
    
    int answerFileCount=0;
    char answerData;
    while (ansFile >> answerData) {
        answerFileCount++;
    }
    
    // clearing and moving pointer back to top
    
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // assigning answer values to answer array
    
    char *answer = nullptr;
    answer = new char [answerFileCount];
    for (int i=0; i<answerFileCount; i++) {
        ansFile >> *(answer+i);
    }
    
    // reset and moving back to top
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // clearing contestant file
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    // counting number of contestants
    string contline;
    int contCounter = 0;
    while (getline(contFile, contline)) {
        
        contCounter++;
    }
    
    //resetting and moving back to top
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    
    
    string line;
    string finalLine;
    string name;
    
    // creating score array to hold cont scores
    double *score = nullptr;
    score = new double [contCounter];
    
    // test is the index for score array
    int test = 0;
    
    // creating other respected arrays
    
    char *contestant = nullptr;
    contestant = new char [answerFileCount];
    
    int *wrongNumber = nullptr;
    wrongNumber = new int [answerFileCount];
    
    char *correctAns = nullptr;
    correctAns = new char [answerFileCount];
    
    char *userAnswer = nullptr;
    userAnswer = new char [answerFileCount];
    
    // splitting the contestant data into string and cont answers
    
    while (getline(contFile, line)) {
        name = line.substr(0, 10);
        finalLine = line.substr(11, answerFileCount+answerFileCount-1);
        
        // calculating length of cont answers
        long long length = finalLine.length();
        
        // storing cont answers in an array excluding whitespace
        
        int x=0;
        for (int i=0; i<length; i++) {
            if (!(finalLine.at(i) == ' ')) {
                
                *(contestant+x) = finalLine.at(i);
                x++;
            }
        }
        

        // creating new int variables to count the appearances
        int correctAnswer=0;
        int wrongNumberIndex=0;
        int userAnswerIndex=0;
        int correctAnswerIndex=0;
        
        
        for (int i=0; i<answerFileCount; i++) {
            if (*(answer+i) == *(contestant+i))
                correctAnswer++;
            
            // else wrong answer
            else {
                
                // assigning wrong numbers to wrongNumber array
                
                *(wrongNumber+wrongNumberIndex)=i+1;
                wrongNumberIndex++;
                
                // assigning cont answer to userAnswer
                *(userAnswer+userAnswerIndex)= *(contestant+i);
                userAnswerIndex++;
                
                // assigning correct answers to correctAns
                *(correctAns+correctAnswerIndex) = *(answer+i);
                correctAnswerIndex++;
                
            }
        }
        
        
        // calculating score here
        *(score+test) = (correctAnswer*100.00) / answerFileCount;
        test++;
    }
    
    // score array holds all the scores from while loop
    // created a new array totalScore to add up all scores
    double totalScore = 0;
    for (int i=0; i<contCounter; i++) {
        totalScore += *(score+i);
    }
    
    // printing out the mean value
        cout << "Mean: " << (totalScore*1.00)/contCounter << endl;
   
    
    // deleting all the dynamically created arrays
       delete[] answer;
       delete[] contestant;
       delete[] wrongNumber;
       delete[] correctAns;
       delete[] userAnswer;
       delete[] score;
    
}


// this function will take in the values to sort the arrays in ascending order
// under the if condition if (a>b)
// called whenever needed (median and mode)

void swap(string &a, string &b) {
    string temp;
    temp = a;
    a = b;
    b = temp;
}

// this function will calculate the median of the scores

void medianFunction(fstream &ansFile, fstream &contFile) {
    
    
    // reset ans file and moving pointer back to top
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // counting number of answer data
    int answerFileCount=0;
    char answerData;
    while (ansFile >> answerData) {
        answerFileCount++;
    }
    
    // resetting ans file and moving back to top
    
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    //assiging answer key to answer array
    
    char *answer = nullptr;
    answer = new char [answerFileCount];
    for (int i=0; i<answerFileCount; i++) {
        ansFile >> *(answer+i);
    }
    
    // resetting ans file and moving back to top
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
   // resetting cont file and moving back to top
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    // counting the number of students
    string line1;
    int contCounter = 0;
    while (getline(contFile, line1)) {
        
        contCounter++;
    }
    
    // resetting cont file and moving back to top
    contFile.clear();
    contFile.seekp(0, ios::beg);
    contFile.seekg(0, ios::beg);
    
   // creating variable to help split the contestant data
    string line;
    string finalLine;
    string name;
    
    // score for scores
    double *score = nullptr;
    score = new double [contCounter];
    
    // test is the index for score array
    int test = 0;
    
    // contestant array for contestant data
    char *contestant = nullptr;
    contestant = new char [answerFileCount];
    
    // array for all the wrongly answered questions
    int *wrongNumber = nullptr;
    wrongNumber = new int [answerFileCount];
    
    // array to hold correct answers
    char *correctAns = nullptr;
    correctAns = new char [answerFileCount];
    
    // array for user answers
    char *userAnswer = nullptr;
    userAnswer = new char [answerFileCount];
    
    
    // getting line by line and splitting contestant data into ID and answers
    
    while (getline(contFile, line)) {
        name = line.substr(0, 10);
        finalLine = line.substr(11, answerFileCount+answerFileCount-1);
        
        // calculating length of split answers
        long long length = finalLine.length();
        
        // assigning contestant answers excluding whitespace
        int x=0;
        for (int i=0; i<length; i++) {
            if (!(finalLine.at(i) == ' ')) {
                
                *(contestant+x) = finalLine.at(i);
                x++;
            }
        }
        
        
        // counter variables to keep track
        int correctAnswer=0;
        int wrongNumberIndex=0;
        int userAnswerIndex=0;
        int correctAnswerIndex=0;
        
        // for loop to check matching
        for (int i=0; i<answerFileCount; i++) {
            if (*(answer+i) == *(contestant+i))
                correctAnswer++;
            
            // else wrong answer
            else {
                
                // assigining wrong numbers and incrementing
                *(wrongNumber+wrongNumberIndex)=i+1;
                wrongNumberIndex++;
                
                // assigning user answers and incrementing
                *(userAnswer+userAnswerIndex)= *(contestant+i);
                userAnswerIndex++;
                
                // assigning correct answers and incrementing
                *(correctAns+correctAnswerIndex) = *(answer+i);
                correctAnswerIndex++;
                
            }
        }
        
        
        // calculating score
    *(score+test) = (correctAnswer*100.00) / answerFileCount;
        test++;
    }
    
    // for loop to sort the arrays
    // if first > second value, call swap function and sort it
    for (int i=0; i<contCounter; i++) {
        for (int j=0; j<contCounter-i-1; j++) {
            if (*(score+j) >  *(score+j+1))
                swap(*(score+j), *(score+j+1));
        }
    }
    
    // two cases while printing out median
    int midValue;
    double evenValueMedian;
    
    // if number of contestants are odd then this step output
    if (contCounter % 2 != 0) {
        midValue = (contCounter + 1)*1.00 / 2;
        cout << "Median: " << (*(score + midValue - 1)) * 1.00;
    }
    // else (even) then we take the mid value of the middle values and output that
    else {
        midValue = (contCounter / 2);
        evenValueMedian = *(score + midValue - 1) + *(score + midValue);
        evenValueMedian = evenValueMedian / 2;
        cout << "Median: " << evenValueMedian * 1.00;
    }
    cout << endl;
    
    // deleting all the dynamically created arrays
       delete[] answer;
       delete[] contestant;
       delete[] wrongNumber;
       delete[] correctAns;
       delete[] userAnswer;
       delete[] score;
    
}

// mode function to calculate modes

void modeFunction (fstream &ansFile, fstream &contFile) {
    
    // resetting ans file and moving pointer back to top
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // counting the number of answers
    int answerFileCount=0;
    char answerData;
    while (ansFile >> answerData) {
        answerFileCount++;
    }
    
    // resetting ans file and moving pointer back to top
    
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // new array to hold the answer key data
    char *answer = nullptr;
    answer = new char [answerFileCount];
    for (int i=0; i<answerFileCount; i++) {
        ansFile >> *(answer+i);
    }
    
    // resetting ans file and moving pointer back to top
    
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // resetting contestant file and moving pointer back to top
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    // counting the number of the contestants
    string line1;
    int contCounter = 0;
    while (getline(contFile, line1)) {
        
        contCounter++;
    }
    
    // resetting contestant file and moving pointer back to top
    
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    
    
    string line;
    string finalLine;
    string name;
    
    // score array to hold score data
    double *score = nullptr;
    score = new double [contCounter];
    
    // test is the index for score array
    int test = 0;
    
    // for contestant data line
    char *contestant = nullptr;
    contestant = new char [answerFileCount];
    
    // for all the wrongly answered questions
    int *wrongNumber = nullptr;
    wrongNumber = new int [answerFileCount];
    
    // for all the correct answers
    char *correctAns = nullptr;
    correctAns = new char [answerFileCount];
    
    // for the user answers (contestants)
    char *userAnswer = nullptr;
    userAnswer = new char [answerFileCount];
    
    // getline to split the ID and cont answers
    while (getline(contFile, line)) {
        name = line.substr(0, 10);
        finalLine = line.substr(11, answerFileCount+answerFileCount-1);
        
        
        long long length = finalLine.length();
        
        // storing cont answers in contestant array
        int x=0;
        for (int i=0; i<length; i++) {
            if (!(finalLine.at(i) == ' ')) {
                
                *(contestant+x) = finalLine.at(i);
                x++;
                
            }
        }
        
        // counter variable for all the respective arrays
        int correctAnswer=0;
        int wrongNumberIndex=0;
        int userAnswerIndex=0;
        int correctAnswerIndex=0;
        
        // checking for correct answer
        for (int i=0; i<answerFileCount; i++) {
            if (*(answer+i) == *(contestant+i))
                correctAnswer++;
            
            // else wrong answer
            else {
                
                // assigns all wrong number questions to array and increments
                *(wrongNumber+wrongNumberIndex)=i+1;
                wrongNumberIndex++;
                
                // assigns user answers to array and increments
                *(userAnswer+userAnswerIndex)= *(contestant+i);
                userAnswerIndex++;
                
                // assigns correct answers for that specific question and increments
                *(correctAns+correctAnswerIndex) = *(answer+i);
                correctAnswerIndex++;
                
            }
        }
        
        
        // calculating score
        *(score+test) = (correctAnswer*100.00) / answerFileCount;
        test++;
    }
    
    // soring score arrays using swap function
    // if first element is greater than second then call swap function and sort
    
    for (int i=0; i<contCounter; i++) {
        for (int j=0; j<contCounter-i-1; j++) {
            if (*(score+j) >  *(score+j+1))
                swap(*(score+j), *(score+j+1));
        }
    }
    
    // mode array that will hold all mode values (1 mode or even more)
    double *modeArray = nullptr;
    modeArray = new double [100];
    
    // assign a variable to first value of the score to compare that with others
    double value = *(score+0);
    // bigCount = mode
    int bigCount = 1;
    int modeCount = -1;
    int modeCounter = 0;
   
    // if first value matches with second value increment bigCount
    for (int i=1; i<=contCounter; i++) {
        if (value == *(score+i)) {
            bigCount++;
        }
        // if not then go to else statement
        else {
            if (bigCount > modeCount) {
                if (modeCounter == 0) {
                    *(modeArray+0) = *(score+i-1);
                    modeCounter++;
                    modeCount = bigCount;
                }
                else {
                    delete[] modeArray;
                    modeArray = new double [100];
                    
                    modeCounter = 1;
                    *(modeArray+0) = *(score+i-1);
                    modeCount = bigCount;
                }
                bigCount = 1;
                
            }
            // if two values have the same mode
            else if (bigCount == modeCount) {
                *(modeArray+modeCounter) = *(score+i-1);
                modeCounter++;
                bigCount = 1;
            }
            value = *(score+i);
        }
        
        
    }
   
    // outputting mode
    // if its last mode then dont display comma else add comma and space
    
    cout << "Mode: ";
    for (int i=0; i<modeCounter; i++) {
        if (i == modeCounter-1)
            cout << *(modeArray+i)*1.00;
        else
            cout << *(modeArray+i)*1.00 << ", ";
    }
    
    cout << endl;
    
    // deleting all the dynamically created arrays
       delete[] answer;
       delete[] contestant;
       delete[] wrongNumber;
       delete[] correctAns;
       delete[] userAnswer;
       delete[] score;
    
}

// function to find out most missed questions

void mostMissedFunction(fstream &ansFile, fstream &contFile) {
    
    
    // reset ans file and move pointer to top of file
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // counting answer key
    int answerFileCount=0;
    char answerData;
    while (ansFile >> answerData) {
        answerFileCount++;
    }
    
    // reset ans file and move pointer to top of file
    ansFile.clear();
    ansFile.seekg(0, ios::beg);
    ansFile.seekp(0, ios::beg);
    
    // assigning answer key to answer array
    char *answer = nullptr;
    answer = new char [answerFileCount];
    for (int i=0; i<answerFileCount; i++) {
        ansFile >> *(answer+i);
    }
    
    // reset cont file and move pointer to top of file
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    // counting contestants
    string line1;
    int contCounter = 0;
    while (getline(contFile, line1)) {
        
        contCounter++;
    }
    
    // reset cont file and move pointer to top of file
    contFile.clear();
    contFile.seekg(0, ios::beg);
    contFile.seekp(0, ios::beg);
    
    
    
    string line;
    string finalLine;
    string name;
    
    // score array to hold scores
    double *score = nullptr;
    score = new double [contCounter];
    
    // calculate 60% of the total number of students
    double sixtyPercent = (0.6) * contCounter;
    
    // for wrong number questions
    int *wrongNumber = nullptr;
    wrongNumber = new int [answerFileCount];
    
    // missed questions array
    int *missedQuestions = nullptr;
    missedQuestions = new int [answerFileCount];
    
    // assigning 0s to all the values of the array
    // plan is to increment the values when there are wrong answers
    // if the wrong answer questions are 2 3 4 then this array will be 0 1 1 1
    // so we know how many times each question has been missed
    
    for (int i=0; i<answerFileCount; i++) {
        *(missedQuestions+i) = 0;
    }
    
    // array for contestant data
    char *contestant = nullptr;
    contestant = new char [answerFileCount];
    
    // array for correctAns
    char *correctAns = nullptr;
    correctAns = new char [answerFileCount];
    
    // array for userAnswer
    char *userAnswer = nullptr;
    userAnswer = new char [answerFileCount];
    
    // this is where we split the ID and contestant answer
    while (getline(contFile, line)) {
        name = line.substr(0, 10);
        finalLine = line.substr(11, answerFileCount+answerFileCount-1);
        
        
        long long length = finalLine.length();
        
        // assign contestant answers excluding whitespace
        int x=0;
        for (int i=0; i<length; i++) {
            if (!(finalLine.at(i) == ' ')) {
                
                *(contestant+x) = finalLine.at(i);
                x++;
            }
        }
        
        // counter variables for all the
        int correctAnswer=0;
        int wrongNumberIndex=0;
        int userAnswerIndex=0;
        int correctAnswerIndex=0;
        
        // checking if answer is correct
        for (int i=0; i<answerFileCount; i++) {
            if (*(answer+i) == *(contestant+i))
                correctAnswer++;
            // else wrong answer
            else {
                
                // assigning wrong numbers to array and incrementing
                *(wrongNumber+wrongNumberIndex)=i+1;
                wrongNumberIndex++;
                
                // assigning user answer and incrementing
                *(userAnswer+userAnswerIndex)= *(contestant+i);
                userAnswerIndex++;
                
                // assigning correct answer and incrementing
                *(correctAns+correctAnswerIndex) = *(answer+i);
                correctAnswerIndex++;
                
                
            }
        }
        
        // will hold a temp wrong Number until we assign it to missedQuestions array
        int temp;
        
        // looping through the wrongNumber array and incrementing the missedQuestions array based off wrong number
        
        for (int i=0; i < wrongNumberIndex; i++) {
            temp = *(wrongNumber+i);
            *(missedQuestions + temp - 1) = (*(missedQuestions+ temp - 1) + 1);
        }
    }
    
    cout << endl;
    
    // outputting most missed questions after comparing each element of the array with the sixtyPercent calculated in the beginning of the function
    
    cout << "MOST MISSED QUESTIONS" << endl;
    for (int i=0; i < answerFileCount; i++) {
        if (*(missedQuestions+i) >= sixtyPercent) {
            cout << (i+1) << "\t" << (*(missedQuestions+i)*100.00)/contCounter << "%" << endl;
        }
    }
    
    // deleting all the dynamically created arrays
    delete[] answer;
    delete[] contestant;
    delete[] wrongNumber;
    delete[] correctAns;
    delete[] userAnswer;
    delete[] score;
    delete[] missedQuestions;
    
}


int main() {
    
    // creating two fstreams for both the files
    fstream contFile;
    fstream ansFile;
    
    // strings to hold the user input
    string answerkeyFileName;
    string contestantFileName;
    
    // getting the input from user
    cin >> answerkeyFileName;
    cin >> contestantFileName;
    
    // opening the files
    ansFile.open(answerkeyFileName, ios::in);
    contFile.open(contestantFileName, ios::in);
    
    // checking if the answer file is opening (exists)
    if (ansFile.good()) {
        
        // checking if contFile is opening (exists)
        if (contFile.good()) {
        
        // calling all the required functions by passing in the fstreams
        
        answercheck(ansFile, contFile);
        meanFunction(ansFile, contFile);
        medianFunction(ansFile, contFile);
        modeFunction(ansFile, contFile);
        mostMissedFunction(ansFile, contFile);
            
        }
        
    }
    
    // closing files after outputting the report
    ansFile.close();
    contFile.close();
}
