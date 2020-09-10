COMPILER = gcc

LEXER_PATH = ./lexer/

PARSER_PATH = ./parser/

PARAMETER_LIST_PATH = ./parameterList/

BUILD_PATH = ./build/

all : $(BUILD_PATH)lexer $(BUILD_PATH)parser


test : $(BUILD_PATH)lexer $(BUILD_PATH)parser test/test.c $(BUILD_PATH)parameterList
	gcc -o $(BUILD_PATH)test test/test.c $(BUILD_PATH)lexer $(BUILD_PATH)parser $(BUILD_PATH)parameterList -I parameterList/ -I build/


$(BUILD_PATH)parameterList : $(PARAMETER_LIST_PATH)parameterList.c $(PARAMETER_LIST_PATH)parameterList.h $(PARAMETER_LIST_PATH)parameterListParserApi.h
	./createBuildDir.sh && gcc -c -o $@ $<


$(BUILD_PATH)parser : $(BUILD_PATH)parser.c ./parameterList/parameterList.c 
	./createBuildDir.sh && gcc  -c -o $@ $< -I ./parameterList/

	
$(BUILD_PATH)parser.c : $(PARSER_PATH)grammar.y
	./createBuildDir.sh && bison $< -o $(BUILD_PATH)parser.c



#LEXER

$(BUILD_PATH)lexer : $(BUILD_PATH)lexer.c
	./createBuildDir.sh && gcc -c -o $@ $< -I $(BUILD_PATH)


$(BUILD_PATH)lexer.c : $(LEXER_PATH)lexicalRules.l $(BUILD_PATH)parser.h
	./createBuildDir.sh && flex -o $@ $<


$(BUILD_PATH)parser.h : $(PARSER_PATH)grammar.y
	./createBuildDir.sh && bison -d $< -o $(BUILD_PATH)parser.c