//Data represented in quantity in computer memory, thinking/computing done by addidtion/subtraction/cmp operantions by cpu, conntrolle by cpu architecture.

//The cpu instructions done in machine code, promted by assembly code.

//When running a c program, (refer grok convo for more) req the program to be available to be run on (loaded) and addtional space for runtime. Handled by OS. OS also handles the running other proccesses apart from C program parrallely (maintains and manages processor states & also manages CPU schduling & also memory schduling with help of virtualization (provides safety as well as abstraction) and manages stdin and stdio, as well as errors, safety by maintaining regions in memory that have permissions (executable, readable and writeable)
//The C program makes use of storage locations that contain data (variables), the ability to manage storage location by user is with help of pointers.
										//Pointers are similar to variables, differ is only the ability for the compiler to realise the pointer as passing storage and variable as passing the data within. (for more pointer details visit grok)

//The control of sequence of statements executed (control flow), is done by looping statement: 	while -> chks condition (i.e. uses a cmp op to cmp 2 data units)
												//for   -> initialises a scoped variable (and uses cmp) Also has incr op at end of each i of body (continue statement for for is also modified to include incr when going to next i)
	//Scope in C (ability to manage asccessing vars such, inner most var if accessed if not available then outer) Scope resolved at compile time (uses symbol table to obatain vars) At asm level no local/global, they now hold they very value they were storing. (Python and intepreter/dynamically typed languages uses runtime symbol table to mange scope, in asm we have symbol table but resolving scope has to be done logically, py uses bytecode which is the asm equivalent to C's asm. It runs a Py VM that is built using C (cpython) and manages scope here)

	//Has another feature to control -> braces (determines the order of evaluation of statements and operations)

//Input statements -> when the c execution reaches input statement (calls read sys call) -> takes from stdio, it blocks the processs and is put at waiting queue. (this frees up the processor from this task) The os now chks the stdio i.e terminal buffer. (Works on interupt system, processing efficient, unlike busy waiting of polling)
//Output -> The C program forwards output to stdout, the OS forwards to terminal manager, and it iteprets the data sent and displays at terminal
	// cycles in printf scanf -> (a typical assignemnt operator takes 1-3 cycles) The cpu loads the format string 12 bytes so ~30 cycles (chk stdout ~5, buffer ~5; cpy str to buffer ~5, flush ~10, jump to syswrite ~5); The cpu prepares for sys call -> store registers, sp, pc -> ~100 cycles; switch to kernel space, resolves stuff, copies the txt from uesrspace to buffer ~ 100 cycles; sys exit to return to program execution including return the registers and user context ~50 cycles
		// the mouse and keyboard input also go through the cpu for processing, uses a special system of keyboard interrupt (unpredicted and higher priority event than planned program execution). Responds to keyboard interrupt event immediatley by pausing execution of program for a moment. here it would take ~20 cycles for processing these interrups alone
//Preprocessor directive: wrt compilation order of lexical, syntatical, semantic, code generation and optimization, the preprocessing is done bore all these and does, exact replacement of macro name to the literal text.
