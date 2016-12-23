#ifndef MACRO
#define MACRO

#include "../AST.h"

std::shared_ptr<AST> listToAst(std::list<Token>& list);
std::list<Token> astToList(std::shared_ptr<AST>& ast);

/**
 * @brief Vrátí neevaluované ast v podobě tokenu. Pokud je to volání vrátí list, pokud je to identifikátor vrátí neevaluovaný identifikátor
 * @param Ast
 * @return Neevaluovaná hodnota
 */
Token quote(std::shared_ptr<AST>& ast);

/**
 * @brief Převede hodnotu na ast (inverze k quote)
 * @param value - Hodnota, kterou je třeba převést
 * @return ast pro evaluaci
 */
std::shared_ptr<AST> unquote(Token& value);

class IMacro
{
protected:
    std::vector<std::shared_ptr<AST>> m_body = {};
    std::vector<std::string> m_args = {};
    Context argsToContext(std::vector<std::shared_ptr<AST> > &args, Context context);
public:
    virtual ~IMacro() = default;

    /**
     * @brief Provede expanzi makra (modifikuje ast, tak aby při dalším zavolání nemuselo docházet k expanzi)
     * @param args
     * @param context
     * @return Ast reprezentující expandované makro
     */
    virtual std::shared_ptr<AST> expand(std::vector<std::shared_ptr<AST> > &args, Context &context);
};

class Macro : public IMacro
{
public:
    Macro(std::vector<std::shared_ptr<AST>>& code);
};


#include "../IFunction.h"

class CreateMacro : public IFunction
{
public:
    Token execute(std::vector<std::shared_ptr<AST> > &args, Context &) override;
};

#endif
