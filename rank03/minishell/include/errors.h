/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcosta-f <tcosta-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:18:23 by bschwell          #+#    #+#             */
/*   Updated: 2025/02/26 23:45:09 by tcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <sysexits.h>

/**
 * @brief Error Codes:
 * C error codes:
 * https://manpages.ubuntu.com/manpages/noble/man3/sysexits.h.3head.html
 * Bash Standard Errors: https://tldp.org/LDP/abs/html/exitcodes.html
 */

/* Bash Standard Errors */
# define EX_OK				0
# define EX_GENERICERR		1
# define EX_BUILTINERR		2
# define EX_EXECERR			126
# define EX_NOTFOUNDERR		127
# define EX_EXITARGERR		128
# define EX_OUTOFRANGEERR	255

/* Error Messages */
# define MSG_ERR_EXIT		"exit\nminishell: exit:"

#endif /* ERRORS_H */
