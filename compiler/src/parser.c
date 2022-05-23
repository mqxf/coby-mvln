#include "include/main.h"

parser_t* initParser(lexer_t* lexer) {
    parser_t* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->size = 1;
    parser->i = 0;

    parser->tokens = calloc(1, sizeof(struct TOKEN_STRUCT*));
    parser->tokens[0] = lexerNextToken(lexer);
    parser->token = parser->tokens[0];

    while (parser->tokens[parser->size - 1]->type != TOKEN_EOF) {
        parser->size++;
        parser->tokens = realloc(parser->tokens, parser->size * sizeof(struct TOKEN_STRUCT*));
        parser->tokens[parser->size - 1] = lexerNextToken(lexer);
    }

    return parser;
}

token_t* parserEat(parser_t* parser, unsigned int type) {
    if (parser->token->type != type) {
        printf("[Parser]: Unexpected token: '%s', was expecting token with type: '%s'\n", tokenToString(parser->token),tokenTypeToString(type));
        exit(1);
    }
    
    parser->i++;
    parser->token = parser->tokens[parser->i];
    return parser->token;
}

token_t* parserPeek(parser_t* parser, size_t offset) {
    if (parser->i + offset < parser->size) return parser->tokens[parser->i + offset];
    else return NULL;
}

AST_t* parserParse(parser_t* parser) {
    AST_t* root = initAST(AST_ROOT);
    while (parser->token->type != TOKEN_EOF) {
        if (parser->token->type == TOKEN_CONSTANT) {
            listPush(root->children, parseConstant(parser));
        }
        else if (parser->token->type == TOKEN_ID) {
            if (parserPeek(parser, 1)->type == TOKEN_LEFT_PAREN) {
                //parse function declaration
            }
            else {
                listPush(root->children, parseVariable(parser));
            }
        }
        else {
            printf("[Parser]: Invalid token %sTokens outside of functions can only be variable or constant declarations.\n", tokenToString(parser->token));
            exit(1);
        }
    }
    return root;
}

AST_t* parseConstant(parser_t* parser) {
    //#name:type = value;
    parserEat(parser, TOKEN_CONSTANT);
    //name:type = value;
    AST_t* constant = initAST(AST_STATEMENT_CONSTANT);
    if (!isValidName(parser->token->value)) {
        printf("[Parser]: Constant '%s' is already defined or uses an already existing identifier.\n", parser->token->value);
        exit(1);
    }
    constant->name = parser->token->value;
    parserEat(parser, TOKEN_ID);
    //:type = value;
    parserEat(parser, TOKEN_COLON);
    //type = value;
    if (strcmp(parser->token->value, "string") == 0) {
        constant->dType = DATA_TYPE_STRING;
        addVariable(constant->name, DATA_TYPE_STRING);
    }
    else if (strcmp(parser->token->value, "int") == 0) {
        constant->dType = DATA_TYPE_INT;
        addVariable(constant->name, DATA_TYPE_INT);
    }
    else if (strcmp(parser->token->value, "char") == 0) {
        constant->dType = DATA_TYPE_CHAR;
        addVariable(constant->name, DATA_TYPE_CHAR);
    }
    else if (strcmp(parser->token->value, "bin") == 0) {
        constant->dType = DATA_TYPE_BIN;
        addVariable(constant->name, DATA_TYPE_BIN);
    }
    else if (strcmp(parser->token->value, "hex") == 0) {
        constant->dType = DATA_TYPE_HEX;
        addVariable(constant->name, DATA_TYPE_HEX);
    }
    else if (strcmp(parser->token->value, "float") == 0) {
        constant->dType = DATA_TYPE_FLOAT;
        addVariable(constant->name, DATA_TYPE_FLOAT);
    }
    else if (strcmp(parser->token->value, "bool") == 0) {
        constant->dType = DATA_TYPE_BOOLEAN;
        addVariable(constant->name, DATA_TYPE_BOOLEAN);
    }
    else {
        constant->dType = DATA_TYPE_UNKNOWN;
        addVariable(constant->name, DATA_TYPE_UNKNOWN);
    }
    parserEat(parser, TOKEN_ID);
    //= value;
    parserEat(parser, TOKEN_EQUALS);
    //value;
    switch (constant->dType) {
        case DATA_TYPE_STRING:
            constant->strValue = parser->token->value;
            parserEat(parser, TOKEN_STRING);
            break;
        case DATA_TYPE_INT:
            constant->longValue = strtol(parser->token->value, NULL, 10);
            parserEat(parser, TOKEN_INT);
            break;
        case DATA_TYPE_CHAR:
            constant->charValue = parser->token->value[0];
            parserEat(parser, TOKEN_CHAR);
            break;
        case DATA_TYPE_BIN:
            constant->longValue = strtol(parser->token->value, NULL, 2);
            parserEat(parser, TOKEN_BIN);
            break;
        case DATA_TYPE_HEX:
            constant->longValue = strtol(parser->token->value, NULL, 16);
            parserEat(parser, TOKEN_HEX);
            break;
        case DATA_TYPE_FLOAT:
            parserEat(parser, TOKEN_FLOAT);
            break;
        case DATA_TYPE_BOOLEAN:
            if (strcmp(parser->token->value, "flase") == 0) {
                constant->longValue = 0;
            }
            else if (strcmp(parser->token->value, "true") == 0) {
                constant->longValue = 1;
            }
            parserEat(parser, TOKEN_ID);
            break;
        default: 
            parserEat(parser, TOKEN_ID);
            break;
    }
    //;
    parserEat(parser, TOKEN_SEMICOLON);
    return constant;
}

