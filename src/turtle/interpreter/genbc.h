#pragma once

#ifndef __GENBYTECODE_H__
#define __GENBYTECODE_H__

#include <vector>
#include "ast.h"

enum ByteCode {
    bc_fw,      // forward
    bc_bw,      // backward
    bc_rt,      // right
    bc_lt,      // left
    bc_up,      // up tail
    bc_dn,      // down tail
    bc_dec,     // --stack[i]
    bc_jz,      // jump if (stack[i] == 0)
    bc_jmp,
    bc_push,
    bc_pop,
    bc_halt
};

void gen_index_bc(AST ast, std::vector<ByteCode>& bc);
std::vector<ByteCode> gen_bytecode(AST ast);

#endif // __GENBYTECODE_H__