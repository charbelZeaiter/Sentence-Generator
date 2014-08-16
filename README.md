Sentence-Generator
==================

A Program which produces random sentances based on an input file. 

**=== What is the input file? ===**  
It is a grammar file. A grammar is a set of rules for some language, in this case it is called a context-free grammar (CFG).   
Essentially the input file contains tags and the program recursivly expands on tags and chooses a random expansion for those tags. Hence you can create your own grammars and have the program randomly generate sentances for you. (Always good to fill up space in an essay :P) 

Here is an example of a simple CFG:  

    {  
    <start>  
    The <object> <verb> tonight. ;  
    }  
    {  
    <object>  
    waves ;  
    big yellow flowers ;  
    slugs ;  
    }  
    {  
    <verb>  
    sigh <adverb> ;  
    portend like <object> ;  
    die <adverb> ;  
    }  
    {  
    <adverb>  
    warily ;  
    grumpily ;  
    }  
  
According to this grammar, two possible poems are “The big yellow flowers sigh warily tonight.” and
“The slugs portend like waves tonight.“ Essentially, the strings in angle-brackets (<>) are variables which
expand according to the rules in the grammar.
More precisely, each string in angle-brackets is known as a non-terminal. A non-terminal is a placeholder
that will expand to another sequence of words when generating a poem. In contrast, a terminal is a normal
word that is not changed to anything else when expanding the grammar. The name terminal is supposed to
conjure up the image that its something of a dead end, that no further expansion is possible.
All whitespace characters serve to separate terminals and non-terminals. For example, “tonight.” in
the example grammar results in one terminal, “tonight.”, being identified. However, “tonight .” (with
one whitespace added before the “.”) will give rise to two terminals, “tonight” and “.”. So all punctuation
marks such as “. ” and ‘’,” (with some whitespaces before and after) are treated as words or terminals.
A definition consists of a non-terminal (on its own line) and its set of productions (or expansions), each of
which is terminated by a semi-colon (;). There will always be at least one and potentially several productions
for each non-terminal. A production is just a sequence of words, some of which themselves may be non-
terminals. A production can be empty (i.e., just consist of the terminating semi-colon) which makes it
possible for a non-terminal to evaporate into nothingness. The entire definition is enclosed in braces ({}).  

For example, the following definition of <verb> has three productions:  

    {  
    <verb>                               // Non-terminal.
    sigh <adverb> ;                      // Production 1.        
    portend like <object> ;              // Production 2.
    die <adverb> ;                       // Production 3.
    }  

**=== Note ===**  
- All comments and spaces outside the curly braces of each definition are ignored.
- All spaces, tabs and newlines inside expansions/productions are ignored.
- Only 5 punctuation marks are supported “,”, “.”, “?”, “!” and “:”.
- Uses a fixed seed; please modify random.cpp to change.

**=== Usage ===**  

    ./rsg grammarFile.txt
    
    
