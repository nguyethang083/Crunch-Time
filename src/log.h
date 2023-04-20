#ifndef LOG_H
#define LOG_H
#include <string>

using namespace std;

class Log {
    private:
        //Error message
        string msg;

    public: 
        //Log SDL error
        void SDL(const string& msg);
        
        //Log IMG error
        void IMG(const string& msg);
    
};

#endif