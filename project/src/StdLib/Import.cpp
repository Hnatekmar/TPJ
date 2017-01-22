#include "include/StdLib/Import.h"
#include <fstream>
#include "include/CompilerException.h"
#include "include/Lexer.h"

Import::Import(Parser &parser) : m_parser(parser)
{
    m_args.push_back("cesta");
}

Token Import::execute(std::vector<std::shared_ptr<AST> > &args, Context &context)
{
     Context copy(context);
     argsToContext(args, copy);
     Token path = copy.at("cesta");
     if(path.type != TokenType::STRING)
     {
         throw InterpreterException("Token není typu string", path);
     }
     std::string fileName = boost::get<std::string>(path.value);
     std::cerr << "Nahrávám " << fileName << std::endl;
     std::ifstream module(fileName, std::ifstream::in);
     if(!module.good())
     {
         char* miragePath = std::getenv("MIRAGE_PATH");
         if(miragePath != nullptr)
         {
             std::string miragePathString = miragePath;
             module.open(miragePathString + "/" + fileName);
         }
         if(!module.good())
         {
            throw InterpreterException("Soubor se nepodařilo otevřít ", path);
         }
     }
     Lexer lexer(module);
     m_parser.parse(lexer);
     return Token{
         TokenType::BOOL,
         true,
         {}
     };
}
