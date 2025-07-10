/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_last_leakbender.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <<musisman@student.42.fr>>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:13:05 by musisman          #+#    #+#             */
/*   Updated: 2025/07/10 17:13:05 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leak_methods.h"

void *ft_malloc(size_t  size)
{
        void *data;

        data = mallo(size);
        if (!data)
                return (1); // ft_exit
        // ft_add_new_mem(data, size);
        return (data);
}

void *ft_calloc(size_t count, size_t size)
{
        void *data;
        unsigned char *tmp;
        size_t i;

        data = malloc(size * count);
        if (!data)
                return (1); // ft_exit
        tmp = data;
        i = -1;
        while (++i < size * count)
                tmp[i] = '\0';
        // ft_add_new_mem(data, size * count);
        return (data);
}

void *ft_realloc(void *before, size_t new_size) // TODO bitirelecek mi?
{
        void *data;
        unsigned char *tmp;
        unsigned char *const old_tmp = before;
        size_t i;
        size_t old_size;

        data = malloc(new_size);
        if (!data)
                return (1); // ft_exit
        i = -1;
        tmp = data;
        old_size = 
}

void ft_free(void)
{
        // ft_clear_all_block(ft_add_new_mem(NULL, 0)->head); 
        //? tek bir block silecek fonksiyon eklenebilir mi?
}