CFLAGS 			=	-Wall -Wextra -Werror -std=c++17
CHECKFLAGS 		= 	-lgtest -lgtest_main -pthread

REPORTFOLDER	=	report/
REPORTFILE		=	$(REPORTFOLDER)gcov_report.info

all: clean build

build:
	g++ $(CFLAGS)  -c *.cc $(CHECKFLAGS)
	g++ $(CFLAGS) -o s21_matrix *.o tests/tests.cc  $(CHECKFLAGS)
	
style: auto_formatting
	clang-format -i -n *.cc tests/*.cc *.h

s21_matrix_oop.a:
	ar rc s21_matrix_oop.a *.cc
	ranlib s21_matrix_oop.a

leaks: test
	valgrind --leak-check=full ./test

auto_formatting:
	clang-format -i *.cc *.h tests/*.cc
	clang-format -i *.cc *.h tests/*.cc

testing: clean
	g++ $(CFLAGS)  -c *.cc $(CHECKFLAGS)
	g++ $(CFLAGS) -o s21_matrix *.o run/run.cc  $(CHECKFLAGS)
	./s21_matrix


test: clean
	g++ $(CFLAGS)  -c tests/tests.cc $(CHECKFLAGS)
	g++ $(CFLAGS) *.o --coverage *.cc -o test $(CHECKFLAGS)
	./test

gcov_report: test
	mkdir -p gcov/
	mkdir report/
	lcov -t "s21_matrix_oop.a" -o $(REPORTFILE) -c -d .
	genhtml $(REPORTFILE) -o $(REPORTFOLDER)
	open $(REPORTFOLDER)index.html

run:
	./s21_matrix 

run_test:
	g++ $(CFLAGS)  -c *.cc $(CHECKFLAGS)
	g++ $(CFLAGS) -o s21_matrix *.o run/run.cc
	./s21_matrix 

clean:
	rm -rf *.o s21_matrix *.a *.gcno report *.gcov test *.gcda *.zip gcov .vs*

push:
	git add --all
	git commit -ms
	git push --all
