/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mappable.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mconreau <mconreau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:54:48 by mconreau          #+#    #+#             */
/*   Updated: 2024/05/08 16:17:26 by mconreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

using namespace std;

template<typename KEY, typename VAL>
class Mappable
{
	private  :
		map<KEY,VAL>				_map;

	protected:
									Mappable();
		virtual						~Mappable() = 0;

	public   :
									Mappable(const Mappable &src);

		void						add(const KEY &key, const VAL &value);
		VAL							get(const KEY &key, const VAL &other);
		bool						has(const KEY &key) const;
		void						set(const KEY &key, const VAL &value);
		size_t						size() const;

		Mappable&					operator=(const Mappable<KEY,VAL> &rhs);
		VAL&						operator[](const KEY &key);
};

#include "Support/Extends/Mappable.tpp"
