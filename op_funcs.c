#include "monty.h"

/**
 * push - pushes an element to the stack
 *
 * @stack: stack_t **, head of doubly linked list
 * @line_number: unsigned int, number of the current line of file
 *
 * Return: void
 */
void push(stack_t **stack, unsigned int line_number)
{
	int n = 0;
	stack_t *new = (stack_t *) malloc(sizeof(stack_t));

	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(stack);
		free(new);
		fclose(glob.file);
		glob.file = NULL;
		free(glob.tok);
		glob.tok = NULL;
		exit(EXIT_FAILURE);
	}

	glob.tok = strtok(NULL, " \t\n");

	if (!glob.tok)
	{
		fprintf(stderr, "L%u: usage: push integer", line_number);
		free_stack(stack);
		free(new);
		fclose(glob.file);
		glob.file = NULL;
		free(glob.tok);
		glob.tok = NULL;
		exit(EXIT_FAILURE);
	}

	n = atoi(glob.tok);

	new->n = n;
	new->prev = NULL;
	new->next = (*stack);

	(*stack)->prev = new;
	(*stack) = new;
}


/**
 * pall - prints all the values on the stack,
 * starting from the top of the stack
 *
 * @stack: stack_t **, head of doubly linked list
 * @line_number: unsigned int, number of the current line of file
 *
 * Return: void
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *node = *stack;

	(void) line_number;

	while (node != NULL)
	{
		printf("%d\n", node->n);
		node = node->next;
	}
}