AST_t* parseVariable(parser_t* parser) {
    AST_t* variable = initAST(AST_STATEMENT_VAR_DECLARATION);
    if (!isValidName(parser->token->value)) {
        printf("[Parser]: Variable '%s' is already defined or uses an already existing identifier.\n", parser->token->value);
        exit(1);
    }

    variable->name = parser->token->value;

    parserEat(parser, TOKEN_ID);
    parserEat(parser, TOKEN_COLON);

    if (strcmp(parser->token->value, "string") == 0) {
        variable = DATA_TYPE_STRING;
        addVariable(variable->name, DATA_TYPE_STRING);
    }
    else if (strcmp(parser->token->value, "int") == 0) {
        variable->dType = DATA_TYPE_INT;
        addVariable(variable->name, DATA_TYPE_INT);
    }
    else if (strcmp(parser->token->value, "char") == 0) {
        variable->dType = DATA_TYPE_CHAR;
        addVariable(variable->name, DATA_TYPE_CHAR);
    }
    else if (strcmp(parser->token->value, "bin") == 0) {
        variable->dType = DATA_TYPE_BIN;
        addVariable(variable->name, DATA_TYPE_BIN);
    }
    else if (strcmp(parser->token->value, "hex") == 0) {
        variable->dType = DATA_TYPE_HEX;
        addVariable(variable->name, DATA_TYPE_HEX);
    }
    else if (strcmp(parser->token->value, "float") == 0) {
        variable->dType = DATA_TYPE_FLOAT;
        addVariable(variable->name, DATA_TYPE_FLOAT);
    }
    else if (strcmp(parser->token->value, "bool") == 0) {
        variable->dType = DATA_TYPE_BOOLEAN;
        addVariable(variable->name, DATA_TYPE_BOOLEAN);
    }
    else if (strcmp(parser->token->value, "collection") == 0) {
        //call function giving it parser AND name
    }
    else if (strcmp(parser->token->value, "library") == 0) {
        //
    }
    else if (strcmp(parser->token->value, "list") == 0) {
        //
    }
    else {
        variable->dType = DATA_TYPE_UNKNOWN;
        addVariable(variable->name, DATA_TYPE_UNKNOWN);
    }

    parserEat(parser, TOKEN_ID);

    if(parser->token->type == TOKEN_SEMICOLON) {
        parserEat(parser, TOKEN_SEMICOLON);
        return variable;
    }

    parserEat(parser, TOKEN_EQUALS);

    switch (variable->dType) {
        case DATA_TYPE_STRING:
            variable->strValue = parser->token->value;
            parserEat(parser, TOKEN_STRING);
            break;
        case DATA_TYPE_INT:
            variable->longValue = strtol(parser->token->value, NULL, 10);
            parserEat(parser, TOKEN_INT);
            break;
        case DATA_TYPE_CHAR:
            variable->charValue = parser->token->value[0];
            parserEat(parser, TOKEN_CHAR);
            break;
        case DATA_TYPE_BIN:
            variable->longValue = strtol(parser->token->value, NULL, 2);
            parserEat(parser, TOKEN_BIN);
            break;
        case DATA_TYPE_HEX:
            variable->longValue = strtol(parser->token->value, NULL, 16);
            parserEat(parser, TOKEN_HEX);
            break;
        case DATA_TYPE_FLOAT:
            parserEat(parser, TOKEN_FLOAT);
            break;
        case DATA_TYPE_BOOLEAN:
            if (strcmp(parser->token->value, "flase") == 0) {
                variable->longValue = 0;
            }
            else if (strcmp(parser->token->value, "true") == 0) {
                variable->longValue = 1;
            }
            parserEat(parser, TOKEN_ID);
            break;
        default: 
            parserEat(parser, TOKEN_ID);
            break;
    }

    parserEat(parser, TOKEN_SEMICOLON);
    return variable;
}
