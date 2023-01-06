all : SAeimages

SAeimages : main.o bitmap.o image_editing.o
	gcc -o SAeimages main.o bitmap.o image_editing.o -lm

main.o : main.c
	gcc -c -Wall -Wextra main.c

bitmap.o : bitmap.c
	gcc -c -Wall -Wextra bitmap.c

image_editing.o : image_editing.c
	gcc -c -Wall -Wextra image_editing.c
	
clean :
	rm -rf *.o
