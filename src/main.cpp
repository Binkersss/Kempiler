//
// Created by binker on 11/25/24.
//
#include "tokenization.hpp"
#include "generator.hpp"
#include "parser.hpp"
#include "node.hpp"
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
	system("rm -f out.asm out.o out");

	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input.hy>" << std::endl;
		return EXIT_FAILURE;
	}

	// Read input file
	std::string contents;
	{
		std::stringstream contents_stream;
		std::fstream input(argv[1], std::ios::in);
		contents_stream << input.rdbuf();
		contents = contents_stream.str();
	}

	// Tokenize
	Tokenizer tokenizer(std::move(contents));
	std::vector<Token> tokens = tokenizer.tokenize();

	// Parse
	Parser parser(std::move(tokens));
	auto node = parser.parse();
	if (!node) {
		std::cerr << "Parse error" << std::endl;
		return EXIT_FAILURE;
	}

	// Generate assembly
	Generator generator;
	if (node->type == NodeType::Exit) {
		generator.generate_exit(node->exit.arg);
	}

	// Write assembly to file
	{
		std::ofstream file("out.asm");
		file << generator.get_output();
	}
	if (system("nasm -f elf64 out.asm -o out.o") != 0) {
		std::cerr << "Assembly failed" << std::endl;
		return EXIT_FAILURE;
	}

	if (system("ld -o out out.o") != 0) {
		std::cerr << "Linking failed" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}