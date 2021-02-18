%option noinput
%option nounput
%option noyywrap

LETTER          [A-Za-z_]
DIGIT           [0-9]
WHITESPACE      [ \t\r\n]
PUNCTUATION     [~`!@#$%^&*()_+-={}|\\\[\]:;\"\'<>,./?]

%%

{LETTER}+                               { return 0; }
{LETTER}+{PUNCTUATION}                  { return 0; }
{LETTER}+"-"({LETTER}+)                 { return 0; }
{LETTER}+"]"({LETTER}+)                 { return 0; }
{LETTER}+"'"({LETTER}+)                 { return 0; }
{LETTER}+"."+{LETTER}+"."+{LETTER}+")"  { return 0; }
{LETTER}+"."+{LETTER}+"."{LETTER}+      { return 0; }
{LETTER}+{DIGIT}+                       { return 0; }
{PUNCTUATION}+                          {}
{WHITESPACE}+                           {}
<<EOF>>                                 { return -1; }
.                                       {}

%%
