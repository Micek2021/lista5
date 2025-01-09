#pragma once

#include <string>
//filename
const std::string FILENAME = "correctoutput.txt";

//node error descriptions
const std::string TOOMANYCHILDRENERRORINFO = "too many children";
const std::string TOOFEWCHILDRENERRORINFO = "too few children";
const std::string DIVISIONBYZEROERRORINFO = "division by zero";
const std::string NOOPERATORINSUM = "no operator in sum";

//tree costants
const char ONE[] = "1";
const char PLUS_SIGN[] = "+";
const char MINUS_SIGN[] = "-";
const char DIV_SIGN[] = "/";
const char MUL_SIGN[] = "*";
const char ALL_DIGITS[] = "0123456789";
const char SIN_FUNC[] = "sin";
const char COS_FUNC[] = "cos";
const char SPACE[] = " ";
const char TAN_FUNC[] = "tan";

//tree error descriptions
const std::string INCOMPLETETREELOADINGERRORINFO = "Tree is incomplete: missing operands.";
const std::string EMPTYROOTERRORINFO = "Expression is incomplete or invalid.";
const std::string TOOBIGEXPRESSIONERRORINFO = "Too many values in the expression.";

//evaluator messages
const char REPAIRED_MSG[] = "Repairing tree, new expression ";
const char INVALID_PARAM_MSG[] = "You have passed invalid parameter to this function.";
const char DIFFERENT_ARGUMENT_MSG[] = "Number of variables are different";
const char EXIT_MSG[] = "You have typed exit command, bye!";
const char NO_ARG_MSG[] = "Your have not put any variables in your equation";

//processor constants
const char ENTER_COMMAND[] = "enter";
const char VARS_COMMAND[] = "vars";
const char PRINT_COMMAND[] = "print";
const char COMP_COMMAND[] = "comp";
const char JOIN_COMMAND[] = "join";
const char EXIT_COMMAND[] = "exit";