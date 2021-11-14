/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Assertion macros
*/

#pragma once

#define STATIC_ASSERT_IS_BASE_OF(Base, Class) \
    static_assert(std::is_base_of<Base, Class>::value, #Class " must inherit from " #Base);

#define STATIC_ASSERT_IS_COMPONENT(T) \
    STATIC_ASSERT_IS_BASE_OF(ComponentBase, T)

#define STATIC_ASSERT_IS_SYSTEM(T) \
    STATIC_ASSERT_IS_BASE_OF(ASystem, T)
