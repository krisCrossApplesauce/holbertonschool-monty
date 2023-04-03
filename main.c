#include "monty.h"

globe_t glob;

/**
 * check_op - runs the function that corresponds with the command
 * specified in the current line of the given file
 *
 * @stack: doubly linked list, the stack used by the commands
 * @ln: unsigned int, line number
 *
 * Return: void
 */
void check_op(stack_t **stack, unsigned int ln)
{
	int i;
	instruction_t stuff[] = {
		{"push", push},
		{"pall", pall}
	};

	for (i = 0; stuff[i].opcode; i++)
	{
		if (strcmp(stuff[i].opcode, glob.tok) == 0)
		{
			stuff[i].f(stack, ln);
			return;
		}
	}

	fprintf(stderr, "L%d: unknown instruction %s\n", ln, glob.tok);
	fclose(glob.file);
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
	stack_t *stack = NULL;
	char *line_buff = NULL;
	size_t buff_size = 0;
	unsigned int line_num = 1;

	glob.file = NULL;
	glob.tok = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	glob.file = fopen(argv[1], "r");

	if (!glob.file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&line_buff, &buff_size, glob.file) != EOF)
	{
		glob.tok = strtok(line_buff, " \t\n");
		check_op(&stack, line_num);
		free(line_buff);
		line_buff = NULL;
	}

	if (stack)
	{ free_stack(&stack); }

	fclose(glob.file);

	return (EXIT_SUCCESS);
}


/**
 * free_stack - frees a stack
 *
 * @stack: the stack to be freed
 *
 * Return: void
 */
void free_stack(stack_t **stack)
{
	stack_t *node;

	while (*stack != NULL)
	{
		node = *stack;
		*stack = (*stack)->next;

		free(node);
	}

	free(*stack);
}
