/*
 * Copyright (c) 2020 Dengbo(dengweiw@hotmail.com)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __EASY_PRINT_H__
#define __EASY_PRINT_H__

#include "macro_paras_opt.h"
#include "macro_struct.h"
#include "macro_type.h"

#define STR_BUF_WRITE_VA_LIST(str, ...)                                \
    do                                                                 \
    {                                                                  \
        int macro_paras_num = GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__);  \
        const char *strbuf = "L" MACRO_STR_LINE_NUM " " str "\n";      \
        str_buf_write_va_list(strbuf, macro_paras_num, ##__VA_ARGS__); \
    } while (0)

#define STR_BUF_WRITE_ARRAY(str, ...)                                                                                         \
    do                                                                                                                        \
    {                                                                                                                         \
        int macro_paras_num = GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__);                                                         \
        unsigned int macro_paras[] = {__VA_ARGS__};                                                                           \
        struct str_print_w str_print_w;                                                                                       \
        const char *strbuf = "L" MACRO_STR_LINE_NUM " " str "\n";                                                             \
        str_print_w.para_c = macro_paras_num;                                                                                 \
        for (int i = 0; (i < macro_paras_num) && (i < (sizeof(((struct str_print_w *)0)->para)) / sizeof(unsigned int)); i++) \
        {                                                                                                                     \
            str_print_w.para[i] = macro_paras[i];                                                                             \
        }                                                                                                                     \
        str_print_w.str_buf = strbuf;                                                                                         \
        str_buf_write_array(&str_print_w);                                                                                    \
    } while (0)

#define _GET_TYPE_SIZE(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9) ((_0) << 0) | ((_1) << 4) | ((_2) << 8) |        \
                                                                   ((_3) << 12) | ((_4) << 16) | ((_5) << 20) | \
                                                                   ((_6) << 24) | ((_7) << 28),                 \
                                                               ((_8) << 0) | ((_9) << 4)
#define GET_TYPE_SIZE(...) _GET_TYPE_SIZE(__VA_ARGS__)

#define _TEMP_PARAS(num, para)    para;
#define TEMP_PARAS(num, para)     MACRO_PARAS_NOTDEAL_0PARAS(_TEMP_PARAS, para)

#define STR_BUF_WRITE_STRU(str, ...)                                                              \
    do                                                                                            \
    {                                                                                             \
        MACRO_PARAS_ENUM_OPT(TEMP_PARAS, GEN_TEMP_VARS(__VA_ARGS__));                             \
        GEN_STRUCT_AUTO(GET_TEMP_VARS(__VA_ARGS__));                                              \
        if (sizeof(GET_STRUCT_AUTO_TYPE()) > STR_PRINT_STRU_W_PARAS_MAX)                          \
        {                                                                                         \
            break;                                                                                \
        }                                                                                         \
        int macro_paras_num = GET_MACRO_PARAS_TOTAL_NUM(__VA_ARGS__);                             \
        unsigned int macro_paras_size[] = {GET_TYPE_SIZE(GET_MACRO_PARAS_SIZE_FIX(__VA_ARGS__))}; \
        struct str_print_stru_w str_print_stru_w;                                                 \
        const char *strbuf = "L" MACRO_STR_LINE_NUM " " str "\n";                                 \
        SET_TEMP_VARS(__VA_ARGS__);                                                               \
        SET_STRUCT_AUTO(GET_TEMP_VARS(__VA_ARGS__));                                              \
        str_print_stru_w.para_c = macro_paras_num;                                                \
        memcpy(str_print_stru_w.para, &GET_STRUCT_AUTO_VAR(), sizeof(GET_STRUCT_AUTO_TYPE()));    \
        memcpy(str_print_stru_w.para_size, macro_paras_size, sizeof(macro_paras_size));           \
        str_print_stru_w.str_buf = strbuf;                                                        \
        str_buf_write_stru(&str_print_stru_w);                                                    \
    } while (0)

#define STR_PRINT_W_PARAS_MAX 10
#define STR_PRINT_R_PARAS_MAX 10
#define STR_PRINT_STRU_W_PARAS_MAX 20

struct str_print_w
{
    char *str_buf;
    unsigned char order;
    unsigned char para_c;
    unsigned int time;
    unsigned int para[STR_PRINT_W_PARAS_MAX];
};

struct str_print_r
{
    char *str_buf;
    unsigned char order;
    unsigned char para_c;
    unsigned int time;
    unsigned int para[STR_PRINT_R_PARAS_MAX];
};
struct str_print_stru_w
{
    char *str_buf;
    unsigned int para_size[2];
    unsigned char order;
    unsigned char para_c;
    unsigned int time;
    unsigned char para[STR_PRINT_STRU_W_PARAS_MAX];
};

#endif