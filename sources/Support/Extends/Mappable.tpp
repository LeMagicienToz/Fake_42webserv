/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mappable.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:03:15 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/18 22:23:54 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<typename KEY, typename VAL>
Mappable<KEY,VAL>::Mappable()
{
}

template<typename KEY, typename VAL>
Mappable<KEY,VAL>::~Mappable()
{
}

template<typename KEY, typename VAL>
Mappable<KEY,VAL>::Mappable(const Mappable &src)
{
	*this = src;
}

template<typename KEY, typename VAL>
void
Mappable<KEY,VAL>::add(const KEY &key, const VAL &value)
{
	if (!this->has(key)) this->set(key, value);
}

template<typename KEY, typename VAL>
bool
Mappable<KEY,VAL>::has(const KEY &key) const
{
	return (this->_map.find(key) != this->_map.end());
}

template<typename KEY, typename VAL>
VAL
Mappable<KEY,VAL>::get(const KEY &key, const VAL &other)
{
	return (this->has(key) ? this->_map[key] : other);
}

template<typename KEY, typename VAL>
void
Mappable<KEY,VAL>::set(const KEY &key, const VAL &value)
{
	this->_map[key] = value;
}

template<typename KEY, typename VAL>
size_t
Mappable<KEY,VAL>::size() const
{
	return (this->_map.size());
}

template<typename KEY, typename VAL>
Mappable<KEY,VAL>&
Mappable<KEY,VAL>::operator=(const Mappable<KEY,VAL> &rhs)
{
	this->_map = rhs._map;
	return (*this);
}

template<typename KEY, typename VAL>
VAL&
Mappable<KEY,VAL>::operator[](const KEY &key)
{
	return (this->find(key)->second);
}
