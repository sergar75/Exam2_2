#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <windows.h>

class Transaction {
public:
    std::string category;
    double amount;
    time_t timestamp;

    Transaction(const std::string& category, double amount, time_t timestamp) :
        category(category), amount(amount), timestamp(timestamp) {}
};

class Wallet {
public:
    std::string name;
    double balance;
    std::vector<Transaction> transactions;

    Wallet(const std::string& name) : name(name), balance(0) {}

    void deposit(double amount) {
        balance += amount;
    }

    void spend(const std::string& category, double amount, time_t timestamp) {
        if (balance >= amount) {
            balance -= amount;
            transactions.emplace_back(category, amount, timestamp);
        }
        else {
            std::cout << "Недостаточно средств в " << name << " кошельке" << std::endl;
        }
    }
};

class FinanceManager {
private:
    std::vector<Wallet> wallets;
public:
    void addWallet(const std::string& name) {
        wallets.emplace_back(name);
    }

    Wallet* getWallet(const std::string& name) {
        for (auto& wallet : wallets) {
            if (wallet.name == name) {
                return &wallet;
            }
        }
        return nullptr;
    }

    void generateReport(const std::time_t& period, const std::string& reportType) {
        std::tm timeInfo;
        if (localtime_s(&timeInfo, &period) != 0) {
            std::cerr << "Error parsing time." << std::endl;
            return;
        }

        for (const auto& wallet : wallets) {
            std::cout << "Кошелек: " << wallet.name << std::endl;
            for (const auto& transaction : wallet.transactions) {
                std::tm transactionTimeInfo;
                if (localtime_s(&transactionTimeInfo, &transaction.timestamp) != 0) {
                    std::cerr << "Error parsing transaction time." << std::endl;
                    continue;
                }

                if (reportType == "day" && timeInfo.tm_mday == transactionTimeInfo.tm_mday &&
                    timeInfo.tm_mon == transactionTimeInfo.tm_mon && timeInfo.tm_year == transactionTimeInfo.tm_year) {
                    std::cout << "Категория: " << transaction.category << ", Сумма: " << transaction.amount << std::endl;
                }
                else if (reportType == "week" && timeInfo.tm_yday / 7 == transactionTimeInfo.tm_yday / 7 &&
                    timeInfo.tm_year == transactionTimeInfo.tm_year) {
                    std::cout << "Категория: " << transaction.category << ", Сумма: " << transaction.amount << std::endl;
                }
                else if (reportType == "month" && timeInfo.tm_mon == transactionTimeInfo.tm_mon &&
                    timeInfo.tm_year == transactionTimeInfo.tm_year) {
                    std::cout << "Категория: " << transaction.category << ", Сумма: " << transaction.amount << std::endl;
                }
            }
        }
    }

    void generateExpenseRanking() {
        for (auto& wallet : wallets) {
            std::sort(wallet.transactions.begin(), wallet.transactions.end(),
                [](const Transaction& t1, const Transaction& t2) {
                return t1.amount > t2.amount;
                });
            std::cout << "Toп 3 категорий расходов в " << wallet.name << ":" << std::endl;
            int count = 0;
            for (const auto& transaction : wallet.transactions) {
                if (count < 3) {
                    std::cout << "Категория: " << transaction.category << ", Сумма: " << transaction.amount << std::endl;
                    count++;
                }
                else {
                    break;
                }
            }
        }
    }

    void saveReportsToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& wallet : wallets) {
                file << "Кошелек: " << wallet.name << std::endl;
                for (const auto& transaction : wallet.transactions) {
                    file << "Категория: " << transaction.category << ", Сумма: " << transaction.amount << std::endl;
                }
            }
            file.close();
            std::cout << "Отчеты записаны в файл: " << filename << std::endl;
        }
        else {
            std::cout << "Не удается открыть файл для сохранения отчетов" << std::endl;
        }
    }
};

