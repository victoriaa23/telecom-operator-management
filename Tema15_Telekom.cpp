#include "Tema15_Telekom.h"
#include <cctype>

using namespace std;

bool IsValidText(const string& s)
{
    if (s.length() < 3 || s.length() > 50)
        return false;

    for (char c : s)
    {
        if (!isalpha(c))
            return false;
    }

    return true;
}

bool IsValidNumber(double x)
{
    return x > 0;
}

bool IsInRange(double x, double lo, double hi)
{
    return x >= lo && x <= hi;
}

int Subscription::subscribersCount = 0;
double Subscription::pricePerExtraMinute = 0.35;

// ==================================================
// Bundle
// ==================================================

Bundle::Bundle()
{
    name = "Default";
    minutes = 0;
    dataMB = 0;
    price = 0;
}

Bundle::Bundle(const string& name,
    int minutes,
    int dataMB,
    double price)
{
    if (!IsValidText(name))
        throw invalid_argument("Invalid bundle name");

    if (minutes < 0)
        throw invalid_argument("Invalid minutes");

    if (dataMB < 0)
        throw invalid_argument("Invalid data");

    if (price < 0)
        throw invalid_argument("Invalid price");

    this->name = name;
    this->minutes = minutes;
    this->dataMB = dataMB;
    this->price = price;
}
Bundle::Bundle(const Bundle& other)
{
    name = other.name;
    minutes = other.minutes;
    dataMB = other.dataMB;
    price = other.price;
}
Bundle::~Bundle()
{
}
string Bundle::getName() const
{
    return name;
}

int Bundle::getMinutes() const
{
    return minutes;
}

int Bundle::getDataMB() const
{
    return dataMB;
}

double Bundle::getPrice() const
{
    return price;
}
void Bundle::setName(string name)
{
    if (!IsValidText(name))
        throw invalid_argument("Invalid name");

    this->name = name;
}

void Bundle::setMinutes(int minutes)
{
    if (minutes < 0)
        throw invalid_argument("Invalid minutes");

    this->minutes = minutes;
}

void Bundle::setDataMB(int dataMB)
{
    if (dataMB < 0)
        throw invalid_argument("Invalid data");

    this->dataMB = dataMB;
}

void Bundle::setPrice(double price)
{
    if (price < 0)
        throw invalid_argument("Invalid price");

    this->price = price;
}
ostream& operator<<(ostream& out,
    const Bundle& obj)
{
    out << "Bundle: " << obj.name
        << " Minutes: " << obj.minutes
        << " Data: " << obj.dataMB
        << " Price: " << obj.price;

    return out;
}

// ==================================================
// Subscription
// ==================================================

Subscription::Subscription()
{
    phoneNumber = "0880000000";
    owner = "Default";
    monthlyFee = 10;

    minutes = 0;
    dataMB = 0;

    usedMinutes = 0;
    usedData = 0;

    subscribersCount++;
}
Subscription::Subscription(
    const string& number,
    const string& owner,
    double fee,
    int minutes,
    int dataMB)
{
    phoneNumber = number;
    this->owner = owner;
    monthlyFee = fee;

    this->minutes = minutes;
    this->dataMB = dataMB;

    usedMinutes = 0;
    usedData = 0;

    subscribersCount++;
}
Subscription::Subscription(const Subscription& other)
{
    phoneNumber = other.phoneNumber;
    owner = other.owner;
    monthlyFee = other.monthlyFee;

    minutes = other.minutes;
    dataMB = other.dataMB;

    usedMinutes = other.usedMinutes;
    usedData = other.usedData;

    subscribersCount++;
}
Subscription::~Subscription()
{
    subscribersCount--;
}

string Subscription::getPhoneNumber() const
{
    return phoneNumber;
}

string Subscription::getOwner() const
{
    return owner;
}

double Subscription::getMonthlyFee() const
{
    return monthlyFee;
}

int Subscription::getMinutes() const
{
    return minutes;
}

int Subscription::getDataMB() const
{
    return dataMB;
}
void Subscription::setPhoneNumber(const string& phoneNumber)
{
    if (phoneNumber.length() != 10)
        throw invalid_argument("Invalid phone number");

    this->phoneNumber = phoneNumber;
}

void Subscription::setOwner(const string& owner)
{
    if (!IsValidText(owner))
        throw invalid_argument("Invalid owner");

    this->owner = owner;
}

