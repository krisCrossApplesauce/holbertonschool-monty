#include "monty.h"

globe_t glob;

/**
 * check_op - runs the function that corresponds with the command
 * specified in the current line of the given file
 *
 * @tok: contents of the current line in the given file
 * @stack: doubly linked list, the stack used by the commands
 * @ln: unsigned int, line number
 *
 * Return: void
 */
void check_op(char *tok, stack_t **stack, unsigned int ln)
{
	int i = 0;
	instruction_t stuff[] = {
		{ "push", push },
		{ "pall", pall }
	};

	while (i < 2)
	{
		if (*stuff[i].opcode == tok)
		{ return (stuff[i].f(stack, ln)); }

		i++;
	}

	fprintf(stderr, "L%d: unknown instruction %s\n", ln, tok);
	free(stack);
	fclose(file);
	exit(EXIT_FAILURE);
}


/**
 * main - runs the monty interpreter
 *
 * @argc: int, number of arguments
 * @argv: str, the arguments
 *
 * Return: int, 0 if succeed, 1 if fail
 */
int main(int argc, char **argv)
{
	glob->file = NULL;
	glob->tok = NULL;
	stack_t *stack = NULL;
	char *line_buff = NULL;
	size_t buff_size = 0;
	unsigned int line_num = 1;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");

	if (!file_contents)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&line_buff, &buff_size, file) != EOF)
	{
		tok = strtok(line_buff, " \t\n");
		free(line_buff);
		line_buff = NULL;
		check_op(&tok, &stack, line_num);
	}

	free(line_buff);
	fclose(file);
	free_stack(&stack);
	return (EXIT_SUCCESS);
}
