// ==========================================================================
//  Тема 15. Телекомуникационен оператор
//  Скелет за курсов проект по C++ - дописва се на местата с TODO.
//
//  Предплатени и абонаментни планове с месечно таксуване.
//
//  Задължително: валидация на данните, конструктор по подразбиране,
//  конструктор с параметри, копиращ конструктор и деструктор,
//  статичен елемент, наследяване, виртуални методи, аритметичен
//  оператор и оператор <<.
// ==========================================================================
#ifndef TEMA15_TELEKOM_H
#define TEMA15_TELEKOM_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// --------------------------------------------------------------------------
//  Помощни функции за валидация (реализация в .cpp)
// --------------------------------------------------------------------------
bool IsValidText(const std::string& s);                   // TODO: само букви, 3-50 знака
bool IsValidNumber(double x);                             // TODO: строго положително число
bool IsInRange(double x, double lo, double hi);           // TODO: проверка за обхват

// --------------------------------------------------------------------------
//  Bundle - помощен клас - пакет
// --------------------------------------------------------------------------
class Bundle {
private:
    std::string name;                                         // TODO
    int minutes;                                              // TODO
    int dataMB;                                               // TODO
    double price;                                             // TODO

public:
    // --- конструктори и деструктор ---
    Bundle();                                                 // TODO: конструктор по подразбиране
    // TODO: валидация на всички данни
    Bundle(const std::string& name, int minutes, int dataMB, double price);
    Bundle(const Bundle& other);                              // TODO: копиращ конструктор
    ~Bundle();                                                // TODO: освобождаване и броячи

    // --- гетери и сетери ---
    // TODO: напишете гетери и сетери с валидация за всички полета
std::string getName() const;
int getMinutes() const;
int getDataMB() const;
double getPrice() const;

void setName(std::string name);
void setMinutes(int minutes);
void setDataMB(int dataMB);
void setPrice(double price);

    // --- предефинирани оператори ---
    friend std::ostream& operator<<(std::ostream& out,        // TODO: извеждане на обекта
                                    const Bundle& obj);
};

// --------------------------------------------------------------------------
//  Subscription - базов клас
// --------------------------------------------------------------------------
class Subscription {
protected:
    std::string phoneNumber;                                  // TODO: 10 цифри
    std::string owner;                                        // TODO: само букви
    double monthlyFee;                                        // TODO: положително
    int minutes;                                              // TODO
    int dataMB;                                               // TODO
    int usedMinutes;                                          // TODO
    int usedData;                                             // TODO

    // --- статични полета (инициализират се в .cpp) ---
    static int subscribersCount;                              // TODO
    static double pricePerExtraMinute;                        // TODO: обща за всички планове

public:
    // --- конструктори и деструктор ---
    Subscription();                                           // TODO: конструктор по подразбиране
    // TODO: валидация на всички данни
    Subscription(const std::string& number, const std::string& owner, double fee, int minutes, int dataMB);
    Subscription(const Subscription& other);                  // TODO: копиращ конструктор
    virtual ~Subscription();                                  // TODO: освобождаване и броячи

    // --- гетери и сетери ---
    // TODO: напишете гетери и сетери с валидация за всички полета
std::string getPhoneNumber() const;
std::string getOwner() const;
double getMonthlyFee() const;
int getMinutes() const;
int getDataMB() const;

void setPhoneNumber(const std::string& phoneNumber);
void setOwner(const std::string& owner);
void setMonthlyFee(double fee);
void setMinutes(int minutes);
void setDataMB(int dataMB);

    // --- методи ---
    void Call(int minutes);                                   // TODO: проверка на остатъка
    void UseData(int mb);                                     // TODO
    virtual double Bill() const;                              // TODO
    void Renew();                                             // TODO
    bool IsActive() const;                                    // TODO
    virtual void Print() const;                               // TODO

    // --- статични методи ---
    static void OperatorReport();                             // TODO

    // --- предефинирани оператори ---
    Subscription& operator+(const Bundle& b);                 // TODO: добавя пакет минути и данни
    friend std::ostream& operator<<(std::ostream& out,        // TODO: извеждане на обекта
                                    const Subscription& obj);
};

// --------------------------------------------------------------------------
//  PrepaidPlan - предплатен план
// --------------------------------------------------------------------------
class PrepaidPlan : public Subscription {
private:
    double credit;                                            // TODO: наличен кредит

public:
    // --- конструктори и деструктор ---
    PrepaidPlan();                                            // TODO: конструктор по подразбиране
    // TODO: валидация на всички данни
    PrepaidPlan(const std::string& number, const std::string& owner, double fee, int minutes, int dataMB, double credit);
    PrepaidPlan(const PrepaidPlan& other);                    // TODO: копиращ конструктор
    virtual ~PrepaidPlan();                                   // TODO: освобождаване и броячи

    // --- гетери и сетери ---
    // TODO: напишете гетери и сетери с валидация за всички полета
double getCredit() const;
void setCredit(double credit);

    // --- методи ---
    void AddCredit(double amount);                            // TODO
    double Bill() const override;                             // TODO
    void Print() const override;                              // TODO

    // --- предефинирани оператори ---
    friend std::ostream& operator<<(std::ostream& out,        // TODO: извеждане на обекта
                                    const PrepaidPlan& obj);
};

// --------------------------------------------------------------------------
//  PostpaidPlan - абонаментен план
// --------------------------------------------------------------------------
class PostpaidPlan : public Subscription {
private:
    int contractMonths;                                       // TODO
    double overuse;                                           // TODO: надхвърляне на пакета

public:
    // --- конструктори и деструктор ---
    PostpaidPlan();                                           // TODO: конструктор по подразбиране
    // TODO: валидация на всички данни
    PostpaidPlan(const std::string& number, const std::string& owner, double fee, int minutes, int dataMB, int contractMonths);
    PostpaidPlan(const PostpaidPlan& other);                  // TODO: копиращ конструктор
    virtual ~PostpaidPlan();                                  // TODO: освобождаване и броячи

    // --- гетери и сетери ---
    // TODO: напишете гетери и сетери с валидация за всички полета
int getContractMonths() const;
void setContractMonths(int months);

    // --- методи ---
    double Bill() const override;                             // TODO: пакет + надхвърляне
    void Print() const override;                              // TODO

    // --- предефинирани оператори ---
    friend std::ostream& operator<<(std::ostream& out,        // TODO: извеждане на обекта
                                    const PostpaidPlan& obj);
};

// --------------------------------------------------------------------------
//  TODO (main.cpp): разговори и данни, добавяне на пакети с +, месечни фактури.
// --------------------------------------------------------------------------

#endif // TEMA15_TELEKOM_H
