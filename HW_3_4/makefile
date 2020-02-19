
## To run:
## make args=“arguments go here”

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

all:
	gcc -Wall -g -o ./commands commands.c
	gcc -Wall -g -o hw3 ./hw3.c
	./hw3 $(args)

clean:
	rm -f hw3