int main() {
    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    FinanceManager manager;
    manager.addWallet("Wallet1");
    manager.addWallet("Wallet2");

    std::string transactionDate1 = "2023-10-15";
    std::string transactionDate2 = "2023-10-20";
    std::string transactionDate3 = "2023-10-25";
    std::string transactionDate4 = "2023-11-25";
    std::string transactionDate5 = "2023-10-22";
    std::string transactionDate6 = "2023-10-21";
    
    /*std::string transactionDate1;
    std::string transactionDate2;
    std::string transactionDate3;
    std::string transactionDate4;
    std::string transactionDate5;
    std::string transactionDate6;*/

    // можно использовать getline()
    /*std::cout << "Введите 3 даты транзакций для Кошелька1 в формате ГГГГ-ММ-ДД:" << std::endl;
    std::cin >> transactionDate1;
    std::cin >> transactionDate2;
    std::cin >> transactionDate3;
    std::cout << "Введите 3 даты транзакций для Кошелька2 в формате ГГГГ-ММ-ДД:" << std::endl;
    std::cin >> transactionDate4;
    std::cin >> transactionDate5;
    std::cin >> transactionDate6;*/


    std::tm tm1 = {};
    std::tm tm2 = {};
    std::tm tm3 = {};
    std::tm tm4 = {};
    std::tm tm5 = {};
    std::tm tm6 = {};

    std::istringstream ss1(transactionDate1);
    ss1 >> std::get_time(&tm1, "%Y-%m-%d");
    std::time_t transactionTime1 = std::mktime(&tm1);

    std::istringstream ss2(transactionDate2);
    ss2 >> std::get_time(&tm2, "%Y-%m-%d");
    std::time_t transactionTime2 = std::mktime(&tm2);

    std::istringstream ss3(transactionDate3);
    ss3 >> std::get_time(&tm3, "%Y-%m-%d");
    std::time_t transactionTime3 = std::mktime(&tm3);

    std::istringstream ss4(transactionDate4);
    ss4 >> std::get_time(&tm4, "%Y-%m-%d");
    std::time_t transactionTime4 = std::mktime(&tm4);

    std::istringstream ss5(transactionDate5);
    ss5 >> std::get_time(&tm5, "%Y-%m-%d");
    std::time_t transactionTime5 = std::mktime(&tm5);

    std::istringstream ss6(transactionDate6);
    ss6 >> std::get_time(&tm6, "%Y-%m-%d");
    std::time_t transactionTime6 = std::mktime(&tm6);

    Wallet* wallet1 = manager.getWallet("Wallet1");
    Wallet* wallet2 = manager.getWallet("Wallet2");

    if (wallet1 && wallet2) {
        wallet1->deposit(1500);
        wallet1->spend("Еда", 100, transactionTime1);
        wallet1->spend("Транспорт", 50, transactionTime1);
        wallet1->spend("Обучение", 250, transactionTime2);
        wallet1->spend("Интернет", 500, transactionTime3);

        wallet2->deposit(2000);
        /*wallet2->spend("Одежда", 200, transactionTime3);
        wallet2->spend("Развлечения", 150, transactionTime3);*/
        wallet2->spend("Обучение", 150, transactionTime4);
        wallet2->spend("Интернет", 250, transactionTime5);
        wallet2->spend("Отдых", 150, transactionTime6);

        std::time_t currentTime = time(nullptr);

        manager.generateReport(transactionTime1, "day"); // Generate report for Wallet1 on the specified day
        std::cout << "-------------------------------------------" << std::endl;

        manager.generateReport(transactionTime4, "week"); // Generate report for Wallet2 on the specified week
        std::cout << "-------------------------------------------" << std::endl;
        
        manager.generateReport(transactionTime5, "month"); // Generate report for Wallet2 on the specified month
        std::cout << "-------------------------------------------" << std::endl;
        
        manager.generateExpenseRanking(); // Generate expense ranking for all wallets
        std::cout << "-------------------------------------------" << std::endl;
        
        manager.saveReportsToFile("finance_reports.txt"); // Save reports to file
    }

    
}



