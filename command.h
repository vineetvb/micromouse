#ifndef COMMAND_H_
#define COMMAND_H_

class Command
{
public:
    // a polymorphic type should have a virtual destructor
    virtual ~Command() = default;
};


class CommandI : public Command //integervalued commands
{
public:
    int x;
    int theta;
    CommandI(int _theta, int _x): theta(_theta), x(_x)
    {
    };
};

class CommandF : public Command
{
public:
    float x;
    float theta;
};

#endif
