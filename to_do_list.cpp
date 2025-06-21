#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Task {
public:
    string description;
    bool completed;

    Task(string desc, bool status = false) {
        description = desc;
        completed = status;
    }

    void markCompleted() {
        completed = true;
    }

    void displayTask(int index) const {
        cout << index << ". " << description 
             << (completed ? " [Completed]" : " [Pending]") << endl;
    }

    string formatForFile() const {
        return description + "|" + (completed ? "1" : "0") + "\n";
    }
};

class ToDoList {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    ToDoList() {
        loadFromFile();
    }

    void addTask() {
        string desc;
        cout << "Enter task description: ";
        cin.ignore();
        getline(cin, desc);
        tasks.push_back(Task(desc));
        cout << "Task added successfully!\n";
        saveToFile();
    }

    void displayTasks() const {
        cout << "\nTo-Do List:\n";
        if (tasks.empty()) {
            cout << "No tasks available.\n";
            return;
        }
        for (size_t i = 0; i < tasks.size(); ++i) {
            tasks[i].displayTask(i + 1);
        }
    }

    void completeTask() {
        displayTasks();
        if (tasks.empty()) return;

        int index;
        cout << "Enter task number to mark as completed: ";
        cin >> index;

        if (index > 0 && index <= tasks.size()) {
            tasks[index - 1].markCompleted();
            cout << "Task marked as completed!\n";
            saveToFile();
        } else {
            cout << "Invalid task number!\n";
        }
    }

    void deleteTask() {
        displayTasks();
        if (tasks.empty()) return;

        int index;
        cout << "Enter task number to delete: ";
        cin >> index;

        if (index > 0 && index <= tasks.size()) {
            tasks.erase(tasks.begin() + index - 1);
            cout << "Task deleted successfully!\n";
            saveToFile();
        } else {
            cout << "Invalid task number!\n";
        }
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving tasks to file!\n";
            return;
        }
        for (const Task& task : tasks) {
            file << task.formatForFile();
        }
        file.close();
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;

        string line, desc;
        bool status;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                desc = line.substr(0, pos);
                status = (line.substr(pos + 1) == "1");
                tasks.push_back(Task(desc, status));
            }
        }
        file.close();
    }
};

int main() {
    ToDoList todo;
    int choice;

    while (true) {
        cout << "\nTo-Do List Manager\n";
        cout << "1. View Tasks\n2. Add Task\n3. Complete Task\n4. Delete Task\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: todo.displayTasks(); break;
            case 2: todo.addTask(); break;
            case 3: todo.completeTask(); break;
            case 4: todo.deleteTask(); break;
            case 5: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}