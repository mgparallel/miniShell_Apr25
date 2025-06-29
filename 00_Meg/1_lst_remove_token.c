#include "minishell.h"

// int    lst_rm_token(t_token **lst, t_token **cur_token)
// {
//     t_token *prev;
//     t_token *temp;
//     int if_space;

//     if_space = (*cur_token)->has_leading_space;
//     prev = *lst;
//     if (*lst == *cur_token)
//     {
//         temp = *lst;
//         *lst = temp->next;
//         free(temp->value);
//         free(temp);
//         *cur_token = temp;
//         return (if_space);
//     }
// 	if (!(*cur_token)->next)
// 		temp = NULL;
// 	else
// 		temp = (*cur_token)->next;
//     while (prev->next != *cur_token)
//     	prev = prev->next;
//     prev->next = temp;
//     free((*cur_token)->value);
//     free(*cur_token);
//     *cur_token = temp;
//     return (if_space);
// }

int    lst_rm_token(t_token **lst, t_token **cur_token_ptr) // Renamed for clarity
{
    t_token *token_to_free;
    t_token *next_node_in_list; // This will hold the node that comes *after* the removed one
    t_token *prev;
    int if_space;

    // Basic null checks
    if (!lst || !cur_token_ptr || !*cur_token_ptr)
    {
        fprintf(stderr, "Error: Invalid input to lst_rm_token\n");
        return (0); // Or an error code / handle appropriately
    }

    token_to_free = *cur_token_ptr; // The node currently pointed to by the caller's iterator
    if_space = token_to_free->has_leading_space; // Save the space info

    // Determine the *next* node BEFORE any freeing or relinking
    next_node_in_list = token_to_free->next;

    // Case 1: Removing the head of the list
    if (*lst == token_to_free)
    {
        *lst = next_node_in_list; // Update the head of the list
    }
    // Case 2: Removing a non-head node
    else
    {
        prev = *lst;
        while (prev && prev->next != token_to_free)
            prev = prev->next;

        if (!prev)
        {
            // Error: token_to_free not found in list (should not happen if logic is sound)
            fprintf(stderr, "Warning: Token to remove not found in list during traversal.\n");
            // You might choose to return an error, but try to proceed with freeing.
            // For now, let's assume it was found or this is a critical error.
            // If it wasn't found, then prev->next = next_node_in_list will likely segfault.
            // A more robust error handling would be needed here.
            return (if_space);
        }
        prev->next = next_node_in_list; // Link previous node to the one *after* token_to_free
    }

    // Now, free the memory of the token_to_free
    free(token_to_free->value);
    free(token_to_free);

    // CRITICAL: Update the caller's pointer to the *next* node in the list
    *cur_token_ptr = next_node_in_list;

    return (if_space);
}