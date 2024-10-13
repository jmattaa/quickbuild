#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"

#define SEARCH_DIR "."
#define CONFIG_FILE "quickbuild"

using namespace std;

int main(int argc, char **argv) {
  cout << "= Quickbuild Beta v0.1.0\n";

  // Get a list of all files in this diectory, recursively
  cout << "- (wait) scanning directory...\n";
  vector<filesystem::directory_entry> file_tree;
  auto dir_iterator = filesystem::recursive_directory_iterator(SEARCH_DIR);
  for (auto &entry : dir_iterator) {
    // Ignore .git and directories
    if (entry.is_directory() ||
        entry.path().string().find(".git") != string::npos)
      continue;
    file_tree.push_back(entry);
  }

  // Build config file
  cout << "- (wait) building configuration...\n";

  // Read config file
  ifstream config_file(CONFIG_FILE, ios::binary);
  if (!config_file.is_open()) {
    cerr << "= (fatal) couldn't find config file!\n";
    return EXIT_FAILURE;
  }
  vector<unsigned char> config_buffer(istreambuf_iterator(config_file), {});

  // Feed config into lexer
  Lexer lexer = Lexer(config_buffer);
  vector<Token> tokens;
  try {
    tokens = lexer.get_token_stream();
  } catch (LexerException lexer_exception) {
    cerr << "= (fatal) failed to lex configuration! details: ";
    cerr << "`" << lexer_exception.what() << "`" << endl;
  }

  // NOTE: Debugging purposes only!
  // for (const auto &i : tokens) {
  //   if (i.type == TokenType::Symbol || i.type == TokenType::Invalid) {
  //     cout << "symbol: ("
  //          << static_cast<typename underlying_type<TokenType>::type>(i.type)
  //          << ", \""
  //          << static_cast<typename underlying_type<SymbolType>::type>(
  //                 get<CTX_SYMBOL>(i.context))
  //          << "\")" << endl;
  //   } else {
  //     cout << "str: ("
  //          << static_cast<typename underlying_type<TokenType>::type>(i.type)
  //          << ", \"" << get<CTX_STRING>(i.context) << "\")" << endl;
  //   }
  // }

  AST root;
  Parser parser = Parser();

  try {
    root = parser.parse_tokens(tokens);
  } catch (ParserException parser_exception) {
    cerr << "= (fatal) failed to parse configuration! details: ";
    cerr << "`" << parser_exception.what() << "`" << endl;
  }

  return EXIT_SUCCESS;
}
