/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dicisner <dicisner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:23:48 by dicisner          #+#    #+#             */
/*   Updated: 2021/09/14 17:55:49 by dicisner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}
