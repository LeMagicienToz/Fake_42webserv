/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   String.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:32:44 by mconreau          #+#    #+#             */
/*   Updated: 2024/04/09 20:56:21 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<typename TYPE>
string
String::tostr(const TYPE &content)
{
	return (static_cast<const ostringstream&>((ostringstream() << dec << content)).str());
}
