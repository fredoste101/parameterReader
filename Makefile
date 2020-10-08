COMPILER = gcc


PARAMETER_READER_PATH = ./parameterReader/

LEXER_PATH = ./lexer/

PARSER_PATH = ./parser/

PARAMETER_LIST_PATH = ./parameterList/

BUILD_PATH = ./build/

TEST_PATH = ./test/

all : $(BUILD_PATH)lexer $(BUILD_PATH)parser


test : $(TEST_PATH)test.c $(BUILD_PATH)parameterReader
	gcc -o $(BUILD_PATH)test test/test.c $(BUILD_PATH)parameterReader $(BUILD_PATH)parameterList $(BUILD_PATH)lexer $(BUILD_PATH)parser -I $(PARAMETER_READER_PATH) -I $(PARAMETER_LIST_PATH)



#PARAMETERREADER - main functionality

$(BUILD_PATH)parameterReader : $(PARAMETER_READER_PATH)parameterReader.c $(PARAMETER_READER_PATH)parameterReader.h $(BUILD_PATH)lexer $(BUILD_PATH)parser $(BUILD_PATH)parameterList
	./createBuildDir.sh && gcc -c -o $(BUILD_PATH)parameterReader $(PARAMETER_READER_PATH)parameterReader.c  -I $(PARAMETER_LIST_PATH) -I $(BUILD_PATH)



#PARAMETERLIST

$(BUILD_PATH)parameterList : $(PARAMETER_LIST_PATH)parameterList.c $(PARAMETER_LIST_PATH)parameterList.h $(PARAMETER_LIST_PATH)parameterListParserApi.h
	./createBuildDir.sh && gcc -c -o $@ $<






#LEXER

$(BUILD_PATH)lexer : $(BUILD_PATH)lexer.c
	./createBuildDir.sh && gcc -c -o $@ $< -I $(BUILD_PATH) -I $(PARAMETER_LIST_PATH)


$(BUILD_PATH)lexer.c : $(LEXER_PATH)lexicalRules.l $(BUILD_PATH)parser.h
	./createBuildDir.sh && flex --header-file=$(BUILD_PATH)lexer.h -o $@ $<



#PARSER

$(BUILD_PATH)parser.h : $(PARSER_PATH)grammar.y
	./createBuildDir.sh && bison -d $< -o $(BUILD_PATH)parser.c

$(BUILD_PATH)parser : $(BUILD_PATH)parser.c ./parameterList/parameterList.c 
	./createBuildDir.sh && gcc  -c -o $@ $< -I ./parameterList/

	
$(BUILD_PATH)parser.c : $(PARSER_PATH)grammar.y
	./createBuildDir.sh && bison $< -o $(BUILD_PATH)parser.c