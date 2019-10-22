/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*   File....: ratpywrite.c                                                  */
/*   Name....: Python Format File Writer                                     */
/*   Author..: Thorsten Koch, Tomasz Pawlak                                  */
/*   Copyright by Authors, All rights reserved                               */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 * Copyright (C) 2003-2018 by Thorsten Koch <koch@zib.de>
 * Copyright (C) 2018 by Tomasz Pawlak <tpawlak@cs.put.poznan.pl>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <gmp.h>
#include <unistd.h>

#include "zimpl/lint.h"
#include "zimpl/mshell.h"
#include <stdbool.h>
#include "zimpl/gmpmisc.h"
#include "zimpl/ratlptypes.h"
#include "zimpl/numb.h"
#include "zimpl/bound.h"
#include "zimpl/mme.h"
#include "zimpl/mono.h"
#include "zimpl/term.h"
#include "zimpl/ratlp.h"
#include "zimpl/ratlpstore.h"
#include "zimpl/random.h"
#include "zimpl/elem.h"
#include "zimpl/tuple.h"
#include "zimpl/hash.h"
#include "zimpl/set.h"
#include "zimpl/set4.h"
#include "zimpl/entry.h"


#define IN(a, b, c) (a <= b && b <= c)

enum SET_RELATION {SET_EQUAL = 0, SET_SUBSET = 1, SET_SUPERSET = 2, SET_DIFFERENT = 4};

extern char* strip_extension(char* filename);
extern const char* strip_path(const char* filename);
extern const Symbol* symbol_get_all(void);

struct symbol
{
   SID
   const char*  name;
   int          size; // total number of entries
   int          used; // number of used entries
   int          extend; // number of number of entries added when extending entries
   SymbolType   type;
   Set*         set;
   Hash*        hash;
   Entry**      entry;
   Entry*       deflt;
   Symbol*      next;
};


static char* symbol_get_index_types(const Symbol* sym) {
    const Tuple* tuple;
    const Elem* elem;
    const int dim = sym->set->head.dim;
    char type;
    char *types = malloc(sizeof(char) * (dim+1));
    memset(types, 0, dim+1);

    for(int i = 0; i < sym->used; i++)
    {
        tuple = entry_get_tuple(sym->entry[i]);
        for(int j = 0; j < dim; j++)
        {
            elem = tuple_get_elem(tuple, j);
            type = elem_get_type(elem) == ELEM_NUMB ? 'N' : 'S';
            switch(types[j]) {
                case 0:
                    types[j] = type;
                    break;
                case 'N':
                case 'S':
                    if (types[j] != type)
                        types[j] = '?'; // varying
                    break;
            }
        }
    }
    return types;
}

static char* symbol_get_value_types(const Symbol* sym) {
    Tuple* tuple;
    const Elem* elem;
    const Set* set = sym->used > 0 ? entry_get_set(sym->entry[0]) : NULL;
    int dim = set != NULL ? set->head.dim : 0;
    char type;
    char *types = malloc(sizeof(char) * (dim+1));
    memset(types, 0, dim+1);

    for(int i = 0; i < sym->used; i++)
    {
        set = entry_get_set(sym->entry[i]);

        SetIter* iter = set_iter_init(set, NULL);
        while(NULL != (tuple = set_iter_next(iter, set)))
        {
            for(int j = 0; j < dim; j++)
            {
                elem = tuple_get_elem(tuple, j);
                type = elem_get_type(elem) == ELEM_NUMB ? 'N' : 'S';
                switch(types[j]) {
                    case 0:
                        types[j] = type;
                        break;
                    case 'N':
                    case 'S':
                        if (types[j] != type)
                            types[j] = '?'; // varying
                        break;
                }
            }

            tuple_free(tuple);
        }
        set_iter_exit(iter, set);
    }

    return types;
}

static void write_name(FILE* fp, const char* name, int var_number)
{
   assert(fp   != NULL);
   assert(name != NULL);

   // fprintf(fp, "%s", s);

   char* tmp_name = (char*)malloc(sizeof(char)*100);
   lps_makename(tmp_name, 100, name, var_number);
   fprintf(fp, "%s", tmp_name);
   free((void*)tmp_name);
}

static void write_lhs(FILE* fp, const Con* con, ConType type)
{
   assert(fp  != NULL);
   assert(con != NULL);
   
   switch(type)
   {
   case CON_RHS :
   case CON_LHS :
   case CON_EQUAL :
      break;
   case CON_RANGE :
      mpq_out_str(fp, 10, con->lhs);
      fprintf(fp, " <= ");
      break;
   default :
      abort();
   }
}

static void write_rhs(FILE* fp, const Con* con, ConType type)
{
   assert(fp  != NULL);
   assert(con != NULL);
   
   switch(type)
   {
   case CON_RHS :
   case CON_RANGE :
      fprintf(fp, " <= ");
      mpq_out_str(fp, 10, con->rhs);
      break;
   case CON_LHS :
      fprintf(fp, " >= ");
      mpq_out_str(fp, 10, con->lhs);
      break;
   case CON_EQUAL :
      fprintf(fp, " == ");
      mpq_out_str(fp, 10, con->rhs);
      break;
   default :
      abort();
   }
   //fprintf(fp, "\n");
}

