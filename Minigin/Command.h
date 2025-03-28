#ifndef COMMAND_H
#define COMMAND_H

//==========================
//Base Class 
//==========================
class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

#endif // !COMMAND_H
