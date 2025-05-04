#include "ast.h"

inline bool is_stmt(TokenID tid0) {
	return (tid0 >= stmt_simple_cmd) && (tid0 <= stmt_tail_down);
}

inline bool is_move_cmd(TokenID tid0) {
	return (tid0 >= tok_fw) && (tid0 <= tok_lt);
}

inline bool is_stmt_simple_cmd(TokenID tid0, TokenID tid1) {
	return is_move_cmd(tid0) && (tid1 == tok_literal);
}

inline bool is_stmt_blocks(TokenID tid0, TokenID tid1) {
	return is_stmt(tid0) && is_stmt(tid1);
}

inline bool is_stmt_cycle(TokenID tid0, TokenID tid1, TokenID tid2, TokenID tid3, TokenID tid4) {
	return (tid0 == tok_repeat) && (tid1 == tok_literal) 
		&& (tid2 == tok_lsp) && is_stmt(tid3) && (tid4 == tok_rsp);
}

inline bool is_stmt_tail_up(TokenID tid0, TokenID tid1) {
	return (tid0 == tok_up) && (tid1 == tok_tail);
}

inline bool is_stmt_tail_down(TokenID tid0, TokenID tid1) {
	return (tid0 == tok_down) && (tid1 == tok_tail);
}

AST make_ast(std::vector<Token> tokens) {
    size_t tok_len = tokens.size();
    std::vector<AST> ast;

    for (int i = 0; i < tok_len; ++i) {
        AST tmp_ast;
        tmp_ast.token = tokens.at(i);
        tmp_ast.id = tokens.at(i).t_id;

        ast.push_back(tmp_ast);
    }

    auto remove_complite_token = [&](size_t _Off, size_t _Len) {
        for (size_t i = _Off + 1; i < tok_len - _Len; ++i) {
            ast[i] = ast[i + _Len];
        }

        for (size_t i = 0; i < _Len; ++i)
            ast.pop_back();

        tok_len -= _Len;
    };

    for (size_t i = 0; i < tok_len; ++i) {
        TokenID tid0 = (TokenID)((i < tok_len) ? ast[i].id : zero_tok);
        TokenID tid1 = (TokenID)((i + 1 < tok_len) ? ast[i + 1].id : zero_tok);
        TokenID tid2 = (TokenID)((i + 2 < tok_len) ? ast[i + 2].id : zero_tok);
        TokenID tid3 = (TokenID)((i + 3 < tok_len) ? ast[i + 3].id : zero_tok);
        TokenID tid4 = (TokenID)((i + 4 < tok_len) ? ast[i + 4].id : zero_tok);
        TokenID tid5 = (TokenID)((i + 5 < tok_len) ? ast[i + 5].id : zero_tok);

        if (is_stmt_simple_cmd(tid0, tid1)) {
            ast[i].id = stmt_simple_cmd;
            ast[i].nodes.push_back(ast[i + 1]);
            remove_complite_token(i, 1);
            i = -1;
        }
        else if (is_stmt_tail_up(tid0, tid1)) {
            ast[i].id = stmt_tail_up;
            remove_complite_token(i, 1);
            i = -1;
        }
        else if (is_stmt_tail_down(tid0, tid1)) {
            ast[i].id = stmt_tail_down;
            remove_complite_token(i, 1);
            i = -1;
        }
        else if (is_stmt_cycle(tid0, tid1, tid2, tid3, tid4)) {
            ast[i].id = stmt_cycle;
            ast[i].nodes.push_back(ast[i + 1]);
            ast[i].nodes.push_back(ast[i + 3]);

            remove_complite_token(i, 4);
            i = -1;
        }
        else if (is_stmt_blocks(tid0, tid1)) {

            if (tid0 == stmt_blocks) {
                ast[i].id = stmt_blocks;
                ast[i].nodes.push_back(ast[i + 1]);
                remove_complite_token(i, 1);
                i = -1;
            }
            else {
                AST new_block;
                new_block.id = stmt_blocks;
                new_block.nodes.push_back(ast[i]);
                new_block.nodes.push_back(ast[i + 1]);

                ast[i] = new_block;
                remove_complite_token(i, 1);
                i = -1;
            }
        }
    }

    return ast.at(0);
}