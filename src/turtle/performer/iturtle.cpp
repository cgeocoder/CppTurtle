#include "iturtle.h"

#include "../interpreter/token.h"
#include "../interpreter/ast.h"
#include "../interpreter/genbc.h"

namespace turtle {

    TurtleInterpreter::TurtleInterpreter(const std::string& _File) {
        std::string source_text = read_file(_File);

        std::vector<Token> tokens = parse_tokens(source_text);

        // tokens_lex(tokens);

        AST ast = make_ast(tokens);

        this->m_Bc = gen_bytecode(ast);
    }

    void TurtleInterpreter::print_bytecode() {
        for (size_t i = 0; i < this->m_Bc.size(); ++i) {
            if (this->m_Bc.at(i) == bc_fw) {
                printf("%llu:\tfw\t%d\n", i, this->m_Bc.at(i + 1));
                i += 1;
            }
            else if (this->m_Bc.at(i) == bc_bw) {
                printf("%llu:\tbw\t%d\n", i, this->m_Bc.at(i + 1));
                i += 1;
            }
            else if (this->m_Bc.at(i) == bc_rt) {
                printf("%llu:\trt\t%d\n", i, this->m_Bc.at(i + 1));
                i += 1;
            }
            else if (this->m_Bc.at(i) == bc_lt) {
                printf("%llu:\tlt\t%d\n", i, this->m_Bc.at(i + 1));
                i += 1;
            }
            else if (this->m_Bc.at(i) == bc_up) {
                printf("%llu:\tup\n", i);
            }
            else if (this->m_Bc.at(i) == bc_dn) {
                printf("%llu:\tdn\n", i);
            }
            else if (this->m_Bc.at(i) == bc_dec) {
                printf("%llu:\tdec\n", i);
            }
            else if (this->m_Bc.at(i) == bc_jz) {
                printf("%llu:\tjz\t%d\n", i, this->m_Bc.at(i + 1));
                i += 1;
            }
            else if (this->m_Bc.at(i) == bc_jmp) {
                printf("%llu:\tjmp\t%d\n", i, this->m_Bc.at(i + 1));
                i += 1;
            }
            else if (this->m_Bc.at(i) == bc_push) {
                printf("%llu:\tpush\t%d\n", i, this->m_Bc.at(i + 1));
                i += 1;
            }
            else if (this->m_Bc.at(i) == bc_halt) {
                printf("%llu:\thalt\n", i);
            }
            else if (this->m_Bc.at(i) == bc_pop) {
                printf("%llu:\tpop\n", i);
            }
        }
        printf("\n");
    }
}