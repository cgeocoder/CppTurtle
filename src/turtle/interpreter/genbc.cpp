#include "genbc.h"

void gen_index_bc(AST ast, std::vector<ByteCode>& bc) {
    if (ast.id == stmt_blocks) {
        for (AST node : ast.nodes) {
            gen_index_bc(node, bc);
        }
    }
    else if (ast.id == stmt_simple_cmd) {
        switch (ast.token.t_id)
        {
        case tok_fw:
            bc.push_back(bc_fw);
            break;
        case tok_bw:
            bc.push_back(bc_bw);
            break;
        case tok_rt:
            bc.push_back(bc_rt);
            break;
        case tok_lt:
            bc.push_back(bc_lt);
            break;
        }

        bc.push_back((ByteCode)ast.nodes[0].token.t_val);
    }
    else if (ast.id == stmt_tail_up) {
        bc.push_back(bc_up);
    }
    else if (ast.id == stmt_tail_down) {
        bc.push_back(bc_dn);
    }
    else if (ast.id == stmt_cycle) {
        bc.push_back(bc_push);                              // push _Val_
        bc.push_back((ByteCode)ast.nodes[0].token.t_val);
        bc.push_back(bc_jz);                                // jz _Val_
        bc.push_back((ByteCode)0);
        
        int jz_inst_pos = (int)(bc.size() - 2);
        int jz_val_pos = (int)(bc.size() - 1);

        // blocks
        gen_index_bc(ast.nodes[1], bc);

        bc.push_back(bc_dec);
        bc.push_back(bc_jmp);
        bc.push_back((ByteCode)jz_inst_pos);

        bc.at(jz_val_pos) = (ByteCode)(bc.size());
        bc.push_back(bc_pop);
    }
}

std::vector<ByteCode> gen_bytecode(AST ast) {
    std::vector<ByteCode> bc;
    gen_index_bc(ast, bc);

    bc.push_back(bc_halt);
    return bc;
}