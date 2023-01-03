/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isaad <isaad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:30:30 by bnaji             #+#    #+#             */
/*   Updated: 2023/01/03 21:56:50 by isaad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{
  template<bool Cond, class T = void> struct enable_if {};
  template<class T> struct enable_if<true, T> { typedef T type; };
}

#endif