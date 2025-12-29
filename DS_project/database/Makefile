# the 'make' cmd calls this scripts
# script run with no args, calls from all label.
# if target not found IN CURRENT DIRECTORY, searches subsequent LABELS, recurses this process.
# upon finding a LABEL, execute its body, and recursively back to parent (all); then executes all's body
flags = -Wall -O2 -std=c2x

all: tree	# need tree before continuing to all
	ls

tree: tree.o	# to obtain tree, need tree.o
	gcc ${flags} $^ -o tree
	rm tree.o

tree.o: tree.s	# to obtain tree.o, need tree.s
	gcc ${flags} -c $^
	rm tree.s

tree.s: tree.c 	# to obtain tree.s, need tree.c
	gcc ${flags} -S $^