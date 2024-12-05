#include <iostream>
#include <vector>
#include <string> // Handles Names
#include <iomanip> // Formats output
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Base class 'Citizen' is an abstract class with pure virtual functions for entering 
// and displaying details, which must be implemented by derived classes.
class Citizen{
public:
    virtual void enterDetails() = 0;  // Pure virtual function to enter details
    virtual void displayDetails() = 0; // Pure virtual function to display details
    virtual ~Citizen() {} // Virtual destructor
};

////////////////////////////////////////////////////////////////////////////////////////
// Derived class 'Questions' from 'Citizen'. This class manages the questions and responses.
class Questions : public virtual Citizen{
public:
    string name, phone;
    int age, ID, salary, bonus;

    // List of questions to ask the user
    vector<string> questions = {
        "1. Rate the damage done to your home (1 = Minor damage, 10 = Completely destroyed): ",
        "2. Rate the length of time you experienced loss of Power (1 = Less than 1 day, 10 = More than 7 days): ",
        "3. Rate the length of time you experienced loss of Internet (1 = Less than 1 day, 10 = More than 7 days): ",
        "4. Rate the length of time you experienced loss of Water (1 = Less than 1 day, 10 = More than 7 days): ",
        "5. Rate your food supply (1 = No food, 10 = Excess food): ",
        "6. Rate how safe you currently feel in your neighborhood (1 = Very unsafe, 10 = Very safe): ",
        "7. Rate your physical condition (1 = Safe, 10 = Critical condition): ",
        "8. How would you rate your access to medical care after the hurricane (1 = No access, 10 = Full access): ",
        "9. How would you rate the amount of support you received from the community and government (1 = None, 10 = Full support): ",
        "10. Estimate your monetary loss/damage (in dollars): $"};

    vector<int> responses; // Stores user responses to questions

    // Function to enter survey details
    void enterDetails() override {
        int response;
        cout << "Please answer the following 10 questions:" << endl;

        for (size_t i = 0; i < questions.size(); ++i) {
            cout << questions[i];
            cin >> response;

            // Validate input for questions 1-9 to ensure answers are between 1 and 10
            if (i < 9) {
                while (cin.fail() || response < 1 || response > 10) {
                    cin.clear();  // Clear error state
                    cin.ignore(); // Ignore incorrect input
                    cout << "Please enter a number between 1 and 10: ";
                    cin >> response;
                }
            } else { // For question 10 (monetary loss), allow non-negative values
                while (cin.fail() || response < 0) {
                    cin.clear();  // Clear error state
                    cin.ignore(); // Ignore incorrect input
                    cout << "Please enter a valid non-negative number for monetary loss: ";
                    cin >> response;
                }
            }

            responses.push_back(response); // Store the validated response
        }
    }

    const vector<int>& getResponses() const{
        return responses;} // Return the responses

    string getName() const{
        return name;} // Return the name of the citizen