static void write_row(
   FILE* fp,
   const Con* con)
{
   const Nzo* nzo;
   int        cnt = 0;

   assert(fp   != NULL);
   assert(con  != NULL);
   
   for(nzo = con->first; nzo != NULL; nzo = nzo->con_next)
   {
      if (mpq_equal(nzo->value, const_one))
      {
         if (nzo != con->first)
             fprintf(fp, "+");
      }
      else if (mpq_equal(nzo->value, const_minus_one))
      {
         fprintf(fp, "-");
      }
      else
      {
         /*lint -e(634) Strong type mismatch (type 'Bool') in equality or conditional */
         if (mpq_sgn(nzo->value) >= 0)
            fprintf(fp, "+");
         
         mpq_out_str(fp, 10, nzo->value);
		 fprintf(fp, "*");
      }
	  fprintf(fp, "_['");
      write_name(fp, nzo->var->name, nzo->var->number);
	  fprintf(fp, "']");      
   }
}

void py_write(
   const Lps*  lp,
   //const Prog* prog,
   FILE*       fp,
   const char* text)
{
   const Var* var;
   const Con* con;
   //const Stmt* stmt;
   const Symbol* sym;
   int i;
   //bool  have_integer  = false;
   //int   cnt;
	   
   assert(lp       != NULL);
   assert(fp       != NULL);

   //if (text != NULL)
   //   fprintf(fp, "%s\n", text);

   fprintf(fp, "import numpy as np\n");

   // class
   fprintf(fp, "class ");
   write_name(fp, strip_path(strip_extension(lp->name)), -1);
   fprintf(fp, ":\n");
   // init
   fprintf(fp, "\tdef __init__(self):\n");
   fprintf(fp, "\t\tself.objective_direction = %d\n", (lp->direct == LP_MIN) ? -1 : 1);
   
   // variables
   fprintf(fp, "\t\tself.variables = {\n\t\t\t");
   for(var = lp->var_root; var != NULL; var = var->next)
   {
      /* A variable without any entries in the matrix
       * or the objective function can be ignored.
       */
      if (var->size == 0 && mpq_equal(var->cost, const_zero) && !lps_has_sos(lp))
         continue;
	  
      if (var->type == VAR_FIXED)
      {
		 fprintf(fp, "'");
         write_name(fp, var->name, var->number);
         fprintf(fp, "': ('R', ");
         mpq_out_str(fp, 10, var->lower);
		 fprintf(fp, ", ");
		 mpq_out_str(fp, 10, var->lower);
      }
      else
      {
		 fprintf(fp, "'");
		 write_name(fp, var->name, var->number);
		 fprintf(fp, "': ('%s', ", var->vclass == VAR_INT ? "Z" : "R");
		 
         if (var->type == VAR_LOWER || var->type == VAR_BOXED)
            mpq_out_str(fp, 10, var->lower);
         else
            fprintf(fp, "float('-inf')");
         
         fprintf(fp, ", ");
         
         if (var->type == VAR_UPPER || var->type == VAR_BOXED)
            mpq_out_str(fp, 10, var->upper);
         else
            fprintf(fp, "float('inf')");
      }
      fprintf(fp, "),\n\t\t\t");
   }
   fprintf(fp, "}\n");

   //sets
   fprintf(fp, "\t\tself.sets = {\n\t\t\t");
   for(sym = symbol_get_all(); sym != NULL; sym = sym->next) {
      if (sym->type == SYM_SET) {
         const Tuple *tuple;

         fprintf(fp, "'");
         write_name(fp, sym->name, -1);

         int value_arity = sym->used > 0 ? entry_get_set(sym->entry[0])->head.dim : -1;
         const char* indexes = symbol_get_index_types(sym);
         const char* value_types = symbol_get_value_types(sym);
         fprintf(fp, "': {'arity': %d, 'value_arity': %d, 'arg_types': '%s', 'value_types': '%s'},\n\t\t\t", sym->set->head.dim, value_arity, indexes, value_types);
         free((void*)indexes);
         free((void*)value_types);
      }
   }
   fprintf(fp, "}\n");

   //vardefs
   fprintf(fp, "\t\tself.vardefs = {\n\t\t\t");
   for(sym = symbol_get_all(); sym != NULL; sym = sym->next) {
      if (sym->type == SYM_VAR && strcmp(sym->name, "@@") != 0) {
         fprintf(fp, "'");
         write_name(fp, sym->name, -1);

         const char* indexes = symbol_get_index_types(sym);
         fprintf(fp, "': {'arity': %d, 'arg_types': '%s', 'domain': '%c'},\n\t\t\t", sym->set->head.dim, indexes, entry_get_var(sym->entry[0])->vclass == VAR_CON ? 'R' : 'Z');
         free((void*)indexes);
      }
   }
   fprintf(fp, "}\n");

   //params
   fprintf(fp, "\t\tself.params = {\n\t\t\t");
   for(sym = symbol_get_all(); sym != NULL; sym = sym->next) {
      if (sym->type == SYM_STRG || sym->type == SYM_NUMB) {
         fprintf(fp, "'");
         write_name(fp, sym->name, -1);

         const char* indexes = symbol_get_index_types(sym);
         fprintf(fp, "': {'arity': %d, 'arg_types': '%s'},\n\t\t\t", sym->set->head.dim, indexes);
         free((void*)indexes);
      }
   }
   fprintf(fp, "}\n\n");
   
   //objective
   fprintf(fp, "\tdef objective(self, _):\n");
   fprintf(fp, "\t\t\"\"\"%s\"\"\"\n", lp->objname == NULL ? "Objective" : lp->objname);
   fprintf(fp, "\t\treturn ");

   bool objective_empty = true;
   for(var = lp->var_root/*, cnt = 0*/; var != NULL; var = var->next)
   {
      /* If cost is zero, do not include in objective function
       */
      if (mpq_equal(var->cost, const_zero))
         continue;

      if (mpq_equal(var->cost, const_one))
         fprintf(fp, "+");
      else if (mpq_equal(var->cost, const_minus_one))
         fprintf(fp, "-");
      else
      {
         /*lint -e(634) Strong type mismatch (type 'Bool') in equality or conditional */
         if (mpq_sgn(var->cost) > 0)
            fprintf(fp, "+");
         
         mpq_out_str(fp, 10, var->cost);
		 fprintf(fp, "*");
      }
	  fprintf(fp, "_[\"");
	  write_name(fp, var->name, var->number);
	  fprintf(fp, "\"]");
	  objective_empty = false;
   }
   if (objective_empty)
      fprintf(fp, "0");
   fprintf(fp, "\n\n");
   
   // constraints
   fprintf(fp, "\tdef constraints(self, _):\n");
   fprintf(fp, "\t\tout = ");

   int con_printed = 0;
   for(con = lp->con_root; con != NULL; con = con->next)
   {
      if (con->size == 0)
         continue;

      ++con_printed;

      fprintf(fp, "(");
      write_lhs(fp, con, con->type);
      write_row(fp, con);
      write_rhs(fp, con, con->type);
	  
	  fprintf(fp, ")\n\t\tout = out & ");
	  //write_name(fp, con->name);
   }
   
   //SOS
   if (lps_has_sos(lp))
   {
      const Sos* sos;
      const Sse* sse;

      for(sos = lp->sos_root; sos != NULL; sos = sos->next)
      {
         ++con_printed;

         fprintf(fp, "(");
         for(sse = sos->first; sse != NULL; sse = sse->next)
         {
			fprintf(fp, "int(");
		    mpq_out_str(fp, 10, sse->weight);
			fprintf(fp, " * _['");
            write_name(fp, sse->var->name, sse->var->number);
			fprintf(fp, "'] != 0)");
        
			if (sse->next != NULL)
				fprintf(fp, "+ "); 
         }
		 
		 fprintf(fp, " <= %d", sos->type == SOS_TYPE1 ? 1 : 2);
			 
		 if (sos->type == SOS_TYPE2 ) {
			 fprintf(fp, " and ");
	         for(sse = sos->first; sse != NULL && sse->next != NULL; sse = sse->next)
	         {
	 			fprintf(fp, "int(");
	 		    mpq_out_str(fp, 10, sse->weight);
	 			fprintf(fp, "*_['");
	            write_name(fp, sse->var->name, sse->var->number);
	 			fprintf(fp, "'] != ");
	 		    mpq_out_str(fp, 10, sse->next->weight);
	 			fprintf(fp, "*_['");
	            write_name(fp, sse->next->var->name, sse->next->var->number);
				fprintf(fp, "'])");
        
	 			if (sse->next->next != NULL)
	 				fprintf(fp, "+");
			 }
			 fprintf(fp, " <= 2");
		 }
		 
		 fprintf(fp, ")\n\t\tout = out & ");
		 //sos->name
      }
   }
   if (con_printed == 0)
       fprintf(fp, "(np.full((_.shape[0]), True) if hasattr(_, 'shape') else True)\n\t\t");
   else {
      fseek(fp, -12, SEEK_CUR);
      ftruncate(fileno(fp), ftell(fp));
   }
   fprintf(fp, "return out\n");

}   

/* ------------------------------------------------------------------------- */
/* Emacs Local Variables:                                                    */
/* Emacs mode:c                                                              */
/* Emacs c-basic-offset:3                                                    */
/* Emacs tab-width:8                                                         */
/* Emacs indent-tabs-mode:nil                                                */
/* Emacs End:                                                                */
/* ------------------------------------------------------------------------- */
