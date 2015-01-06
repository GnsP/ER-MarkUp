ER Markup Language And Compiler
===============================

###Author: 
Ganesh Prasad Sahoo 
6th Semester B.Tech 
Computer Science and Engineering
National Institute of Technology, Rourkela


Background
----------

ER Markup language is a textual framework to represent Entities 
and Relationships. This project started as a weekend project to 
avoid MS Visio for drawing ER Diagrams. I had very low diskspace 
and no wish to switch from Linux to Windows again just for a piece 
software that would enable me to to do one thing in particular - 
"Drawing ER Diagrams", that too for a class assignment. So I decided 
on designing and developing something lighter and more productive
for this specific task and started writing Grammar Productions for the
same. After about one and half days of work, I was sitting on some 
500 lines of code which compiled my ER Diagram Descriptions written 
in the ER Markup Language to Graphviz dot language.

GRAMMAR SPECIFICATIONS
----------------------

'*PROGRAM* -> DIAGRAM name; BEGIN *(ENTITY+RELATION)+* END

*ENTITY* -> ENT name [WEAK] ;
			| ENT name [WEAK] { *ATTRIBUTE*\* } 
			
*ATTRIBUTE* -> ATTR name *(TAG)*\* ;
			| ATTR name COMPOSITE { *ATTRIBUTE*\* }
			
*RELATION* -> RELN name [WEAK] FROM { *EDGE*+ } TO { *EDGE*+ } ;

*EDGE* -> CONNECT name *EDGETYPE*\* ;

*TAG* -> WEAK | MULTI | KEY | DERIVED 

*EDGETYPE* -> PARTIAL | TOTAL | ONE | MANY '


**comments start with #**

USAGE
-----

Build the executable 'erdcc' with make.

Then run 'erdcc < source file in ER Markup > < Outputfile >'

This will give you a Dot file describing nodes and edges of the ER Diagram.
For best results, render this Dot file with Graphviz fdp engine.


EXAMPLE
-------

'# Test code in ER Markup Language
DIAGRAM test;
BEGIN
ENT I{
	ATTR Consciousness;
	ATTR "Knowledge" DERIVED;
	ATTR self KEY;
}

ENT God{
	ATTR "Everything" KEY COMPOSITE{
		ATTR Universe;
		ATTR I KEY;
	}
	ATTR Reality;
}

RELN Conceived 	FROM{ CONNECT I MANY; }	TO { CONNECT God ONE; };
RELN Created FROM{ CONNECT God ONE; } TO { CONNECT I MANY; };

ENT Book{
	ATTR Name;
	ATTR ISBN KEY;
	ATTR Price;
	ATTR Author MULTI;
}

RELN Write FROM { CONNECT I MANY; } TO { CONNECT Book MANY; };
RELN Read FROM { CONNECT I MANY; } TO { CONNECT Book MANY; };

ENT Software{
	ATTR Name;
	ATTR "Written in (Language)" MULTI;
	ATTR "Interface CLI/TUI/GUI" MULTI;
	ATTR Bugs MULTI;
	ATTR Programmer MULTI;
}

RELN Write FROM { CONNECT I ONE; } TO { CONNECT Software MANY; };

END

'