    // Function to display details (e.g., salary, bonus) for a specific person
    void displayDetails() override{
        cout << "Salary: $" << salary << endl;
        cout << "Bonus: $" << bonus << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////
// 'User' class is a derived class from 'Questions' that adds more personal details
class User : public Questions {
private:
    string fname, lname;  // First and last name
    string workPlace;     // Workplace name (if first responder)
    string designation;   // Designation (if first responder)
    string countyName;    // County the user resides in
    string choice;        // Whether the user is a first responder (y/n)
    int household;        // Number of people in the household
    int county;           // County selection number
    int age;              // User's age

public:
    User() : fname(""), lname(""), age(0), county(0), household(0), designation("") {}

    // Function to enter user-specific details
    void enterDetails() override {
    bool validAge = false;
    while (!validAge) {
        cout << "Enter Your First Name: ";
        cin >> fname;
        cout << "Enter Your Last Name: ";
        cin >> lname;
        cout << "Enter Your Age: ";
        cin >> age;

        if (age > 17 && age < 99) {
            validAge = true; // Valid age entered, exit loop
        } else {
            cout << "//This Survey is available only to participants ages 18 - 99.//" << endl;
        }
    }

    // County selection with error checking
    bool validCounty = false;
    while (!validCounty) {
        cout << "\nFrom the list below, select the county you live in." << endl;
        cout << "1. Lee\n2. Collier\n3. Glades\n4. Hendry\n5. Charlotte\nSelection: ";
        cin >> county;

        if (cin.fail()) {
            // Handle non-numeric input (e.g., if the user enters a letter)
            cin.clear(); // Clear error flag
            cin.ignore(); // Ignore invalid input
            cout << "Invalid input! Please enter a number between 1 and 5." << endl;
        } else if (county >= 1 && county <= 5) {
            validCounty = true; // Valid county selected
            // Assign county name based on selection
            switch (county) {
                case 1: countyName = "Lee"; break;
                case 2: countyName = "Collier"; break;
                case 3: countyName = "Glades"; break;
                case 4: countyName = "Hendry"; break;
                case 5: countyName = "Charlotte"; break;
            }
        } else {
            cout << "Invalid selection! Please choose a number between 1 and 5." << endl;
        }
    }

    // First responder choice with validation
    redo2:
    cout << "Are you a first responder? (y/n): ";
    cin >> choice;

    if (choice == "y") {
        cout << "Enter Designation: ";
        cin.ignore(); // Ignore newline left by previous input
        getline(cin, designation);
        cout << "Enter Name of Workplace: ";
        getline(cin, workPlace);
    } else if (choice == "n") {
        designation = "N/A";
        workPlace = "N/A";
        cout << "/////No Hurricane Work Recorded/////" << endl;
    } else {
        cout << "Invalid Choice!!!" << endl;
        goto redo2; // Prompt again if invalid input
    }

    // Household size input
    cout << "State the number of people in your household (including yourself): ";
    cin >> household;

    // Ensure the household number is valid
    while (cin.fail() || household <= 0) {
        cout << "Invalid number! Please enter a valid number for your household size: ";
        cin.clear();
        cin.ignore(); // Ignore invalid input
        cin >> household;
    }

    Questions::enterDetails(); // Call the base class method for further questions
}


    // Function to display user details along with their responses
    void displayDetails(int userIndex) const{
        vector<string> conditions = {
        "1. Damage to home: ",
        "2. Length of time without power: ",
        "3. Length of time without internet: ",
        "4. Length of time without water: ",
        "5. Quantity of food for household: ",
        "6. Necessity for supplies (Lighters, Gas, Household, etc.): ",
        "7. Survey participant's physical health: ",
        "8. Household medical attention: ",
        "9. Assets lost during hurricane: ",
        "10. Give an estimate of your monetary loss/damage: $"};

        cout<<"\nUser "<<(userIndex + 1)<<": "<<fname<<" "<<lname<<", Age: "<<age<<endl;
        cout<<"County: "<<countyName<<", Household Size: "<<household<<endl;
        cout<<"First Responder Designation: "<<designation<<", Workplace: "<<workPlace<<endl;
        cout<<"Answers On A 1-10 Scale: \n";
        for(int i = 0; i < 10; ++i){
            cout<<conditions[i]<<responses[i]<<endl;} // Display all user responses
        cout<<endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////
// Main program logic
int main(){
    vector<User> users;  // Vector to store users' data
    double average[10];  // Array to store average results for each question
    int numQuestions = 10; // Number of survey questions
    int numUsers = 0; // Number of users participating in the survey
    int choice; // User choice from menu options

    cout<<"----------------Welcome to the Hurricane Relief Survey----------------"<<endl;

    do{
        cout<<"-----------------Select an Option from the List Below-----------------"<<endl;
        cout<<"1. Begin The Survey Loop."<<endl;
        cout<<"2. View Individual Survey Results."<<endl;
        cout<<"3. View Combined Survey Results."<<endl;
        cout<<"4. End The Program."<<endl;
        redo:cout<<"\nSelection: ";
        cin>>choice;

        switch(choice){
            case 1:
                cout<<"Enter the number of users participating in this survey today: ";
                cin>>numUsers;
                users.resize(numUsers); // Resize the user vector to hold the number of users

                // Enter details for each user
                for(int i = 0; i < numUsers; ++i){
                    cout<<"\nEnter details for User "<<(i + 1)<<endl;
                    users[i].enterDetails();}
                break;

            case 2:
                if(numUsers == 0){
                    cout<<"No results available! Please take the survey to generate results."<<endl<<endl;}
                else{
                    cout<<"-----------------------------Survey Results---------------------------"<<endl;
                    // Display details of all users
                    for(int i = 0; i < numUsers; ++i){
                        users[i].displayDetails(i);}}  
                break;

            case 3:
                if(numUsers == 0){
                    cout<<"No results available! Please take the survey to generate results."<<endl<<endl;}
                else{
                    cout<<"--------------------Combined Results and Totals-----------------------"<<endl;
                    // Calculate average for each question
                    for(int j = 0; j < numQuestions; j++){
                        int sum = 0;

                        for (int k = 0; k < numUsers; k++){
                            sum += users[k].getResponses()[j];}  // Sum responses for the current question
                        average[j] = static_cast<double>(sum) / numUsers;} // Calculate average for each question

                    // Display the average for each question
                    cout<< fixed << setprecision(2);
                    cout<< "Average for Home Damage: "<<average[0]<<endl;
                    cout<< "Average for Power Loss Time: "<<average[1]<<endl;
                    cout<< "Average for Internet Loss Time: "<<average[2]<<endl;
                    cout<< "Average for Water Loss Time: "<<average[3]<<endl;
                    cout<< "Average for Food Supply: "<<average[4]<<endl;
                    cout<< "Average for Security: "<<average[5]<<endl;
                    cout<< "Average for Physical Condition: "<<average[6]<<endl;
                    cout<< "Average for Medical Care Access: "<<average[7]<<endl;
                    cout<< "Average for Support Received: "<<average[8]<<endl;
                    cout<< "Average for Financial Loss: "<<average[9]<<endl;}
                break;

            case 4:
                cout<<"Thank you for using the program."<<endl;
                break;

            default:
                cout<<"That is an Invalid Input."<<endl;
                goto redo;} // Invalid input handling
    } while (choice != 4); // Exit loop when user selects option 4
    return 0;} // End of main function
