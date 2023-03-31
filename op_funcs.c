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
		free(stack);
		free(new);
		fclose(file);
		return (EXIT_FAILURE);
	}

	tok = strtok(NULL, " \t\n");

	if (!tok || !(n = atoi(tok)))
	{
		fprintf(stderr, "L%s: usage: push integer", line_number);
		free(stack);
		free(new);
		fclose(file);
		return (EXIT_FAILURE);
	}

	new->n = tok;
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

	while (node != NULL)
	{
		printf("%d\n", node->n);
		node = node->next;
	}
}
