/*
 * Copyright (c) 2020 Dengbo(dengweiw@hotmail.com)
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdarg.h>
#include <stdio.h>
#include "macro_paras_opt.h"
#include "easy_print.h"

// get timestamp
#define EASY_PRINT_TIME_GET() 0
// disable/enable all interrupt
#define EASY_PRINT_HW_INT_DIS() 0
#define EASY_PRINT_HW_INT_EN(...) 

unsigned char print_order = 0;

// STR_PRINT_W_BUF_LEN should be '1<<n'
#define STR_PRINT_W_BUF_LEN 0x20
#define STR_PRINT_W_BUF_LEN_MASK STR_PRINT_W_BUF_LEN - 1
struct str_print_w str_print_w_buf[STR_PRINT_W_BUF_LEN];
int str_w_buf_num_w = 0;
int str_w_buf_num_r = 0;

void str_buf_write_va_list(char *str, unsigned char para_c, ...)
{
    va_list Paras;
    unsigned int time = EASY_PRINT_TIME_GET();

    unsigned int level = EASY_PRINT_HW_INT_DIS();
    int str_w_buf_num_w_get = str_w_buf_num_w;
    str_w_buf_num_w++;
    str_w_buf_num_w &= STR_PRINT_W_BUF_LEN_MASK;
    int print_order_get = print_order++;
    EASY_PRINT_HW_INT_EN(level);

    struct str_print_w *str_print_w_buf_p = &str_print_w_buf[str_w_buf_num_w_get];

    str_print_w_buf_p->str_buf = str;
    str_print_w_buf_p->order = print_order_get;
    str_print_w_buf_p->para_c = para_c;
    str_print_w_buf_p->time = time;

    va_start(Paras, para_c);
    for (int i = 0; (i < para_c) && (i < STR_PRINT_W_PARAS_MAX); i++)
    {
        str_print_w_buf_p->para[i] = va_arg(Paras, unsigned int);
    }
    va_end(Paras);
}

void str_buf_write_array(struct str_print_w *str_print_w)
{
    unsigned int time = EASY_PRINT_TIME_GET();

    unsigned int level = EASY_PRINT_HW_INT_DIS();
    int str_w_buf_num_w_get = str_w_buf_num_w;
    str_w_buf_num_w++;
    str_w_buf_num_w &= STR_PRINT_W_BUF_LEN_MASK;
    int print_order_get = print_order++;
    EASY_PRINT_HW_INT_EN(level);

    struct str_print_w *str_print_w_buf_p = &str_print_w_buf[str_w_buf_num_w_get];

    memcpy(str_print_w_buf_p, str_print_w, sizeof(struct str_print_w));
    str_print_w_buf_p->order = print_order_get;
    str_print_w_buf_p->time = time;
}

void str_buf_read(struct str_print_r *str_print_r)
{
    struct str_print_w *str_print_w_buf_p = &str_print_w_buf[str_w_buf_num_r];
    str_w_buf_num_r++;
    str_w_buf_num_r &= STR_PRINT_W_BUF_LEN_MASK;

    str_print_r->str_buf = str_print_w_buf_p->str_buf;
    str_print_r->order = str_print_w_buf_p->order;
    str_print_r->para_c = str_print_w_buf_p->para_c;

    for (int i = 0; i < str_print_r->para_c; i++)
    {
        str_print_r->para[i] = str_print_w_buf_p->para[i];
    }

    return;
}

int str_buf_is_empty(void)
{
    return (str_w_buf_num_r == str_w_buf_num_w) ? 1 : 0;
}

void print_str_buf(void)
{
    unsigned char order;
    struct str_print_r str_print_r;

    while (!str_buf_is_empty())
    {
        str_buf_read(&str_print_r);
        printf("%03d\t", str_print_r.order);
        printf(str_print_r.str_buf, str_print_r.para[0],
               str_print_r.para[1], str_print_r.para[2], str_print_r.para[3]);
    }
    return;
}

// STR_PRINT_STRU_W_BUF_LEN should be '1<<n'
#define STR_PRINT_STRU_W_BUF_LEN 0x20
#define STR_PRINT_STRU_W_BUF_LEN_MASK STR_PRINT_STRU_W_BUF_LEN - 1
struct str_print_stru_w str_print_stru_w_buf[STR_PRINT_STRU_W_BUF_LEN];
int str_stru_w_buf_num_w = 0;
int str_stru_w_buf_num_r = 0;

void str_buf_write_stru(struct str_print_stru_w *str_print_stru_w)
{
    unsigned int time = EASY_PRINT_TIME_GET();

    unsigned int level = EASY_PRINT_HW_INT_DIS();
    int str_stru_w_buf_num_w_get = str_stru_w_buf_num_w;
    str_stru_w_buf_num_w++;
    str_stru_w_buf_num_w &= STR_PRINT_STRU_W_BUF_LEN_MASK;
    int print_order_get = print_order++;
    EASY_PRINT_HW_INT_EN(level);

    struct str_print_stru_w *str_print_stru_w_p = &str_print_stru_w_buf[str_stru_w_buf_num_w_get];

    memcpy(str_print_stru_w_p, str_print_stru_w, sizeof(struct str_print_stru_w));
    str_print_stru_w_p->order = print_order_get;
    str_print_stru_w_p->time = time;
}

void str_stru_buf_read(struct str_print_r *str_print_r)
{
    int i;
    int size;
    int x, y;
    int offset;

    struct str_print_stru_w *str_print_stru_w_p = &str_print_stru_w_buf[str_stru_w_buf_num_r];
    str_stru_w_buf_num_r++;
    str_stru_w_buf_num_r &= STR_PRINT_STRU_W_BUF_LEN_MASK;

    str_print_r->str_buf = str_print_stru_w_p->str_buf;
    str_print_r->order = str_print_stru_w_p->order;
    str_print_r->para_c = str_print_stru_w_p->para_c;
    str_print_r->time = str_print_stru_w_p->time;

    for (i = 0, offset = 0; i < str_print_r->para_c; i++)
    {
        x = i & 0x08;
        y = (i < 8) ? i : (i - 8);
        size = ((str_print_stru_w_p->para_size[x]) >> (y << 2)) & 0x0F;
        switch (size)
        {
        case 1:
            str_print_r->para[i] = *(unsigned char *)&str_print_stru_w_p->para[offset];
            break;
        case 2:
            str_print_r->para[i] = *(unsigned short *)&str_print_stru_w_p->para[offset];
            break;
        case 4:
            str_print_r->para[i] = *(unsigned int *)&str_print_stru_w_p->para[offset];
            break;
        // case 8:
        //     break;
        default:
            break;
        }
        offset += size;
    }

    return;
}

int str_stru_buf_is_empty(void)
{
    return (str_stru_w_buf_num_r == str_stru_w_buf_num_w) ? 1 : 0;
}

void print_str_stru_buf(void)
{
    unsigned char order;
    struct str_print_r str_print_r;

    while (!str_stru_buf_is_empty())
    {
        str_stru_buf_read(&str_print_r);
        printf("%03d\t%05d\t", str_print_r.order, str_print_r.time);
        printf(str_print_r.str_buf, str_print_r.para[0],
               str_print_r.para[1], str_print_r.para[2], str_print_r.para[3], str_print_r.para[4], str_print_r.para[5]);
    }
    return;
}

int main(int argc, void **argv)
{

    STR_BUF_WRITE_VA_LIST("hello");
    STR_BUF_WRITE_VA_LIST("hello %d %d %d %d %d", 0, 1, 2, 3, 4);
    STR_BUF_WRITE_ARRAY("hello %d %d %d %d", 0, 1, 2, 3, 4);
    print_str_buf();

    char t0 = 01;
    unsigned char t1 = 2;
    short t2 = 3;
    unsigned short t3 = 4;
    int t4 = 5;
    unsigned int t5 = 6;
    STR_BUF_WRITE_STRU("hello");
    STR_BUF_WRITE_STRU("hello %d %d %d %d %d", 0, 1, 2, 3, 4);
    STR_BUF_WRITE_STRU("hello %d %d %d %d %d %d", t0, t1, t2, t3, t4, t5);
    print_str_stru_buf();

    return 0;
}
