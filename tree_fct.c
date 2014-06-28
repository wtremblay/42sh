/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 18:00:43 by wtrembla          #+#    #+#             */
/*   Updated: 2014/06/26 18:58:13 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		place_node(int pos, int prev_pos)
{
	if (pos == prev_pos * 2 + 1)
		return (1);
	else if (pos == prev_pos * 2)
		return (0);
	if ((pos % 2) != 0)
		pos = pos - 1;
	pos = pos / 2;
	return (place_node(pos, prev_pos));
}

t_node			*new_node(char *type, char *word, int pos)
{
	char		*tmp1;
	char		*tmp2;
	t_node		*elem;

	tmp1 = ft_strtrim(type);
	tmp2 = ft_strtrim(word);
	if (!(elem = (t_node *)malloc(sizeof(t_node))))
		ft_error(ERROR(SH, E_MEMALLOC), "(adding node)", 'n');
	else
	{
		elem->type = ft_strdup(tmp1);
		elem->word = ft_strdup(tmp2);
		elem->pos = pos;
		elem->left = NULL;
		elem->right = NULL;
		ft_strdel(&tmp1);
		ft_strdel(&tmp2);
	}
	return (elem);
}

void			add_node(t_node **tree, t_node *elem)
{
	t_node		*tmp_tree;
	t_node		*tmp_node;

	tmp_tree = *tree;
	if (tmp_tree)
	{
		while (tmp_tree)
		{
			tmp_node = tmp_tree;
			if (place_node(elem->pos, tmp_tree->pos))
			{
				tmp_tree = tmp_tree->right;
				if (!tmp_tree)
					tmp_node->right = elem;
			}
			else
			{
				tmp_tree = tmp_tree->left;
				if (!tmp_tree)
					tmp_node->left = elem;
			}
		}
	}
	else
		*tree = elem;
}

void			del_tree(t_node **tree)
{
	if (*tree)
	{
		del_tree(&(*tree)->left);
		del_tree(&(*tree)->right);
		ft_strdel(&(*tree)->type);
		ft_strdel(&(*tree)->word);
		free(*tree);
		*tree = NULL;
	}
}
