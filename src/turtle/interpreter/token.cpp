#include "token.h"

#include <fstream>

std::string read_file(const std::string& _File) {
	std::fstream f{ _File };

	if (!f.is_open())
		throw std::exception(
			("read_file() failed: could't open the file " + _File).c_str()
		);

	return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

inline static bool is_separator(wchar_t wch) {
    return (wch == ' ') || (wch == '\t') || (wch == '\n') || (wch == '[') || (wch == ']');
}

inline static bool is_literal(const std::string& wstr) {
    return (wstr.at(0) != '0') && (wstr.find_first_not_of("0123456789") == std::string::npos);
}

std::vector<Token> parse_tokens(const std::string& _Text) {
	std::vector<Token> tokens;

    std::string target;
    int line_count = 1;
    int pos_count = 0;
    size_t prog_len = _Text.length();
    for (int i = 0; i < prog_len; ++i) {
        char ch = _Text.at(i);

        if (is_separator(ch)) {
            if (target != "") {
                if (target == "Повтори") {
                    tokens.push_back({ tok_repeat , pos_count - 7, pos_count, line_count });
                }
                else if (target == "Вперёд") {
                    tokens.push_back({ tok_fw , pos_count - 6, pos_count, line_count });
                }
                else if (target == "Назад") {
                    tokens.push_back({ tok_bw , pos_count - 5, pos_count, line_count });
                }
                else if (target == "Направо") {
                    tokens.push_back({ tok_rt , pos_count - 7, pos_count, line_count });
                }
                else if (target == "Налево") {
                    tokens.push_back({ tok_lt , pos_count - 6, pos_count, line_count });
                }
                else if (target == "Поднять") {
                    tokens.push_back({ tok_up , pos_count - 7, pos_count, line_count });
                }
                else if (target == "Опустить") {
                    tokens.push_back({ tok_down , pos_count - 8, pos_count, line_count });
                }
                else if (target == "хвост") {
                    tokens.push_back({ tok_tail , pos_count - 5, pos_count, line_count });
                }
                else if (is_literal(target)) {
                    unsigned int val = std::stoi(target);

                    tokens.push_back({ tok_literal , pos_count - (int)target.length(), pos_count, line_count, val });
                }
                else {
                    tokens.push_back({ tok_invalid, pos_count - (int)target.length(), pos_count, line_count });
                }
            }
            if (ch == '[') {
                tokens.push_back({ tok_lsp , pos_count, pos_count + 1, line_count });
            }
            else if (ch == ']') {
                tokens.push_back({ tok_rsp , pos_count, pos_count + 1, line_count });
            }
            else if (ch == '\n') {
                pos_count = -1;
                line_count += 1;
            }
            
            target.clear();
        }
        else {
            target += ch;
        }
        pos_count += 1;
    }

	return tokens;
}

std::vector<std::string> tokens_lex(const std::vector<Token>& tokens, const std::string& raw_text) {
    size_t len = tokens.size() - 2;
    int spars = 0;
    TokenID excepted_sym = tok_invalid;

    std::vector<std::string> errors;

    auto print_err = [&](Token t_left, Token t_current, Token t_right) {
        size_t cntr = 0;
        size_t line_counter = 1;
        while (line_counter != t_current.t_line) {
            if (raw_text.at(cntr) == '\n')
                line_counter += 1;
            cntr += 1;
        }
        int spaces = 0;
        char ch = raw_text.at(cntr);
        while (ch == ' ' || ch == '\t') {
            cntr += 1;
            ch = raw_text.at(cntr);
            spaces += 1;
        }
        std::string text_info = "line " + std::to_string(t_current.t_line) + " | ";
        while (raw_text.at(cntr) != '\n') {
            text_info += raw_text.at(cntr++);
        }
        text_info += "\n    ";
        for (size_t t = 0; t < std::to_string(t_current.t_line).length(); ++t)
            text_info += " ";

        text_info += "+ | ";
        for (size_t i = 0; i < text_info.length(); ++i) {
            if (i >= (t_left.t_start - spaces) && i <= (t_right.t_start - spaces)) {
                text_info += '^';
            }
            else if (i > (t_right.t_start - spaces)) {
                break;
            }
            else {
                text_info += ' ';
            }
        }

        errors.push_back("EGE6I: invalid syntax:\n" + text_info + "\n");
    };

    for (size_t i = 0; i < len; ++i) {
        TokenID tid0 = tokens.at(i).t_id;
        TokenID tid1 = tokens.at(i + 1).t_id;

        if (tid0 == tok_repeat) {
            if (tid1 != tok_literal) {
                print_err(tokens.at(i), tokens.at(i + 1), tokens.at(i + 2));
            }
            else {
                excepted_sym = tok_lsp;
            }

            i += 1;
        }
        else if (tid0 == tok_literal) {
            if (excepted_sym != tok_invalid && excepted_sym != tid0) {
                print_err(tokens.at(i), tokens.at(i + 1), tokens.at(i + 2));
            }
        }
    }

    return errors;
} 