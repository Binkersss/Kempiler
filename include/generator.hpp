//
// Created by binker on 11/25/24.
//

#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <sstream>


class Generator {
private:
	std::stringstream m_output;


public:
	Generator() {
		// Write header
		m_output << "global _start\n";
		m_output << "section .text\n\n";
		m_output << "_start:\n";
	}

	void generate_exit(const std::string& exit_code) {
		m_output << "    mov rax, 60\n";          // sys_exit
		m_output << "    mov rdi, " << exit_code << "\n";  // exit code
		m_output << "    syscall\n";
	}

	std::string get_output() {
		return m_output.str();
	}
};



#endif //GENERATOR_HPP
