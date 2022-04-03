#include "../framework.h"

expect("[]", "");
expect("[1, ]", "1");
expect("IllegalCharError", "£");

expect("[1, 2, ]", "1;2");

expect("[1.6, ]", "1.6");
expect("[-0.1, ]", "-0.1");
expect("[6, ]", "1+5");
expect("[0.3, ]", "0.1 + 0.2");
expect("[-4, ]", "1 - 5");
expect("[3, ]", "2*1.5");