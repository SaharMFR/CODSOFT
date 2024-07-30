#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

class Task {
    string name;
    string description;
    bool status;
public:
    Task(string n, string d, bool s) {
        name = n;
        description = d;
        status = s;
    }
    void setName(string newName) {
        name = newName;
    }
    void setDescription(string newDescription) {
        description = newDescription;
    }
    void setStatus(bool newStatus) {
        status = newStatus;
    }
    string getName() {
        return name;
    }
    string getDescription() {
        return description;
    }
    bool getStatus() {
        return status;
    }
    void view() {
        cout << "\n--------------------------\n"
        << "      " << name
        << "\n--------------------------\n"
        << description
        << " .\n\nStatus : ";
        if (status)
            cout << "Completed .\n";
        else
            cout << "Pending ..\n";
    }
};

class ToDo_List {
    vector<Task> tasks;
public:
    ToDo_List() {
        fstream database("Tasks.txt");
        string line, name, description = "";
        vector<string> allTasks;
        while (getline(database, line)) {
            allTasks.push_back(line);
        }
        for (int i = 0; i < allTasks.size(); i++) {
            if (i == 0 || allTasks[i - 1].empty()) {
                name = allTasks[i];
            } else if (!allTasks[i].empty()) {
                if (allTasks[i + 1].empty()) {
                    if (allTasks[i] == "Completed") {
                        tasks.push_back(Task(name, description, true));
                    } else {
                        tasks.push_back(Task(name, description, false));
                    }
                    description = "";
                } else {
                    if (!description.empty())
                        description += '\n';
                    description += allTasks[i];
                }
            }
        }
        database.close();
    }

//Studying Math
//Completing 4 units with 3 lessons each in algebra
//Completing 2 units with2 lessons each in geometry
//Pending
//
//Reading book
//Finish reading `Beauty and the beast` book
//Completed
//
//Watching movie
//Completing `Monsters at work` series
//Pending

    ~ToDo_List() {
        fstream database("Tasks.txt");
        for (Task task : tasks) {
            database << task.getName() << '\n' << task.getDescription() << '\n';
            if (task.getStatus())
                database << "Completed\n\n";
            else
                database << "Pending\n\n";
        }
        database.close();
    }

    vector<Task> getTasks() {
        return tasks;
    }

    void addTask(const Task& t) {
        tasks.push_back(t);
    }

    void viewTasks() {
        cout << "\n--------------------------------------------\n"
                "              Completed tasks"
                "\n--------------------------------------------\n";
        for (Task t : tasks) {
            if (t.getStatus())
                t.view();
        }
        cout << "\n--------------------------------------------\n"
                "              Uncompleted tasks"
                "\n--------------------------------------------\n";
        for (Task t : tasks) {
            if (!t.getStatus())
                t.view();
        }
        cout << "\n----------------------------------------\n";
    }

    int search(const string& taskName) {
        int i;
        for (i = 0; i < tasks.size(); i++) {
            if (tasks[i].getName() == taskName)
                break;
        }
        return i;
    }

    void markCompleted(int taskNumber) {
        tasks[taskNumber].setStatus(true);
    }

    void editTask(int i) {
        cout << "\n\nThe task :\n";
        tasks[i].view();
        int choice;
        bool validChoice = false;
        while (!validChoice) {
            cout << "\nDo you want to edit its :"
                    "\n( 1 ) Name ."
                    "\n( 2 ) Description ."
                    "\n( 3 ) Status ."
                    "\n\nEnter the number of your choice : ";
            cin >> choice;
            if (choice == -1) {
                validChoice = true;
            } else if (choice == 1) {
                validChoice = true;
                string name;
                cout << "\nEnter the new name : ";
                cin.ignore();
                getline(cin, name);
                if (name != "-1") {
                    tasks[i].setName(name);
                    cout << "\nThe name has been edited successfully ..\n";
                }
            } else if (choice == 2) {
                validChoice = true;
                string description;
                cout << "\nEnter the new description (no new lines) : ";
                cin.ignore();
                getline(cin, description);
//                cin.ignore();
                if (description != "-1") {
                    tasks[i].setDescription(description);
                    cout << "\nThe description has been edited successfully ..\n";
                }
            } else if (choice == 3) {
                validChoice = true;
                int status;
                bool validStatus = false;
                while (!validStatus) {
                    cout << "\n( 1 ) Completed ."
                            "\n( 2 ) Pending ."
                            "\n\nEnter the number of the new status : ";
                    cin >> status;
                    if (status != -1) {
                        if (status == 1) {
                            validStatus = true;
                            tasks[i].setStatus(true);
                            cout << "\nThe status has been edited successfully ..\n";
                        } else if (status == 2) {
                            validStatus = true;
                            tasks[i].setStatus(false);
                            cout << "\nThe status has been edited successfully ..\n";
                        } else {
                            cout << "\nInvalid choice :("
                                    "\nPlease, choose one of the displayed ..\n";
                        }
                    }
                }
            } else {
                cout << "\nInvalid choice :("
                        "\nPlease choose from the displayed choices only ..";
            }
        }
        cout << "\n\nThe new task :\n";
        tasks[i].view();
        cout << "\n-----------------------------\n";
    }

