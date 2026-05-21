#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// Base Class using runtime polymorphism
class Task {
protected:
    std::string name;
public:
    Task(std::string t_name) : name(std::move(t_name)) {}
    virtual ~Task() = default; // Essential for correct cleanup of derived objects

    // Pure virtual function makes this an abstract class
    virtual void execute() const = 0; 
    
    std::string getName() const { return name; }
};

// Derived Class 1
class DownloadTask : public Task {
    std::string url;
public:
    DownloadTask(std::string t_name, std::string t_url) 
        : Task(std::move(t_name)), url(std::move(t_url)) {}

    void execute() const override {
        std::cout << "[Downloading] " << name << " from " << url << "...\n";
    }
};

// Derived Class 2
class ComputeTask : public Task {
    int complexity;
public:
    ComputeTask(std::string t_name, int t_comp) 
        : Task(std::move(t_name)), complexity(t_comp) {}

    void execute() const override {
        std::cout << "[Computing] " << name << " with intensity level: " << complexity << "\n";
    }
};

int main() {
    // A vector holding safe, automatically managed unique pointers to Task objects
    std::vector<std::unique_ptr<Task>> taskQueue;

    // Populating the queue dynamically
    taskQueue.push_back(std::make_unique<DownloadTask>("Dataset_A", "https://example.com/data.zip"));
    taskQueue.push_back(std::make_unique<ComputeTask>("Matrix_Factorization", 9));
    taskQueue.push_back(std::make_unique<DownloadTask>("Config_File", "https://example.com/config.json"));

    std::cout << "--- Executing Tasks via Polymorphism ---\n";
    for (const auto& task : taskQueue) {
        task->execute(); // Resolves at runtime to the correct derived class method
    }

    std::cout << "\n--- Filtering Tasks using Lambdas ---\n";
    // Using std::any_of with a lambda expression to search for a specific task name
    std::string searchName = "Matrix_Factorization";
    bool found = std::any_of(taskQueue.begin(), taskQueue.end(), [&searchName](const auto& task) {
        return task->getName() == searchName;
    });

    std::cout << "Is '" << searchName << "' in the queue? " << (found ? "Yes" : "No") << "\n";

    return 0; // Vector goes out of scope here, and std::unique_ptr automatically deallocates the memory!
}