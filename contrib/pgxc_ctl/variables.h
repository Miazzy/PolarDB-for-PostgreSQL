/*-------------------------------------------------------------------------
 *
 * variables.h
 *
 *    Variable handling module of Postgres-XC configuration and operation tool.
 *
 * Copyright (c) 2020, Alibaba Group Holding Limited
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (c) 2013 Postgres-XC Development Group
 *
 *-------------------------------------------------------------------------
 */
#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdio.h>
#include <stdlib.h>
#define NUM_HASH_BUCKET 128

typedef struct pgxc_ctl_var {
    struct pgxc_ctl_var *next;
    struct pgxc_ctl_var *prev;
    char    *varname;
    int        val_size;        /*
                             * current size of the allocated array including
                             * place to store the NULL pointer as an
                             * end-of-array marker
                             */

    int        val_used;        /* currently used values */

    char    **val;            /* 
                             * max (val_size - 1) values and NULL as the last
                             * element
                             */
} pgxc_ctl_var;


extern pgxc_ctl_var *var_head;
extern pgxc_ctl_var *var_tail;

typedef struct pgxc_var_hash {
    int        el_size;
    int        el_used;
    pgxc_ctl_var **el;
} pgxc_var_hash;


pgxc_var_hash var_hash[NUM_HASH_BUCKET];

void init_var_hash(void);
void add_var_hash(pgxc_ctl_var *var);
pgxc_ctl_var *new_var(char *name);
void add_val(pgxc_ctl_var *var, char *val);
void add_val_name(char *name, char *val);
pgxc_ctl_var *find_var(char *name);
char *sval(char *name);
char **aval(char *name);
int arraySizeName(char *name);
int arraySize(pgxc_ctl_var *var);
void print_vars(void);
void print_var(char *vname);
void reset_value(pgxc_ctl_var *var);
void assign_val(char *dest, char *src);
void assign_sval(char *name, char *val);
void assign_arrayEl(char *name, int idx, char *val, char *pad);
void replace_arrayEl(char *name, int idx, char *val, char *pad);
pgxc_ctl_var *confirm_var(char *name);
void reset_var_val(char *name, char *val);
void reset_var(char *name);
void remove_var(pgxc_ctl_var *var);
void reset_value(pgxc_ctl_var *var);
void log_var(char *name);
char **add_member(char **array, char *val);
void var_assign(char **dest, char *src);
char  *listValue(char *name);
char  *listValue_CM(char *name);
int extendVar(char *name, int newSize, char *def_value);
int doesExist(char *name, int idx);
void assign_arrayEl_internal(char *name, int idx, char *val, char *pad,
        int extend);

#define AddMember(a, b) do{if((a) == NULL) (a) = Malloc0(sizeof(char *)); (a) = add_member((a), (b));}while(0)
void clean_array(char **array);
#define CleanArray(a) do{clean_array(a); (a) = NULL;}while(0)
#define VAR(a) find_var(a)

int ifExists(char *name, char *value);
int IfExists(char *name, char *value);

#endif /* VARIABLES _H */
