
generate: lexer.l parser.y
	bison -d parser.y
	flex --header-file=scanner.h --outfile=scanner.c lexer.l

clean:
	rm -rf parser.tab.c parser.tab.h scanner.c scanner.h
