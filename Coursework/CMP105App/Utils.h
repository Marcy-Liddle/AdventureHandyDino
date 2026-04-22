#pragma once
#include <string>
#include <iostream>

enum class MessageType { INFO, DEBUG, WARNING, ERROR, SUCCESS};

class Utils
{
public:
	const static bool DEBUG_OUTPUT = true;

	static void printMsg(std::string msg, MessageType type = MessageType::INFO)
	{
		if (DEBUG_OUTPUT) 
		{
			switch (type)
			{
				case MessageType::DEBUG:   std::cout << "\033[36m" << msg << "\033[0m" << std::endl; break;
				case MessageType::WARNING: std::cout << "\033[33m" << msg << "\033[0m" << std::endl; break;
				case MessageType::ERROR:   std::cout << "\033[31m" << msg << "\033[0m" << std::endl; break;
				case MessageType::SUCCESS: std::cout << "\033[32m" << msg << "\033[0m" << std::endl; break;
				default:				   std::cout <<				  msg			   << std::endl; break;
			}
		}
	}
};