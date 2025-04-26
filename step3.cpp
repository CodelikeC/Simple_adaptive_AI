#include <iostream>
using namespace std;
#include <string> 
#include <vector>
#include <functional>
#include <memory>

#include <thread>
#include <ctime> 

struct Rule
{
    public: 
    int id; 
    string description;
    function <bool()> condition;
    function<void()> action;  
    bool active = false; 
}; 

class RuleEngine
{
    private: 
    vector<shared_ptr<Rule>> rules; 
    int nextId = 1; 

    public: 
    void proposeRule (const string &desc, function<bool()> cond, function<void()> act)
    {
        auto rule = make_shared<Rule>(Rule{nextId++, desc, cond, act, false}); 
        rules.push_back(rule); 
        cout << "New Rule proposed:" << rule ->description << "(ID :" << rule -> id << endl; 
        
    }

    void activeRule(int id)
    {
        for (auto &rule : rules)
        {
            if (rule -> id == id)
            {
                rule -> active = true;
                cout <<"rule" << id << "activated" << endl;
                return; 
            }
        }
        cout <<"Rule ID not found" << endl; 
    }

    void evaluateRules()
    {
        for (auto &rule : rules)
        {
            if (rule -> active and rule -> condition())
            {
                rule -> action(); 
            }
        }
    }

    void listRules()
    {
        for (auto &rule : rules)
        {
            cout <<"id:" << rule -> id
            << "desc:" << rule -> description
            <<"active:" << (rule -> active ? "yes" : "no") << endl; 
        }
    }
}; 

bool suspiciousActivity()
{
    // Gia lap dieu kien - thuc te se phuc tap..//
    return rand() % 2 == 0;
}

void alertAdmin()
{
    cout <<"Alert: suspicious activity detected" << endl;
}

int main ()
{
    RuleEngine engine;

    // AI de xuat rule .. /// 
    engine.proposeRule("Dectect suspicious activities", suspiciousActivity, alertAdmin); 

    // nguoi dung duyet rule .. // 
    engine.listRules() ; 
    int id;
    cout <<"Enter Rule ID to activate:" << endl; 
    cin >> id; 
    engine.activeRule(id); 

    // vong lap he thong ..//
    while (true)
    {
        engine.evaluateRules();
        this_thread ::sleep_for(chrono::seconds(5));
    }
    return 0; 
}