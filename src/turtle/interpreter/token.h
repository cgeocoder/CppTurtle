#pragma once

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <vector>
#include <string>

enum TokenID {
	zero_tok,
	tok_invalid,

	tok_literal,
	tok_repeat,
	tok_fw,
	tok_bw,
	tok_rt,
	tok_lt,
	tok_up,
	tok_down,
	tok_tail,
	tok_lsp,
	tok_rsp,

	stmt_simple_cmd,
	stmt_blocks,
	stmt_cycle,
	stmt_tail_up,
	stmt_tail_down
};

class Token {
public:
	TokenID t_id;
	int t_start;
	int t_end;
	int t_line;
	unsigned int t_val;
};

std::string read_file(const std::string& _File);
std::vector<Token> parse_tokens(const std::string& _Text);
std::vector<std::string> tokens_lex(
	const std::vector<Token>& tokens,
	const std::string& raw_text
);

#endif // __TOKEN_H__