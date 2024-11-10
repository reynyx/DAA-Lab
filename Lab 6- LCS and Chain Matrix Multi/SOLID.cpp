#include <iostream>
#include <string>
#include <vector>
#include <memory>

// === 1. Single Responsibility Principle (SRP) ===
class User {
public:
    std::string name;
    int age;

    User(const std::string& name, int age) : name(name), age(age) {}
};

class FileManager {
public:
    static void saveUser(const User& user) {
        // Code to save user data to a file (example)
        std::cout << "Saving user " << user.name << " to file.\n";
    }
};

// === 2. Open-Closed Principle (OCP) ===
class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return 3.14 * radius * radius;
    }
};

// === 3. Liskov Substitution Principle (LSP) ===
class BaseRectangle {
protected:
    double width, height;
public:
    virtual void setWidth(double w) { width = w; }
    virtual void setHeight(double h) { height = h; }
    virtual double area() const { return width * height; }
};

class Square : public BaseRectangle {
public:
    void setWidth(double w) override {
        width = height = w;
    }
    void setHeight(double h) override {
        width = height = h;
    }
};

// === 4. Interface Segregation Principle (ISP) ===
class Printer {
public:
    virtual void print() = 0;
    virtual ~Printer() = default;
};

class Scanner {
public:
    virtual void scan() = 0;
    virtual ~Scanner() = default;
};

// === 5. Dependency Inversion Principle (DIP) ===
class IEmailService {
public:
    virtual void sendEmail(const std::string& message) = 0;
    virtual ~IEmailService() = default;
};

class SmtpEmailService : public IEmailService {
public:
    void sendEmail(const std::string& message) override {
        // Code to send email (example)
        std::cout << "Sending email: " << message << "\n";
    }
};

class EmailSender {
private:
    IEmailService* emailService;
public:
    EmailSender(IEmailService* service) : emailService(service) {}

    void send(const std::string& message) {
        emailService->sendEmail(message);
    }
};

// === Main Function to Demonstrate All Principles ===
int main() {
    // Single Responsibility Principle (SRP)
    User user("Alice", 30);
    FileManager::saveUser(user);

    // Open-Closed Principle (OCP)
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::unique_ptr<Shape>(new Rectangle(5.0, 3.0)));
    shapes.push_back(std::unique_ptr<Shape>(new Circle(2.0)));

    for (const auto& shape : shapes) {
        std::cout << "Area: " << shape->area() << "\n";
    }

    // Liskov Substitution Principle (LSP)
    BaseRectangle* rect = new BaseRectangle();
    rect->setWidth(4.0);
    rect->setHeight(5.0);
    std::cout << "Rectangle area: " << rect->area() << "\n";
    delete rect;

    // Dependency Inversion Principle (DIP)
    SmtpEmailService smtpService;
    EmailSender emailSender(&smtpService);
    