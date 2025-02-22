/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:24:28 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/22 20:37:06 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
When handling infile and outfile, understand that each commands has an input and an output.
In some commands as cat, the input can be tricky because it can be in the argument of the command
or as the stdin of the command.
- < infile cat -e
- cat -e infile

When there is an input redirection for a command in a pipe, the output of the previous
command is not looked.

Also note that if a command has an output redirection, the result of the command will be transmetted
to the output redirection, but also to the next command in the pipeline

If an input is invalid (not the right) and open fail just stop and send the error and pass to the next command
For output i don't know.

When a here_doc is called, he has the prioirty, understand that

A good thing can be to understand with a lot of redirection how to data flow betweem files
*/