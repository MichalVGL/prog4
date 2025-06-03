#ifndef COMMAND_H
#define COMMAND_H

//==========================
//Base Class 
//==========================

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class NullCommand final : public Command
	{
	public:
		void Execute() override {};
	};
}

#endif // !COMMAND_H