void Subscription::setMonthlyFee(double fee)
{
    if (fee <= 0)
        throw invalid_argument("Invalid fee");

    monthlyFee = fee;
}

void Subscription::setMinutes(int minutes)
{
    if (minutes < 0)
        throw invalid_argument("Invalid minutes");

    this->minutes = minutes;
}

void Subscription::setDataMB(int dataMB)
{
    if (dataMB < 0)
        throw invalid_argument("Invalid data");

    this->dataMB = dataMB;
}
void Subscription::Call(int minutes)
{
    if (minutes < 0)
        throw invalid_argument("Invalid minutes");

    usedMinutes += minutes;
}
void Subscription::UseData(int mb)
{
    if (mb < 0)
        throw invalid_argument("Invalid data");

    usedData += mb;
}
double Subscription::Bill() const
{
    return monthlyFee;
}
void Subscription::Renew()
{
    usedMinutes = 0;
    usedData = 0;
}
bool Subscription::IsActive() const
{
    return true;
}
void Subscription::Print() const
{
    cout << "Owner: " << owner << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Monthly fee: " << monthlyFee << endl;
    cout << "Minutes: " << minutes << endl;
    cout << "Data: " << dataMB << endl;
}
void Subscription::OperatorReport()
{
    cout << "Subscribers: "
        << subscribersCount << endl;

    cout << "Extra minute price: "
        << pricePerExtraMinute << endl;
}

Subscription& Subscription::operator+(const Bundle& b)
{
    minutes += b.getMinutes();
    dataMB += b.getDataMB();

    return *this;
}
ostream& operator<<(ostream& out,
    const Subscription& obj)
{
    out << "Owner: " << obj.owner
        << ", Phone: " << obj.phoneNumber
        << ", Fee: " << obj.monthlyFee;

    return out;
}

// ==================================================
// PrepaidPlan
// ==================================================

PrepaidPlan::PrepaidPlan()
    : Subscription()
{
    credit = 0;
}

PrepaidPlan::PrepaidPlan(
    const string& number,
    const string& owner,
    double fee,
    int minutes,
    int dataMB,
    double credit)
    : Subscription(number, owner, fee, minutes, dataMB)
{
    if (credit < 0)
        throw invalid_argument("Invalid credit");

    this->credit = credit;
}

PrepaidPlan::PrepaidPlan(const PrepaidPlan& other)
    : Subscription(other)
{
    credit = other.credit;
}

PrepaidPlan::~PrepaidPlan()
{
}
double PrepaidPlan::getCredit() const
{
    return credit;
}

void PrepaidPlan::setCredit(double credit)
{
    if (credit < 0)
        throw invalid_argument("Invalid credit");

    this->credit = credit;
}
void PrepaidPlan::AddCredit(double amount)
{
    if (amount <= 0)
        throw invalid_argument("Invalid amount");

    credit += amount;
}
double PrepaidPlan::Bill() const
{
    return monthlyFee;
}
void PrepaidPlan::Print() const
{
    Subscription::Print();

    cout << "Credit: "
        << credit
        << endl;
}

// ==================================================
// PostpaidPlan
// ==================================================

PostpaidPlan::PostpaidPlan()
    : Subscription()
{
    contractMonths = 0;
    overuse = 0;
}

PostpaidPlan::PostpaidPlan(
    const string& number,
    const string& owner,
    double fee,
    int minutes,
    int dataMB,
    int contractMonths)
    : Subscription(number, owner, fee, minutes, dataMB)
{
    if (contractMonths < 0)
        throw invalid_argument("Invalid contract months");

    this->contractMonths = contractMonths;
    overuse = 0;
}

PostpaidPlan::PostpaidPlan(const PostpaidPlan& other)
    : Subscription(other)
{
    contractMonths = other.contractMonths;
    overuse = other.overuse;
}

PostpaidPlan::~PostpaidPlan()
{
}
int PostpaidPlan::getContractMonths() const
{
    return contractMonths;
}

void PostpaidPlan::setContractMonths(int months)
{
    if (months < 0)
        throw invalid_argument("Invalid months");

    contractMonths = months;
}
double PostpaidPlan::Bill() const
{
    double extra = 0;

    if (usedMinutes > minutes)
    {
        extra = (usedMinutes - minutes)
            * pricePerExtraMinute;
    }

    return monthlyFee + extra;
}
void PostpaidPlan::Print() const
{
    Subscription::Print();

    cout << "Contract months: "
        << contractMonths
        << endl;
}
