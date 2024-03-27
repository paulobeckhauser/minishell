/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_set_redirection_priority.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:12:56 by sfrankie          #+#    #+#             */
/*   Updated: 2024/03/27 20:53:34 by sfrankie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	delete_repeating_redirection_tokens(t_token_node **tokens)
{
	t_token_node	*head;

	head = NULL;
	while (*tokens)
	{
		if ((*tokens)->token.type == PIPE)
			*tokens = (*tokens)->next;
		mark_last_in_redirection(*tokens);
		mark_last_out_redirection(*tokens);
		delete_and_close_not_used_redirections(tokens, &head);
	}
	*tokens = head;
}

void	delete_and_close_not_used_redirections(t_token_node **tokens, t_token_node **head)
{
	t_token_node	*tmp;
	t_token_node	*previous_token;

	tmp = NULL;
	previous_token = NULL;
	while (*tokens && (*tokens)->token.type != PIPE)
	{
		if ((*tokens)->token.type == REDIRECTION && !(*tokens)->token.last_redirection)
		{
			tmp = (*tokens);
			close_token_fd(*tokens);
			if (previous_token)
				previous_token->next = (*tokens)->next;
			*tokens = (*tokens)->next;
			free(tmp);
		}
		else
		{
			if (!*head)
				*head = *tokens;
			previous_token = *tokens;
			*tokens = (*tokens)->next;
		}
	}
}

void	mark_last_in_redirection(t_token_node *tokens)
{
	t_token_node	*current_last;

	current_last = NULL;
	while (tokens && tokens->token.type != PIPE)
	{
		if (tokens->token.type == REDIRECTION
			&& tokens->token.t_value.single_ptr[0] == '<')
			current_last = tokens;
		tokens = tokens->next;
	}
	if (current_last)
		current_last->token.last_redirection = true;
}

void	mark_last_out_redirection(t_token_node *tokens)
{
	t_token_node	*current_last;

	current_last = NULL;
	while (tokens && tokens->token.type != PIPE)
	{
		if (tokens->token.type == REDIRECTION
			&& tokens->token.t_value.single_ptr[0] == '>')
			current_last = tokens;
		tokens = tokens->next;
	}
	if (current_last)
		current_last->token.last_redirection = true;
}

void	close_token_fd(t_token_node *tokens)
{
	if (tokens->token.in.file_name && !tokens->token.in.heredoc)
	{
		if (close(tokens->token.in.fd) == -1)
			perror("close");
	}
	else if (tokens->token.out.file_name)
	{
		if (close(tokens->token.out.fd) == -1)
			perror("close");
	}
}
