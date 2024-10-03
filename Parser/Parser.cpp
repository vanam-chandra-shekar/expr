#include "Parser.hpp"
#include "App.hpp"


#define  pi 3.141592653589793
#define e 2.718281828459045

void makeConstInst(Chunk& chunk , double constant)
{
    chunk.writeChunk(OP_CONSTANT);
    chunk.writeChunk(chunk.addConstant(constant));
}

void Parser::parse(Chunk &code, std::vector<Token> &_tokens) 
{
    tokens = std::move(_tokens);
    current = 0;

    try
    {
        expression(code);
    }
    catch(const ParseError& err)
    {
        App::error(err.pos , err.mssg);
    }
}

void Parser::expression(Chunk &out) { binary(out); }

void Parser::binary(Chunk &out)
{
    term(out);

    while (match(TPLUS , TMINUS))
    {
        Token op = previous();
        term(out);

        if(op.mtype == TPLUS)
        {
            out.writeChunk(OP_ADD);
        }
        else
        {
            out.writeChunk(OP_SUB);
        }
    }
}

void Parser::term(Chunk &out)
{
    unary(out);

    while (match(TSLASH , TSTAR))
    {
        Token op = previous();
        unary(out);
        if(op.mtype == TSLASH)
        {
            out.writeChunk(OP_DIV);
        }
        else
        {
            out.writeChunk(OP_MUL);
        }
    }
}

void Parser::unary(Chunk &out)
{
    if(match(TMINUS))
    {
        unary(out);
        out.writeChunk(OP_NEG);
        return;
    }

    expo(out);
    return;
}

void Parser::expo(Chunk &out)
{
    func(out);

    while (match(TCARROT))
    {
        func(out);
        out.writeChunk(OP_EXPO);
    }
    
}

void Parser::func(Chunk &out)
{
    if(match(TSIN))
    {
        primary(out);
        out.writeChunk(OP_SIN);
        return;
    }

    if(match(TCOS))
    {
        primary(out);
        out.writeChunk(OP_COS);
        return;
    }

    if(match(TTAN))
    {
        primary(out);
        out.writeChunk(OP_TAN);
        return;
    }

    if(match(TLN))
    {
        primary(out);
        out.writeChunk(OP_LN);
        return;
    }

    primary(out);

}

void Parser::primary(Chunk &out)
{
    if(match(TNUMBER))
    {
        double literal = std::get<double>(previous().mliteral);
        makeConstInst(out , literal);
        return;
    }

    if(match(TPI)) 
    {
        makeConstInst(out , pi);
        return;
    }

    if(match(TE))
    {
        makeConstInst(out,e);
        return;
    }

    if(match(TLEFTPAREN))
    {
        expression(out);
        consume(TRIGHTPAREN, "Expect ')' after expression.");
        return;
    }

    throw error(peek() , "Expected a expression.");
}