    void removeTask(int taskNumber) {
        vector<Task> newTasks;
        for (int i = 0; i < tasks.size(); i++) {
            if (i != taskNumber)
                newTasks.push_back(tasks[i]);
        }
        tasks[taskNumber].view();
        tasks = newTasks;
        cout << "\nThis task has been removed successfully ..\n";
    }
};

int main() {
    cout << "\n------------------------------------------------------\n"
            "              Welcome to my Task Manager"
            "\n------------------------------------------------------\n\n";
    cout << "\nNote :"
            "\n     You can back from any option by entering `-1` .\n\n";
    ToDo_List myList;
    bool quit = false;
    int choice;
    while (!quit) {
        cout << "\n------------------------------------------------------\n\n";
        bool validChoice = false;
        while (!validChoice) {
            cout << "\n( 1 ) Add new task ."
                    "\n( 2 ) View all tasks ."
                    "\n( 3 ) Mark existing task as completed ."
                    "\n( 4 ) Edit existing task ."
                    "\n( 5 ) Remove existing task ."
                    "\n( 6 ) Quit the task manager ."
                    "\n\nEnter the number of your choice : ";
            cin >> choice;
            if (choice == 1) {
                validChoice = true;
                string name, description, status;
                cout << "\nEnter the name of the new task : ";
                cin.ignore();
                getline(cin, name);
                if (name != "-1") {
                    cout << "\nEnter the content ( description ) of the new"
                            "\ntask : ";
//                    cin.ignore();
                    getline(cin, description);
//                    cin.ignore();
                    if (description != "-1") {
                        cout << "\nIs this task completed ? ";
                        cin >> status;
                        if (status != "-1") {
                            if (status == "yes" || status == "Yes" || status == "YES")
                                myList.addTask(Task(name, description, true));
                            else
                                myList.addTask(Task(name, description, false));
                            cout << "\nThe task has been added successfully ..\n\n";
                        }
                    }
                }
            } else if (choice == 2) {
                validChoice = true;
                myList.viewTasks();
            } else if (choice == 3) {
                validChoice = true;
                string name;
                cout << "\nEnter the name of the task you want to mark as completed"
                        "\n( Be careful about lowercase and uppercase letters )"
                        "\nIf you don't remember , you can view tasks first : ";
                cin.ignore();
                getline(cin, name);
                if (name != "-1") {
                    int taskNumber = myList.search(name);
                    myList.markCompleted(taskNumber);
                    cout << "\nThe task has been marked as completed successfully ..\n\n";
                }
            } else if (choice == 4) {
                validChoice = true;
                string name;
                cout << "\nEnter the name of the task you want to edit"
                        "\n( Be careful about lowercase and uppercase letters )"
                        "\nIf you don't remember , you can view tasks first : ";
                cin.ignore();
                getline(cin, name);
                if (name != "-1") {
                    int taskNumber = myList.search(name);
                    myList.editTask(taskNumber);
                }
            } else if (choice == 5) {
                validChoice = true;
                string name;
                cout << "\nEnter the name of the task you want to remove"
                        "\n( Be careful about lowercase and uppercase letters )"
                        "\nIf you don't remember , you can view tasks first : ";
                cin.ignore();
                getline(cin, name);
                if (name != "-1") {
                    int taskNumber = myList.search(name);
                    myList.removeTask(taskNumber);
                }
            } else if (choice == 6) {
                validChoice = true;
                quit = true;
                cout << "\nThank you for using my task manager :)"
                        "\nI hope this is not the last time .. Bye\n\n";
            } else {
                cout << "\nInvalid choice :("
                        "\nPlease choose one of the displayed option ..\n\n";
            }
        }
    }

//    fstream file;
//    file.open("Tasks.txt");
//    string line;
//    while (getline(file, line))
//        cout << line;

    return 0;
}
