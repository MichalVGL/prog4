#ifndef COMMAND_H
#define COMMAND_H

#include <functional>

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

	class FuncCommand final : public Command
	{
	public:
		explicit FuncCommand(std::function<void()>&& func)
			: m_Func(std::move(func))
		{
		}
		void Execute() override
		{
			if (m_Func)
			{
				m_Func();
			}
		}

	private:

		std::function<void()> m_Func;	//function to execute
	};
}

#endif // !COMMAND_H
